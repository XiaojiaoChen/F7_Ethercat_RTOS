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
  $Id: TerminalHandler.h 2926 2017-03-24 13:46:22Z Ricky $:

  Description:
    Terminal Handler header file

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-23  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file  TerminalHandler.h
*   Terminal Handler header file                                             */
/*****************************************************************************/
#ifndef COMPONENTS_CIFXAPPLICATIONDEMO_INCLUDES_TERMINALHANDLER_H_
#define COMPONENTS_CIFXAPPLICATIONDEMO_INCLUDES_TERMINALHANDLER_H_

#include "UserInterface.h"
#include "cifXApplicationDemo.h"

/** APP_MAX_TERMINAL_CMD_LEN characters for the command string*/
#define APP_MAX_TERMINAL_CMD_LEN 7
/** APP_MAX_TERMINAL_CMD_HELP_LEN characters for the help message*/
#define APP_MAX_TERMINAL_CMD_HELP_LEN 35
/** APP_MAX_TERMINAL_CMDLINE_LEN characters for command length*/
#define APP_MAX_TERMINAL_CMDLINE_LEN 40

/*****************************************************************************/
/*! ENUMERATIONS of terminal commands                                        */
/*****************************************************************************/
enum  {
  APP_TC_UNKNOWN      = 0x00,
  APP_TC_HELP,
  APP_TC_READ,
  APP_TC_WRITE,
  APP_TC_FWINFO,
  APP_TC_HWINFO,
  APP_TC_INPUT_IMAGE,
  APP_TC_OUTPUT_IMAGE,
  APP_TC_VARS,
  APP_TC_QUIT,
  APP_TC_LAST,     /** just for determining number of commands in this list */
};

/*****************************************************************************/
/*! ENUMERATIONS of terminal variables code                                                             */
/*****************************************************************************/
enum APP_VAR_CODE_E {
  APP_DIP_INPUTDATA = 1,
  APP_CYCLE_CNT,
  APP_ALARM0_CODE,
  APP_ERROR0_CODE,
  APP_ALARM0,
  APP_ERROR0,
  APP_UART_INPUTDATA0,
  APP_UART_INPUTDATA1,
  APP_ALARM1,
  APP_ERROR1,
  APP_OUTPUTDATA0,
  APP_DIAG0,
  APP_LAST_VAR, /** just to determine number of vars*/
};

enum APP_ERROR {
  APP_E_OK = 0,
  APP_E_VAR_READ_ONLY,
  APP_E_VAR_UNKNOWN,
};

/*****************************************************************************/
/*! typedef terminal command structure                                       */
/*****************************************************************************/
typedef struct APP_TERMINAL_CMD_Ttag {
  int iCode;
  char szString[APP_MAX_TERMINAL_CMD_LEN];
  char szHelp[APP_MAX_TERMINAL_CMD_HELP_LEN];
} APP_TERMINAL_CMD_T;


/*****************************************************************************/
/*! FUNCTION PROTOTYPES                                                      */
/*****************************************************************************/
void App_TerminalHandler(APP_DATA_T *ptAppData);

#endif /* COMPONENTS_CIFXAPPLICATIONDEMO_INCLUDES_TERMINALHANDLER_H_ */
