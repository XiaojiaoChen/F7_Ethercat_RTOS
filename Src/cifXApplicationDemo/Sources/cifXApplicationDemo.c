/**************************************************************************************
Exclusion of Liability for this demo software:
  The following software is intended for and must only be used for reference and in an
  evaluation laboratory environment. It is provided without charge and is subject to
  alterations. There is no warranty for the software, to the extent permitted by
  applicable law. Except when otherwise stated in writing the copyright holders and/or
  other parties provide the software "as is" without warranty of any kind, either
  expressed or implied.
  Please refer to the Agreement in README_DISCLAIMER.txt, provided together with this file!
  By installing or otherwise using the software, you accept the terms of this Agreement.
  If you do not agree to the terms of this Agreement, then do not install or use the
  Software!
**************************************************************************************/

/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************
  $Id: cifXApplicationDemo.c 2895 2017-03-13 12:55:24Z Jin $:

  Description:
    cifX Application Demo

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-23  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file cifXApplicationDemo.c            
*   cifX Application Demo                                                    */
/*****************************************************************************/


/*****************************************************************************/
/*! General Inclusion Area                                                   */
/*****************************************************************************/
#include <Central.h>
#include "cifXApplicationDemo.h"
#include "TerminalHandler.h"
#include "EventHandler.h"
#include <stdbool.h>
#include "OS_Includes.h"
#include "OS_Spi.h"
#include "SerialDPMInterface.h"
#include "cifXEndianess.h"
#include "cifXErrors.h"
#include "cifXToolkit.h"
#include "rcX_Public.h"
#include "main.h"

extern CENTRAL gCentral;
APP_DATA_T tAppData = {0};
CIFXHANDLE hDriver = NULL;  /** Handle of cifX driver                    */

static int32_t initCifXToolkit();
static bool isCookieAvailable(PDEVICEINSTANCE ptDevInstance, uint32_t ulTimeoutInMs);

/*****************************************************************************/
/*! EthercatCyclicIODataHandler -- cyclic IO data handler
*       fast data exchange with netX via DPM called from a RTOS task with highest priority
*/
/*****************************************************************************/
void EthercatCyclicIODataHandler()
{
  long            lRet = CIFX_NO_ERROR; /** Return value for common error codes  */
  CENTRAL *ptCentral = &gCentral;
  APP_DATA_T      *ptAppData = &tAppData;

  if(ptAppData->hChannel[0] != NULL){
    /**DATA from Master to Slave*************************************/
    lRet = xChannelIORead(ptAppData->hChannel[0], 0, 0, sizeof(ptAppData->tOutputData), &ptAppData->tOutputData, 0);

    /*check data validity*/
    ptAppData->fOutputDataValid = ((lRet != CIFX_NO_ERROR)?0:1);

    /*update data*/
    /** DATA from Slave to Master*************************************/
    lRet = xChannelIOWrite(ptAppData->hChannel[0], 0, 0, sizeof(ptAppData->tInputData), &ptAppData->tInputData, 0);
  }

} /** EthercatCyclicIODataHandler */



/*****************************************************************************/
/*! EthercatPacketEventHandler -- packet and event handler
*   \param pPrm   pointer to APP_DATA_T structure                            */
/*****************************************************************************/
int32_t EthercatPacketEventHandler()
{
	int32_t lRet;

	lRet = Protocol_PacketHandler(&tAppData);

	/** check for events (DIP switches, changed variable values, etc.) */
	App_EventHandler(&tAppData);

	return lRet;

} /** EthercatPacketEventHandler */






