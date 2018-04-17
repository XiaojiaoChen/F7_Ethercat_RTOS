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
  $Id: EventHandler.c 2895 2017-03-13 12:55:24Z Jin $:

  Description:
    Event Handler

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-23  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file EventHandler.c                                
*   Event Handler                                                            */
/*****************************************************************************/
#include "EventHandler.h"
#include "UserInterface.h"


/*****************************************************************************/
/*! checks if events have been triggered
*   It detects state changes like switch of a DIP switch or changed variables
*   (I.e. states of certain elements are stored in this function)
*   If the state of an element changes, a respective EVENT is signalled to the
*   protocol specific event handler function, named EventHandlerProtocl()
*   furthermore the specified generic hardware action might be implemented in 
*   this function, like e.g. switching on/off status LEDs
*   \param ptAppData   pointer to APP_DATA_T structure                       */
/*****************************************************************************/
void App_EventHandler(APP_DATA_T *ptAppData)
{
//  UI_DIAG_T tDiag = {{0}};
//  static UI_DIAG_T s_tLastDiag = {{0}};
//  static uint8_t s_bLastAlarm1State = 0;
//  static uint8_t s_bLastError1State = 0;
//  static int s_fLastOutputDataValid = 0;
//
//  APP_EVENT_E eEvent = APP_EVENT_NONE;
//
//  /** checks if Alarm0 is triggered  */
//  tDiag.fAlarm0 = UserInterface_getDiagAlarm0();
//  if(tDiag.fAlarm0 != s_tLastDiag.fAlarm0){
//    if(tDiag.fAlarm0){
//      eEvent = APP_EVENT_SET_ALARM0;
//      UserInterface_putStatLedOn(UI_STAT_LED_ALARM);
//    }
//    else {
//      eEvent = APP_EVENT_CLR_ALARM0;
//      UserInterface_putStatLedOff(UI_STAT_LED_ALARM);
//    }
//    Protocol_EventHandler(ptAppData, eEvent);
//  }
//
//  /** checks if Error0 is triggered  */
//  tDiag.fError0 = UserInterface_getDiagError0();
//  if(tDiag.fError0 != s_tLastDiag.fError0){
//    if(tDiag.fError0){
//      eEvent = APP_EVENT_SET_ERROR0;
//      UserInterface_putStatLedOn(UI_STAT_LED_ERROR);
//    }
//    else {
//      eEvent = APP_EVENT_CLR_ERROR0;
//      UserInterface_putStatLedOff(UI_STAT_LED_ERROR);
//    }
//    Protocol_EventHandler(ptAppData, eEvent);
//  }
//
//  /** checks if Alarm1 is triggered  */
//  if(ptAppData->tInputData.bApp_Alarm1 != s_bLastAlarm1State){
//    if(ptAppData->tInputData.bApp_Alarm1){
//      eEvent = APP_EVENT_SET_ALARM1;
//      UserInterface_putStatLedOn(UI_STAT_LED_ALARM);
//    }
//    else {
//      eEvent = APP_EVENT_CLR_ALARM1;
//      UserInterface_putStatLedOff(UI_STAT_LED_ALARM);
//    }
//    Protocol_EventHandler(ptAppData, eEvent);
//  }
//
//  /** checks if Error1 is triggered  */
//  if(ptAppData->tInputData.bApp_Error1 != s_bLastError1State){
//    if(ptAppData->tInputData.bApp_Error1){
//      eEvent = APP_EVENT_SET_ERROR1;
//      UserInterface_putStatLedOn(UI_STAT_LED_ERROR);
//    }
//    else {
//      eEvent = APP_EVENT_CLR_ERROR1;
//      UserInterface_putStatLedOff(UI_STAT_LED_ERROR);
//    }
//    Protocol_EventHandler(ptAppData, eEvent);
//  }
//
//  /** checks if Output Data validity is changed  */
//  if(ptAppData->fOutputDataValid != s_fLastOutputDataValid){
//    if(ptAppData->fOutputDataValid){
//      eEvent = APP_EVENT_IO_VALID;
//      UserInterface_putStatLedOn(UI_STAT_LED_DATA);
//    }
//    else {
//      eEvent = APP_EVENT_IO_INVALID;
//      UserInterface_putStatLedOff(UI_STAT_LED_DATA);
//    }
//    Protocol_EventHandler(ptAppData, eEvent);
//  }
//
//  /** Copies the current elements states to the static variables */
//  s_tLastDiag = tDiag;
//  s_fLastOutputDataValid = ptAppData->fOutputDataValid;
//  s_bLastAlarm1State = ptAppData->tInputData.bApp_Alarm1;
//  s_bLastError1State = ptAppData->tInputData.bApp_Error1;

} /** App_EventHandler */
