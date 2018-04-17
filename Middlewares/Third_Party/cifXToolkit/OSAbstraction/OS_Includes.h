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
  $Id: OS_Includes.h 3205 2017-07-18 06:53:59Z dirk $

  Description:
  	 This is one part of the hardware/OS abstraction layer for the cifX toolkit.

  	 Please refer to the document "cifX/netX Toolkit Manual", available under https://kb.hilscher.com/x/WYWhAQ
     for further information.

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2017-02-16  initial version

 **************************************************************************************/

#ifndef __OS_INCLUDES_H_
#define __OS_INCLUDES_H_

#include <string.h>
#include <stdint.h>

/* Ignore redundant declarations to suppress warning caused by 
   redundant declaration in cifXToolkit.h and cifXHWFunctions.h */
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wredundant-decls"
#endif

#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a<b)?b:a)
#define UNREFERENCED_PARAMETER(x) (x=x)
#define APIENTRY


extern void HAL_GetSystime( uint32_t* pulSystime_s, uint32_t* pulSystime_ns, void* pvUser );
extern void HAL_SysLockIrq(void);
extern void HAL_SysUnlockIrq(void);


#endif /* __OS_INCLUDES_H_ */
