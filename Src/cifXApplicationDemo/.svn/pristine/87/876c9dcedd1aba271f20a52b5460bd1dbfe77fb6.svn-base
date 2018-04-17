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
  $Id: UserInterface.h 2944 2017-04-11 09:29:27Z Jin $:

  Description:
    user interface header file

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-23  initial version

******************************************************************************/

/*****************************************************************************/
/*! \file  UserInterface.h
*   user interface header file                                               */
/*****************************************************************************/

#ifndef COMPONENTS_NETX_USERINTERFACE_INCLUDES_USERINTERFACE_H_
#define COMPONENTS_NETX_USERINTERFACE_INCLUDES_USERINTERFACE_H_

#include <stdint.h>


/*****************************************************************************/
/*! typedef                                                                  */
/*****************************************************************************/
#if defined ( __CC_ARM ) /* KEIL IDE */
#pragma anon_unions
#endif
typedef union
{
  struct
  {
    unsigned char fAlarm0 : 1;  /** bit0 Alarm0 trigger */
    unsigned char fError0 : 1;  /** bit1 Error0 trigger */
  };
  unsigned char bDiag;
} UI_DIAG_T;


/*****************************************************************************/
/*! ENUMERATIONS                                                             */
/*****************************************************************************/
typedef enum UI_RESULT_Etag {
  UI_OK,
  UI_ERROR,
  UI_UNKNOWN_STAT_LED,
  UI_UNKNOWN_CALLBACK_TYPE,
} UI_RESULT_E;

typedef enum {
  UI_ONE_MSEC  = 100000,
  UI_FIVE_MSEC = 500000,
} UI_TIME_T;

typedef enum UI_CALLBACK_TYPE_Etag {
  UI_CB_INPUT,
  UI_CB_DIAG,
  UI_CB_ROTARY,
  UI_CB_TIMER,
  UI_CB_NUMBER_OF_ENTRIES, /** needed for implementation only to signalize how many entries this enum have*/
} UI_CALLBACK_TYPE_E;


typedef enum UI_STATUS_LED_TYPE_Etag {
  UI_STAT_LED_ALARM,
  UI_STAT_LED_ERROR,
  UI_STAT_LED_STATUS,
  UI_STAT_LED_DATA,
  UI_STAT_LED_NUMBER_OF_ENTRIES,  /** needed for implementation only to signalize how many entries this enum have*/
} UI_STATUS_LED_TYPE_E;


/*****************************************************************************/
/*! FUNCTION PROTOTYPES                                                      */
/*****************************************************************************/
UI_RESULT_E UserInterface_init(void);


/** OUTPUT ******************************************************/
UI_RESULT_E UserInterface_putOutData(uint32_t ulData);
UI_RESULT_E UserInterface_putStatLed(uint32_t ulData);
UI_RESULT_E UserInterface_putStatLedOn(UI_STATUS_LED_TYPE_E eStatusLed);
UI_RESULT_E UserInterface_putStatLedOff(UI_STATUS_LED_TYPE_E eStatusLed);


/** INPUT *******************************************************/

/** POLLING */
uint32_t    UserInterface_getInData(void);
uint32_t    UserInterface_getRotary(void);
uint8_t     UserInterface_getRotary0(void);
uint8_t     UserInterface_getRotary1(void);
UI_DIAG_T   UserInterface_getDiag(void);
uint8_t     UserInterface_getDiagAlarm0(void);
uint8_t     UserInterface_getDiagError0(void);

/** EVENT BASED */
UI_RESULT_E UserInterface_registerCallback(UI_CALLBACK_TYPE_E eClbType, void(*pfnEventClb)(void* pPrm), void* pPrm);
UI_RESULT_E UserInterface_enableCallbacks(void);
UI_RESULT_E UserInterface_disableCallbacks(void);

/** TERMINAL IO *************************************************/
int   UserInterface_kbhit(void);
void  UserInterface_Sleep(uint32_t ulSleepTimeMs);

void  UserInterface_timerIsr(void);

#endif /** COMPONENTS_NETX_USERINTERFACE_INCLUDES_USERINTERFACE_H_ */
