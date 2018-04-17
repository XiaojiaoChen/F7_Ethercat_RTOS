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
  $Id: TerminalHandler.c 2926 2017-03-24 13:46:22Z Ricky $:

  Description:
    Terminal Handler

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-23  initial version

**************************************************************************************/

/*************************************************************************************/
/*! \file TerminalHandler.c
*   Terminal Handler                                                                 */
/*************************************************************************************/
#include "SystemPackets.h"
#include "TerminalHandler.h"

#include <stdio.h>
#include <string.h>
#include "OS_Dependent.h"

/** Terminal service commands */
APP_TERMINAL_CMD_T g_tTerminalCommands[] =
{
  {APP_TC_HELP,         "help",    "display help"},
  {APP_TC_READ,         "rd",      "read var"},
  {APP_TC_WRITE,        "wr",      "write var val"},
  {APP_TC_FWINFO,       "fwinfo",  "firmware info"},
  {APP_TC_HWINFO,       "hwinfo",  "hardware info"},
  {APP_TC_INPUT_IMAGE,  "in",      "display input data image"},
  {APP_TC_OUTPUT_IMAGE, "out",     "display output data image"},
  {APP_TC_VARS,         "var",     "display variables"},
  {APP_TC_QUIT,         "quit",    "returns from main function"},
};


/*****************************************************************************/
/*! Term_MatchTerminalCommand
*   \param szCmd command string  
*   \return Terminal Command code                                            */
/*****************************************************************************/
static int Term_MatchTerminalCommand(char *szCmd)
{
  int i=0;
  for(i=0; i<(APP_TC_LAST-1); i++){
    if( 0 == strcmp(szCmd, &g_tTerminalCommands[i].szString[0])){
      return g_tTerminalCommands[i].iCode;
    }
  }
  return APP_TC_UNKNOWN;
} /** Term_MatchTerminalCommand */


/*****************************************************************************/
/*! Term_PrintHelp
*   Displays a list of supported commands                                    */
/*****************************************************************************/
static void Term_PrintHelp(void)
{
  int i=0;
  for(i=0; i<(APP_TC_LAST-1); i++){
    printf("%s: %s\r\n", g_tTerminalCommands[i].szString, g_tTerminalCommands[i].szHelp);
  }
} /** Term_PrintHelp */


/*****************************************************************************/
/*! Term_ReadVar 
*   \param ptAppData pointer to APP_DATA_T structure  
*   \param iVar terminal variables code
*   \param pulVal variable value pointer      
*   \return APP_E_OK on success                                              */
/*****************************************************************************/
static uint32_t Term_ReadVar(APP_DATA_T *ptAppData, int iVar, uint32_t *pulVal)
{
  uint32_t ulRslt = APP_E_OK;

  switch(iVar){
  case APP_DIP_INPUTDATA:
    OS_EnterLock(0);
    *pulVal = ptAppData->tInputData.bApp_Dip_Inputdata;
    OS_LeaveLock(0);
    break;
  
  case APP_CYCLE_CNT:
    OS_EnterLock(0);
    *pulVal = ptAppData->tInputData.bApp_CycleCnt;
    OS_LeaveLock(0);
    break;  
  
  case APP_ALARM0_CODE:
    OS_EnterLock(0);
    *pulVal = ptAppData->tInputData.bApp_Alarm0_Code;
    OS_LeaveLock(0);
    break;
  
  case APP_ERROR0_CODE:
    OS_EnterLock(0);
    *pulVal = ptAppData->tInputData.bApp_Error0_Code;
    OS_LeaveLock(0);
    break;
    
  case APP_ALARM0:
    OS_EnterLock(0);
    *pulVal = ptAppData->tInputData.bApp_Alarm0;
    OS_LeaveLock(0);
    break;
  
  case APP_ERROR0:
    OS_EnterLock(0);
    *pulVal = ptAppData->tInputData.bApp_Error0;
    OS_LeaveLock(0);
    break;
    
  case APP_UART_INPUTDATA0:
    OS_EnterLock(0);
    *pulVal = ptAppData->tInputData.bApp_Uart_Inputdata0;
    OS_LeaveLock(0);
    break;

  case APP_UART_INPUTDATA1:
    OS_EnterLock(0);
    *pulVal = ptAppData->tInputData.bApp_Uart_Inputdata1;
    OS_LeaveLock(0);
    break;

  case APP_ALARM1:
    OS_EnterLock(0);
    *pulVal = ptAppData->tInputData.bApp_Alarm1;
    OS_LeaveLock(0);
    break;
  
  case APP_ERROR1:
    OS_EnterLock(0);
    *pulVal = ptAppData->tInputData.bApp_Error1;
    OS_LeaveLock(0);
    break;
    
  case APP_OUTPUTDATA0:
    OS_EnterLock(0);
    *pulVal = ptAppData->tOutputData.ulApp_Outputdata0;
    OS_LeaveLock(0);
    break;

  case APP_DIAG0:
    OS_EnterLock(0);
    *pulVal = ptAppData->tVarData.bApp_Diag0;
    OS_LeaveLock(0);
    break;

  default:
    ulRslt = APP_E_VAR_UNKNOWN;
    break;
  }

  return ulRslt;
} /** Term_ReadVar */