/*****************************************************************************/
/*! App_CifXApplicationDemo -- Main entry of cifX Application Demo
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int Ethercat_Init(void)
{
    int32_t   lRet = 0;         /** Return value for common error codes      */
  uint32_t  ulState = 0;      /** Actual state returned                    */
  uint32_t  ulTimeout = 1000; /** Timeout in milliseconds                  */

  initCifXToolkit();

  printf("---------- cifX Application Demo ----------\r\n");

  tAppData.fRunning = true;

  /*set up timer, start timer IT, init LED */
  UserInterface_init();

  /*LED test*/
  App_Selftest();

  /** Opens the driver, allowing access to every driver function */
  lRet = xDriverOpen(&hDriver);

  if(CIFX_NO_ERROR != lRet)
  {
    printf("ERROR: xDriverOpen failed: 0x%08x\r\n", (unsigned int) lRet);
    return lRet;
  } 
  else
  {
    /** Driver successfully opened */
    App_ReadBoardInfo(hDriver, &tAppData.tBoardInfo);
    
    /** Opens a connection to a communication channel */
lRet = xChannelOpen(hDriver, "cifX0", 0, &tAppData.hChannel[0]);

    if(CIFX_NO_ERROR != lRet)
    {
      printf("Error opening Channel: 0x%08X\r\n", (unsigned int) lRet);
      /** Closes an open connection to the driver */
      xDriverClose(hDriver);
      hDriver = NULL;
      return lRet;
    }
    else
    {
      /** Communication Channel successfully opened */
      /** Makes a system start to reset the whole device */
      lRet = xChannelReset(tAppData.hChannel[0], CIFX_SYSTEMSTART, 10000);
      printf("Device is reset.\r\n");
      
      /** Waiting for RCX_COMM_COS_READY flag is set properly */
      do
      {
        xChannelInfo(tAppData.hChannel[0], sizeof(CHANNEL_INFORMATION), &tAppData.tChannelInfo[0]);
      }
      while(!(tAppData.tChannelInfo[0].ulDeviceCOSFlags & RCX_COMM_COS_READY) || (tAppData.tChannelInfo[0].ulDeviceCOSFlags == CIFX_DPM_NO_MEMORY_ASSIGNED));

      /** reads and displays communication channel Information */
      App_ReadChannelInfo(hDriver, tAppData.hChannel[0], &tAppData.tChannelInfo[0]);
      
      /** Set the Application state flag in the application COS flags */
      lRet = xChannelHostState(tAppData.hChannel[0], CIFX_HOST_STATE_READY, &ulState, ulTimeout);

      if(lRet != CIFX_NO_ERROR){
        /** error handling */
    	  Error_Handler();
      }
      /** now the bus is running */
    }
  }
  return lRet;
} /** App_CifXApplicationDemo */


 static int32_t initCifXToolkit(){
  	int32_t      lRet              = 0;                                                  /* Return value for common error codes      */

  	/* First of all initialize toolkit */
  	lRet = cifXTKitInit();


  	if(CIFX_NO_ERROR == lRet)
  	{
  		PDEVICEINSTANCE ptDevInstance = (PDEVICEINSTANCE)OS_Memalloc(sizeof(*ptDevInstance));
  		OS_Memset(ptDevInstance, 0, sizeof(*ptDevInstance));

  		/* Set trace level of toolkit */
  		g_ulTraceLevel = TRACE_LEVEL_ERROR   |
  				TRACE_LEVEL_WARNING |
  				TRACE_LEVEL_INFO    |
  				TRACE_LEVEL_DEBUG;

  		/* Insert the basic device information , into the DeviceInstance structure
         for the toolkit. The DPM address must be zero, as we only transfer address
         offsets via the SPI interface.
         NOTE: The physical address and irq number are for information use
               only, so we skip them here. Interrupt is currently not supported
               and ignored, so we dont need to set it */
  		ptDevInstance->fPCICard          = 0;
  		ptDevInstance->pvOSDependent     = ptDevInstance;
  		ptDevInstance->ulDPMSize         = 0x10000;
  		OS_Strncpy(ptDevInstance->szName, "cifX0", sizeof(ptDevInstance->szName));

  		/* netX needs some time until SPM is ready for netX type autodetection */
  		OS_Sleep(500);

  		/* netX type corresponding SPM initialization */
  		printf("netX type detection and SPM initialisation ...\n\r");
  		lRet=SerialDPM_Init(ptDevInstance);
  		printf("netX type 0x%02x\n\r",(char)lRet);


  		/** we know that netX firmware is flash based in this application, therefore we check if it starts up
  		 ** by comparing cookie at DPM address 0x00 is valid.*/
  		while( false == isCookieAvailable(ptDevInstance, 100) );

  		/* Add the device to the toolkits handled device list */
  		lRet = cifXTKitAddDevice(ptDevInstance);
  	}
  	return lRet;
  }

 static bool isCookieAvailable(PDEVICEINSTANCE ptDevInstance, uint32_t ulTimeoutInMs)
 {
 	bool fCookieAvailable = false;
 	char szCookie[5];
 	uint32_t starttime;
 	uint32_t difftime = 0;

 	starttime = OS_GetMilliSecCounter();

 	while(false == fCookieAvailable && difftime < ulTimeoutInMs)
 	{
 		OS_Memset(szCookie, 0, sizeof(szCookie));

 		HWIF_READN(ptDevInstance, szCookie, ptDevInstance->pbDPM, 4);

 		/** on DPM cards we need to check the for a valid cookie */
 		if( (0 == OS_Strcmp( szCookie, CIFX_DPMSIGNATURE_BSL_STR)) ||
 				(0 == OS_Strcmp( szCookie, CIFX_DPMSIGNATURE_FW_STR)) )
 		{
 			/** We have a firmware or bootloader running, so we assume it is a flash based device */
 			/** NOTE: If the driver is restarted and a RAM based FW was downloaded before this
            will result in the device being handled as flash based.
            Currently there is no way to detect this */
 			fCookieAvailable = true;
 		}else
 		{
 			fCookieAvailable = false;
 			difftime = OS_GetMilliSecCounter() - starttime;
 		}
 	}
 	if(false == fCookieAvailable)
 	{
 		printf("DPM cookie not available since %u milliseconds\r\n", (unsigned int)ulTimeoutInMs);
 	}
 	return fCookieAvailable;
 }

 void Ethercat_DeInit()
{
	int32_t   lRet = 0;         /** Return value for common error codes      */
	uint32_t  ulState = 0;      /** Actual state returned                    */
	uint32_t  ulTimeout = 1000; /** Timeout in milliseconds                  */

	UserInterface_disableCallbacks();
	UserInterface_registerCallback(UI_CB_TIMER, NULL, NULL);
	xChannelBusState(tAppData.hChannel[0], CIFX_BUS_STATE_OFF, &ulState, 10);
	xChannelHostState(tAppData.hChannel[0], CIFX_HOST_STATE_NOT_READY, &ulState, ulTimeout);
	xChannelClose(tAppData.hChannel[0]);
	tAppData.hChannel[0] = NULL;
	tAppData.fRunning = false;
	xDriverClose(hDriver);
	hDriver = NULL;
	printf(" State = 0x%08X !\r\n", (unsigned int) lRet);
	printf("----------------------------------------------------\r\n");
 }
