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
  $Id: EventHandlerECS.c 2305 2016-11-23 13:05:55Z Jin $:

  Description:
    Protocol EventHandler

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-10-21  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file EventHandlerECS.c
*   Protocol EventHandler                                                    */
/*****************************************************************************/

#include "EventHandler.h"

/*****************************************************************************/
/** Handles Protocol specific events.
Does nothing, because this is a simple example */
/*****************************************************************************/
void Protocol_EventHandler(APP_DATA_T *ptAppData, APP_EVENT_E eEvent){

  switch(eEvent){

  case APP_EVENT_SET_ALARM0:
    break;
  case APP_EVENT_CLR_ALARM0:
    break;

  case APP_EVENT_SET_ALARM1:
    break;
  case APP_EVENT_CLR_ALARM1:
    break;

  case APP_EVENT_SET_ERROR0:
    break;
  case APP_EVENT_CLR_ERROR0:
    break;

  case APP_EVENT_SET_ERROR1:
    break;
  case APP_EVENT_CLR_ERROR1:
    break;

  default:
    break;

  }
}