/*****************************************************************************/
/*! Term_WriteVar 
*   \param ptAppData pointer to APP_DATA_T structure  
*   \param iVar terminal variables code
*   \param ulVal variable value to be written       
*   \return APP_E_OK on success                                              */
/*****************************************************************************/
static uint32_t Term_WriteVar(APP_DATA_T *ptAppData, int iVar, uint32_t ulVal)
{
  uint32_t ulRslt = APP_E_OK;

  switch(iVar){
  case APP_DIP_INPUTDATA:
    ulRslt = APP_E_VAR_READ_ONLY;
    break;

  case APP_CYCLE_CNT:
    ulRslt = APP_E_VAR_READ_ONLY;
    break;

  case APP_ALARM0_CODE:
    ulRslt = APP_E_VAR_READ_ONLY;
    break;
    
  case APP_ERROR0_CODE:
    ulRslt = APP_E_VAR_READ_ONLY;
    break;
    
  case APP_ALARM0:
    ulRslt = APP_E_VAR_READ_ONLY;
    break;
    
  case APP_ERROR0:
    ulRslt = APP_E_VAR_READ_ONLY;
    break;    
    
  case APP_UART_INPUTDATA0:
    OS_EnterLock(0);
    ptAppData->tInputData.bApp_Uart_Inputdata0 = (uint8_t)ulVal;
    OS_LeaveLock(0);
    break;

  case APP_UART_INPUTDATA1:
    OS_EnterLock(0);
    ptAppData->tInputData.bApp_Uart_Inputdata1 = (uint8_t)ulVal;
    OS_LeaveLock(0);
    break;
    
  case APP_ALARM1:
    OS_EnterLock(0);
    ptAppData->tInputData.bApp_Alarm1 = (uint8_t)ulVal;
    OS_LeaveLock(0);
    break;
    
  case APP_ERROR1:
    OS_EnterLock(0);
    ptAppData->tInputData.bApp_Error1 = (uint8_t)ulVal;
    OS_LeaveLock(0);
    break; 

  case APP_OUTPUTDATA0:
    ulRslt = APP_E_VAR_READ_ONLY;
    break;

  case APP_DIAG0:
    OS_EnterLock(0);
    ptAppData->tVarData.bApp_Diag0 = (uint8_t)ulVal;
    OS_LeaveLock(0);
    break;

  default:
    ulRslt = APP_E_VAR_UNKNOWN;
    break;
  }

  return ulRslt;
} /** Term_WriteVar */


/*****************************************************************************/
/*! Term_ListVars 
*   displays a list of all variables and their values
*   \param ptAppData pointer to APP_DATA_T structure                         */
/*****************************************************************************/
static void Term_ListVars(APP_DATA_T *ptAppData)
{
  int i;
  uint32_t ulValue;

  for(i = 1; i < APP_LAST_VAR; i++){
    if(APP_E_OK == Term_ReadVar(ptAppData, i, &ulValue)){
      printf("var 0x%02x ",i);
      printf("value 0x%08x \r\n", (int)ulValue);
    }
  }
} /** Term_ListVars */


