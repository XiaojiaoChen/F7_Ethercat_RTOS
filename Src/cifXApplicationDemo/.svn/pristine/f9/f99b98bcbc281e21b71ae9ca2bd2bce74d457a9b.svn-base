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
  $Id: EventHandler.h 2439 2017-01-12 13:56:15Z Jin $:

  Description:
    Event Handler header file

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-23  initial version

******************************************************************************/

/*****************************************************************************/
/*! \file  EventHandler.h
*   Event Handler header file                                                */
/*****************************************************************************/

#ifndef COMPONENTS_CIFXAPPLICATIONDEMO_INCLUDES_EVENTHANDLER_H_
#define COMPONENTS_CIFXAPPLICATIONDEMO_INCLUDES_EVENTHANDLER_H_

#include "cifXApplicationDemo.h"

/*****************************************************************************/
/*! ENUMERATIONS                                                             */
/*****************************************************************************/
typedef enum APP_EVENT_Etag {
  APP_EVENT_NONE = 0,
  APP_EVENT_SET_ALARM0,
  APP_EVENT_CLR_ALARM0,
  APP_EVENT_SET_ALARM1,
  APP_EVENT_CLR_ALARM1,
  APP_EVENT_SET_ERROR0,
  APP_EVENT_CLR_ERROR0,
  APP_EVENT_SET_ERROR1,
  APP_EVENT_CLR_ERROR1,
  APP_EVENT_IO_INVALID,
  APP_EVENT_IO_VALID,
} APP_EVENT_E;


/*****************************************************************************/
/*! FUNCTION PROTOTYPES                                                      */
/*****************************************************************************/
void App_EventHandler(APP_DATA_T *ptAppData);
extern void Protocol_EventHandler(APP_DATA_T *ptAppData, APP_EVENT_E eEvent);


#endif /** COMPONENTS_CIFXAPPLICATIONDEMO_INCLUDES_EVENTHANDLER_H_ */
