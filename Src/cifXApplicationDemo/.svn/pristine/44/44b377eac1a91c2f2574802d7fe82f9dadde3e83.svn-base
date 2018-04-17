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
#include "cifXApplicationDemo.h"
#include "TerminalHandler.h"
#include "EventHandler.h"
#include <stdbool.h>

/*****************************************************************************/
/*! App_IODataHandler -- cyclic IO data handler
*       fast data exchange with netX via DPM called from a timer ISR
*   \param pPrm   pointer to APP_DATA_T structure                            */
/*****************************************************************************/
void App_IODataHandler(void *pPrm)
{
  long            lRet = CIFX_NO_ERROR; /** Return value for common error codes  */
  static uint32_t s_ulCycle = 0;
  APP_DATA_T      *ptAppData = (APP_DATA_T*) pPrm;

  if(ptAppData->hChannel[0] != NULL){

    /** OUTPUT DATA *********************************************************************/
    lRet = xChannelIORead(ptAppData->hChannel[0], 0, 0, sizeof(ptAppData->tOutputData), &ptAppData->tOutputData, 0);
    if(lRet != CIFX_NO_ERROR){
      ptAppData->fOutputDataValid = 0;
      /** TODO: error handling */
    }
    else{
      /** process newly received output data image */
      ptAppData->fOutputDataValid = 1;
      UserInterface_putOutData((uint32_t) ptAppData->tOutputData.ulApp_Outputdata0);
    }

    /** INPUT DATA ***********************************************************************/
    /** update input data image to be sent in this cycle */
    ptAppData->tInputData.bApp_Dip_Inputdata  = (uint8_t) UserInterface_getInData();
    ptAppData->tInputData.bApp_CycleCnt       = (uint8_t) ++s_ulCycle;
    ptAppData->tInputData.bApp_Alarm0_Code    = UserInterface_getRotary0();
    ptAppData->tInputData.bApp_Error0_Code    = UserInterface_getRotary1();
    ptAppData->tInputData.bApp_Alarm0         = UserInterface_getDiagAlarm0();
    ptAppData->tInputData.bApp_Error0         = UserInterface_getDiagError0();
    /** the following part of the input data image contains data which is updated in the "slow" main loop */
    /**    ptAppData->tInputData.bApp_Uart_Inputdata0  not written here but in "slow" main loop */
    /**    ptAppData->tInputData.bApp_Uart_Inputdata1  not written here but in "slow" main loop */
    /**    ptAppData->tInputData.bApp_Alarm1           not written here but in "slow" main loop */
    /**    ptAppData->tInputData.bApp_Error1           not written here but in "slow" main loop */

    lRet = xChannelIOWrite(ptAppData->hChannel[0], 0, 0, sizeof(ptAppData->tInputData), &ptAppData->tInputData, 0);
    if(lRet != CIFX_NO_ERROR){
      /** TODO: error handling */
    }
  }

} /** App_IODataHandler */


/*****************************************************************************/
/*! App_CifXApplicationDemo -- Main entry of cifX Application Demo
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int App_CifXApplicationDemo(void)
{
  APP_DATA_T tAppData = {0};
  CIFXHANDLE hDriver = NULL;  /** Handle of cifX driver                    */
  int32_t   lRet = 0;         /** Return value for common error codes      */
  uint32_t  ulState = 0;      /** Actual state returned                    */
  uint32_t  ulTimeout = 1000; /** Timeout in milliseconds                  */

  printf("---------- cifX Application Demo ----------\r\n");

  tAppData.fRunning = true;

  UserInterface_init();
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
      if(lRet == CIFX_NO_ERROR)
      {
        /** register App_IODataHandler as timer callback function */
        if(UI_OK == (lRet = UserInterface_registerCallback(UI_CB_TIMER, App_IODataHandler, (void*)&tAppData)))
        {
          /** enable callback functions only after timer callback function is registered */
          lRet = UserInterface_enableCallbacks();
        }
        else
        {
          printf("fails to register timer callback function!\r\n");
        }
      }

      if(lRet == CIFX_NO_ERROR)
      {
        lRet = Protocol_SendFirstPacket(&tAppData);
      }
      
      if(lRet != CIFX_NO_ERROR){
        /** error handling */
      }

      /** now the bus is running */
      while(tAppData.fRunning && lRet == CIFX_NO_ERROR)
      {
        /** check and process incoming packets */
        lRet = Protocol_PacketHandler(&tAppData);

        /** check and process input from terminal (UART console) */
        App_TerminalHandler(&tAppData);

        /** check for events (DIP switches, changed variable values, etc.) */
        App_EventHandler(&tAppData);

        UserInterface_Sleep(1);
      }

      /** remove calling of App_IODataHandler, because we don't have valid IO Data any more */
      UserInterface_disableCallbacks();
      UserInterface_registerCallback(UI_CB_TIMER, NULL, NULL);

      /** Set the bus state flag in the application COS state flags, to stop communication */
      xChannelBusState(tAppData.hChannel[0], CIFX_BUS_STATE_OFF, &ulState, 10);

      /** Set Host not ready to stop bus communication */
      xChannelHostState(tAppData.hChannel[0], CIFX_HOST_STATE_NOT_READY, &ulState, ulTimeout);
    }

    /** Close a connection to a communication channel */
    xChannelClose(tAppData.hChannel[0]);
    tAppData.hChannel[0] = NULL;
    tAppData.fRunning = false;
  }

  /** Closes an open connection to the driver */
  xDriverClose(hDriver);
  hDriver = NULL;

  printf(" State = 0x%08X !\r\n", (unsigned int) lRet);
  printf("----------------------------------------------------\r\n");

  return lRet;

} /** App_CifXApplicationDemo */