/*****************************************************************************/
/*! Term_TerminalCommandHandler 
*   \param ptAppData pointer to APP_DATA_T structure   
*   \param uiTerminalCommandCode terminal command code   
*   \param iArgc     
*   \param uiArgv                                                            */
/*****************************************************************************/
static void Term_TerminalCommandHandler(APP_DATA_T *ptAppData, int uiTerminalCommandCode, int iArgc, unsigned int *uiArgv)
{
  int       i = 0;
  uint32_t  ulRslt = APP_E_OK;
  uint32_t  ulVal = 0;
  uint8_t   *pbIoData;

  if(iArgc == 0){
    /** error */
  }
  else {
    switch(uiTerminalCommandCode){

    case APP_TC_HELP:
      printf("Help:\r\n");
      Term_PrintHelp();
      break;

    case APP_TC_READ:
      if(iArgc < 2){
        printf("ERROR, READ wrong number of arguments\r\n");
      }
      ulRslt = Term_ReadVar(ptAppData, uiArgv[0], &ulVal);
      switch (ulRslt){
      case APP_E_OK:
        printf("OK, read var 0x%02x value 0x%08x\r\n", uiArgv[0], (int)ulVal);
        break;
      case APP_E_VAR_UNKNOWN:
        printf("ERROR, var 0x%02x is unknown\r\n", uiArgv[0]);
        break;
      default:
        break;
      }
      break;

    case APP_TC_WRITE:
      if(iArgc < 3){
        printf("ERROR, WRITE wrong number of arguments\r\n");
      }
      ulRslt = Term_WriteVar(ptAppData, uiArgv[0], (uint32_t)uiArgv[1]);
      switch (ulRslt){
      case APP_E_OK:
        printf("OK, wrote var 0x%02x value 0x%08x\r\n", uiArgv[0], uiArgv[1]);
        break;
      case APP_E_VAR_READ_ONLY:
        printf("ERROR, var 0x%02x is READ ONLY\r\n", uiArgv[0]);
        break;
      case APP_E_VAR_UNKNOWN:
        printf("ERROR, var 0x%02x is unknown\r\n", uiArgv[0]);
        break;
      default:
        break;
      }
      break;

    case APP_TC_FWINFO:
      Sys_FirmwareIdentifyReq(ptAppData->hChannel[0], &ptAppData->tPkt, ptAppData->ulSendPktCnt++, 0);
      break;

    case APP_TC_HWINFO:
      Sys_HardwareInfoReq(ptAppData->hChannel[0], &ptAppData->tPkt, ptAppData->ulSendPktCnt++);
      break;

    case APP_TC_INPUT_IMAGE:
      printf("Input Data Image:\r\n");
      pbIoData=(uint8_t*)&ptAppData->tInputData;
      OS_EnterLock(0);
      for(i = 0; i < sizeof(ptAppData->tInputData); i++){
        printf("%02d 0x%02x\r\n", i, (int)pbIoData[i]);
      }
      OS_LeaveLock(0);
      break;

    case APP_TC_OUTPUT_IMAGE:
      printf("Output Data Image:\r\n");
      pbIoData = (uint8_t*)&ptAppData->tOutputData;
      OS_EnterLock(0);
      for(i=0; i < sizeof(ptAppData->tOutputData); i++){
        printf("%02d 0x%02x\r\n", i, (int)pbIoData[i]);
      }
      OS_LeaveLock(0);
      break;

    case APP_TC_VARS:
      printf("Variables:\r\n");
      Term_ListVars(ptAppData);
      break;

    case APP_TC_QUIT:
      printf("Quit now!\r\n");
      ptAppData->fRunning = false;
      break;

    case APP_TC_UNKNOWN:
      printf("unknown command\r\n");
      break;

    default:
      printf("unhandled command\r\n");
      break;
    }
  }
} /** Term_TerminalCommandHandler */


/*****************************************************************************/
/*! App_TerminalHandler 
*   \param ptAppData   pointer to APP_DATA_T structure                       */
/*****************************************************************************/
void App_TerminalHandler(APP_DATA_T *ptAppData)
{
  int           iKey = 0;
  static int    s_iKeyCnt = 0;
  static char   s_szInBuffer[APP_MAX_TERMINAL_CMDLINE_LEN];
  char          szCmd[APP_MAX_TERMINAL_CMDLINE_LEN]; /** note, in sscanf format string below, command length is hard coded */
  unsigned int  uiArgv[3];
  int           iArgc = 0;

  if (UserInterface_kbhit()) {
    iKey = getchar();

    if(iKey == '\r'||iKey == '\n'){
      s_szInBuffer[s_iKeyCnt] = 0;
      s_iKeyCnt = 0;
      iArgc=sscanf(&s_szInBuffer[0], "%6s %x %x %x", &szCmd[0], &uiArgv[0], &uiArgv[1], &uiArgv[2]); /** command length is hardcoded here*/
      Term_TerminalCommandHandler(ptAppData, Term_MatchTerminalCommand(&szCmd[0]), iArgc, &uiArgv[0]);
    }
    else {
      s_szInBuffer[s_iKeyCnt] = (char)iKey;
      s_iKeyCnt++;
      if(s_iKeyCnt >= APP_MAX_TERMINAL_CMDLINE_LEN){
        s_iKeyCnt = 0;
      }
    }
  }
} /** App_TerminalHandler */
