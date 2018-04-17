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
  $Id: OS_Custom_STM32.c 3815 2018-02-28 16:07:21Z dirk $

  Description:
  	 This is one part of the hardware/OS abstraction layer for the cifX toolkit.
  	 The functions in this C-Module are called from the cifX Toolkit.
  	 It is adapted for STM32 Microcontroller targets, using STM32_HAL function calls.
  	 The implementation is for a bare metal implementation, without RTOS usage.
  	 Therefore some, not required functions are "stubbed out".
  	 Two contexts are specified in the application: 1) main loop, 2) timer interrupt handler
  	 To protect critical data access, OS_WaitMutex(), OS_EnterLock() simply disable the timer interrupt.

  	 Please refer to the document "cifX/netX Toolkit Manual", available under https://kb.hilscher.com/x/WYWhAQ
     for further information.

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2017-02-16  initial version

 **************************************************************************************/

/* Standard includes */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "OS_Includes.h"
#include "cifXErrors.h"
#include "OS_Dependent.h"

#include "main.h"

static          int               s_fOSInitDone = 0;


/* resources for events */
/* maximum number of events */
#define OSAL_MAX_EVENTS 16
/* event states */
typedef enum
{
  EVENT_STATE_UNUSED,
  EVENT_STATE_CLEAR,
  EVENT_STATE_SET,
  EVENT_STATE_DELETED,
} OSAL_EVENT_STATE_E;

volatile OSAL_EVENT_STATE_E s_eOsalEvents[OSAL_MAX_EVENTS + 1];


/* idle time processing, provided in the application */
void (*g_pfnOSAL_Idle)(void);



/*****************************************************************************/
/*! O/S Specific initialization (initializes libpciaccess)
*     \return CIFX_NO_ERROR on success                                       */
/*****************************************************************************/
int32_t OS_Init(void)
{
  s_fOSInitDone = 1;
  
  return CIFX_NO_ERROR;
}

/*****************************************************************************/
/*! O/S Specific de-initialization (de-initializes libpciaccess)             */
/*****************************************************************************/
void OS_Deinit(void)
{
}

/*****************************************************************************/
/*! Memory allocation wrapper (standard malloc)
*     \param ulSize Size of block to allocate
*     \return NULL on failure                                                */
/*****************************************************************************/
void* OS_Memalloc(uint32_t ulSize)
{
  return malloc(ulSize);
}

/*****************************************************************************/
/*! Memory de-allocation wrapper (standard free)
*     \param pvMem  Block to free                                            */
/*****************************************************************************/
void OS_Memfree(void* pvMem)
{
  free(pvMem);
}

/*****************************************************************************/
/*! Memory resize wrapper (standard realloc)
*     \param pvMem      Block to resize
*     \param ulNewSize  New size of the block
*     \return NULL on error                                                  */
/*****************************************************************************/
void* OS_Memrealloc(void* pvMem, uint32_t ulNewSize)
{
  return realloc(pvMem, ulNewSize);
}

/*****************************************************************************/
/*! Memset wrapper
*     \param pvMem   Memory to set
*     \param bFill   Fill byte
*     \param ulSize  Size of the fill block                                  */
/*****************************************************************************/
void OS_Memset(void* pvMem, uint8_t bFill, uint32_t ulSize)
{
  memset(pvMem, bFill, ulSize);
}

/*****************************************************************************/
/*! Memcopy wrapper
*     \param pvDest  Destination pointer
*     \param pvSrc   Source pointer
*     \param ulSize  Size to copy                                            */
/*****************************************************************************/
void OS_Memcpy(void* pvDest, void* pvSrc, uint32_t ulSize)
{
  memcpy(pvDest, pvSrc, ulSize);
}

/*****************************************************************************/
/*! Memcompare wrapper
*     \param pvBuf1  First compare buffer
*     \param pvBuf2  Second compare buffer
*     \param ulSize  Size to compare
*     \return 0 if blocks are equal                                          */
/*****************************************************************************/
int OS_Memcmp(void* pvBuf1, void* pvBuf2, uint32_t ulSize)
{
  return memcmp(pvBuf1, pvBuf2, ulSize);
}

/*****************************************************************************/
/*! Memmove wrapper (Overlapping memory copy)
*     \param pvDest  Destination buffer
*     \param pvSrc   Source buffer
*     \param ulSize  Size to move                                            */
/*****************************************************************************/
void OS_Memmove(void* pvDest, void* pvSrc, uint32_t ulSize)
{
  memmove(pvDest, pvSrc, ulSize);
}

/*****************************************************************************/
/*! Read PCI configuration area of specified card
*     \param pvOSDependent OS Dependent parameter to identify card
*     \return Pointer to configuration data (passed to WritePCIConfig)       */
/*****************************************************************************/
void* OS_ReadPCIConfig(void* pvOSDependent)
{
  UNREFERENCED_PARAMETER(pvOSDependent);
  return NULL;
}

/*****************************************************************************/
/*! Restore PCI configuration
*     \param pvOSDependent OS Dependent parameter to identify card
*     \param pvPCIConfig   Pointer returned from ReadPCIConfig               */
/*****************************************************************************/
void OS_WritePCIConfig(void* pvOSDependent, void* pvPCIConfig)
{
  UNREFERENCED_PARAMETER(pvOSDependent);
  UNREFERENCED_PARAMETER(pvPCIConfig);
}

/*****************************************************************************/
/*! Enable interrupts on the given device
*     \param pvOSDependent Pointer to internal device structure              */
/*****************************************************************************/
void OS_EnableInterrupts(void* pvOSDependent)
{
	__enable_irq();
}

/*****************************************************************************/
/*! Disable interrupts on the given device
*     \param pvOSDependent Pointer to internal device structure              */
/*****************************************************************************/
void OS_DisableInterrupts(void* pvOSDependent)
{
	__disable_irq();
}

/*****************************************************************************/
/*! Open file for reading
*     \param szFilename   File to open (including path)
*     \param pulFileSize  Returned size of the file in bytes
*     \return Handle to the file, NULL on failure                            */
/*****************************************************************************/
void* OS_FileOpen(char* szFile, uint32_t* pulFileLen)
{
  UNREFERENCED_PARAMETER(szFile);
  UNREFERENCED_PARAMETER(pulFileLen);
  return NULL;
}

/*****************************************************************************/
/*! Read data from file
*     \param pvFile    Handle to the file (acquired by OS_FileOpen)
*     \param ulOffset  Offset to read from
*     \param ulSize    Size to read
*     \param pvBuffer  Buffer to read data into
*     \return number of bytes read                                           */
/*****************************************************************************/
uint32_t OS_FileRead(void* pvFile, uint32_t ulOffset, uint32_t ulSize, void* pvBuffer)
{
  UNREFERENCED_PARAMETER(pvFile);
  UNREFERENCED_PARAMETER(ulOffset);  
  UNREFERENCED_PARAMETER(ulSize);
  UNREFERENCED_PARAMETER(pvBuffer);
  return 0;
}

/*****************************************************************************/
/*! Close open file
*     \param pvFile    Handle to the file (acquired by OS_FileOpen)          */
/*****************************************************************************/
void OS_FileClose(void* pvFile)
{
  UNREFERENCED_PARAMETER(pvFile);
}

/*****************************************************************************/
/*! Get Millisecond counter value (used for timeout handling)
*     \return Counter value with a resolution of 1ms                         */
/*****************************************************************************/
uint32_t OS_GetMilliSecCounter(void)
{
  return HAL_GetTick();
}

/*****************************************************************************/
/*! Sleep for the given time
*     \param ulSleepTimeMs Time in ms to sleep (0 will sleep for 50us)       */
/*****************************************************************************/
void OS_Sleep(uint32_t ulSleepTimeMs)
{
	uint32_t ulStartTime   = 0;
	uint32_t ulCurrentTime = 0;

	if (!s_fOSInitDone)
		return;

	if (ulSleepTimeMs == 0)
	{
		if (g_pfnOSAL_Idle != NULL)
			g_pfnOSAL_Idle(); /* call idle time function, can be used by application*/
	}
	else
	{
		ulStartTime = OS_GetMilliSecCounter();
		do
		{
			if (g_pfnOSAL_Idle != NULL)
				g_pfnOSAL_Idle();
			HAL_Delay(1);
			ulCurrentTime = OS_GetMilliSecCounter();
		}
		while ((ulCurrentTime - ulStartTime) < ulSleepTimeMs);
	}


}

/*****************************************************************************/
/*! Create Lock (Usually same as mutex, but does not support timed waiting)
*     \return Handle to created lock                                         */
/*****************************************************************************/
void* OS_CreateLock(void)
{
  return OS_CreateMutex();
}

/*****************************************************************************/
/*! Acquire a lock
*     \param pvLock Handle to lock                                           */
/*****************************************************************************/
void OS_EnterLock(void* pvLock)
{
	//HAL_NVIC_DisableIRQ(TIMx_Ethercat_IRQn); // disable IRQ at NVIC
}

/*****************************************************************************/
/*! Release a lock
*     \param pvLock Handle to lock                                           */
/*****************************************************************************/
void OS_LeaveLock(void* pvLock)
{
//	HAL_NVIC_EnableIRQ(TIMx_Ethercat_IRQn); // enable IRQ at NVIC
}

/*****************************************************************************/
/*! Delete a lock
*     \param pvLock Handle to lock                                           */
/*****************************************************************************/
void OS_DeleteLock(void* pvLock)
{
  OS_DeleteMutex(pvLock);
}

/*****************************************************************************/
/*! Create mutex
*     \return Handle to new created mutex                                    */
/*****************************************************************************/
void* OS_CreateMutex(void)
{
  return (void*)1;
}

/*****************************************************************************/
/*! Try to acquire mutex with timeout
*     \param pvMutex   Handle to mutex
*     \param ulTimeout Timeout in ms to wait for mutex
*     \return !=0 if mutex was acquired                                      */
/*****************************************************************************/
int OS_WaitMutex(void* pvMutex, uint32_t ulTimeout)
{ 
//	HAL_NVIC_DisableIRQ(TIMx_Ethercat_IRQn); // disable IRQ at NVIC

    UNREFERENCED_PARAMETER(pvMutex);
    UNREFERENCED_PARAMETER(ulTimeout);
  
  return 1;  
}

/*****************************************************************************/
/*! Release previously acquired mutex
*     \param pvMutex   Handle to mutex                                       */
/*****************************************************************************/
void OS_ReleaseMutex(void* pvMutex)
{
//	HAL_NVIC_EnableIRQ(TIMx_Ethercat_IRQn); // enable IRQ at NVIC

	UNREFERENCED_PARAMETER(pvMutex);
}

/*****************************************************************************/
/*! Delete mutex
*     \param pvMutex   Handle to mutex                                       */
/*****************************************************************************/
void OS_DeleteMutex(void* pvMutex)
{
  UNREFERENCED_PARAMETER(pvMutex);
}

/*****************************************************************************/
/*! Create event
*     \return Handle to created event                                        */
/*****************************************************************************/
void* OS_CreateEvent(void)
{
	  uint32_t ulIndex;

	  /* first pass: search for an event entry that has never been used */
	  for (ulIndex = OSAL_MAX_EVENTS; ulIndex > 0; ulIndex--)
	  {
	    if (s_eOsalEvents[ulIndex] == EVENT_STATE_UNUSED)
	    {
	      s_eOsalEvents[ulIndex] = EVENT_STATE_CLEAR;
	      break;
	    }
	  }
	  if (ulIndex == 0)
	  { /* second pass: search for an event entry that has been used and released before */
	    for (ulIndex = OSAL_MAX_EVENTS; ulIndex > 0; ulIndex--)
	    {
	      if (s_eOsalEvents[ulIndex] == EVENT_STATE_DELETED)
	      {
	        s_eOsalEvents[ulIndex] = EVENT_STATE_CLEAR;
	        break;
	      }
	    }
	  }
	  return (void*)(ulIndex);
}

/*****************************************************************************/
/*! Signal event
*     \param pvEvent Handle to event                                         */
/*****************************************************************************/
void OS_SetEvent(void* pvEvent)
{
	  uint32_t ulIndex = (uint32_t) pvEvent;

	  if (ulIndex <= OSAL_MAX_EVENTS)
	  {
	    if (s_eOsalEvents[ulIndex] == EVENT_STATE_CLEAR)
	      s_eOsalEvents[ulIndex] = EVENT_STATE_SET;
	  }
}

/*****************************************************************************/
/*! Reset event
*     \param pvEvent Handle to event                                         */
/*****************************************************************************/
void OS_ResetEvent(void* pvEvent)
{
	  uint32_t ulIndex = (uint32_t) pvEvent;

	  if (ulIndex <= OSAL_MAX_EVENTS)
	    s_eOsalEvents[ulIndex] = EVENT_STATE_CLEAR;
}

/*****************************************************************************/
/*! Delete event
*     \param pvEvent Handle to event                                         */
/*****************************************************************************/
void OS_DeleteEvent(void* pvEvent)
{
	  uint32_t ulIndex = (uint32_t) pvEvent;

	  if (ulIndex <= OSAL_MAX_EVENTS)
	    s_eOsalEvents[ulIndex] = EVENT_STATE_DELETED;
}

/*****************************************************************************/
/*! Wait for event
*     \param pvEvent   Handle to event
*     \param ulTimeout Timeout in ms to wait for event
*     \return CIFX_EVENT_SIGNALLED if event was set, CIFX_EVENT_TIMEOUT otherwise */
/*****************************************************************************/
uint32_t OS_WaitEvent(void* pvEvent, uint32_t ulTimeout)
{ 
	  uint32_t    ulResult      = CIFX_NO_ERROR;
	  uint32_t    ulIndex       = (uint32_t) pvEvent;
	  uint32_t    ulStartTime   = 0;
	  uint32_t    ulCurrentTime = 0;

	  if (ulIndex > OSAL_MAX_EVENTS)
	    ulResult = CIFX_INVALID_PARAMETER;
	  else
	  {
	    ulStartTime = OS_GetMilliSecCounter();
	    while (1)
	    {
	      if (s_eOsalEvents[ulIndex] == EVENT_STATE_SET)
	      {
	        s_eOsalEvents[ulIndex] = EVENT_STATE_CLEAR;
	        break;
	      }
	      if (s_eOsalEvents[ulIndex] < EVENT_STATE_CLEAR
	      ||  s_eOsalEvents[ulIndex] > EVENT_STATE_SET)
	      {
	        ulResult = CIFX_INVALID_PARAMETER;
	        break;
	      }
	      ulCurrentTime = OS_GetMilliSecCounter();
	      if ((ulCurrentTime - ulStartTime) >= ulTimeout)
	      {
	        ulResult = CIFX_EVENT_TIMEOUT;
	        break;
	      }
	      OS_Sleep(0);
	    }
	  }
	  return (ulResult);
}

/*****************************************************************************/
/*! Map driver pointer to user space
*     \param pvDriverMem  Pointer to driver memory
*     \param ulMemSize    Size of the memory to map
*     \param ppvMappedMem Returned mapped pointer
*     \param os_dependent OS Dependent parameter in DEVICEINSTANCE
*     \return Handle to mapping, NULL on error                               */
/*****************************************************************************/
void* OS_MapUserPointer(void* pvDriverMem, uint32_t ulMemSize, void** ppvMappedMem, void* pvOSDependent)
{
  UNREFERENCED_PARAMETER(ulMemSize);
  UNREFERENCED_PARAMETER(pvOSDependent);
  /* We are running in user mode, so it is not necessary to map anything to user space */ 
  *ppvMappedMem = pvDriverMem;
  
  return pvDriverMem;
}

/*****************************************************************************/
/*! Unmap previously mapped user space pointer 
*     \param phMapping  Handle returned from OS_MapUserPointer
*     \param os_dependent OS Dependent parameter in DEVICEINSTANCE
*     \return 0 on error                                                     */
/*****************************************************************************/
int OS_UnmapUserPointer(void* phMapping, void* pvOSDependent)
{
  UNREFERENCED_PARAMETER(phMapping);
  UNREFERENCED_PARAMETER(pvOSDependent);
  /* We are running in user mode, so it is not necessary to map anything to user space */ 
  return 1;
}

/*****************************************************************************/
/*! Compare strings
*     \param pszBuf1  String buffer 1
*     \param pszBuf2  String buffer 2
*     \return 0 if strings are equal                                         */
/*****************************************************************************/
int OS_Strcmp(const char* pszBuf1, const char* pszBuf2)
{
  return strcmp(pszBuf1, pszBuf2);
}

/*****************************************************************************/
/*! Compare strings case insensitive
*     \param pszBuf1  String buffer 1
*     \param pszBuf2  String buffer 2
*     \param ulLen    Maximum length to compare
*     \return 0 if strings are equal                                         */
/*****************************************************************************/
int OS_Strnicmp(const char* pszBuf1, const char* pszBuf2, uint32_t ulLen)
{
  return strncasecmp(pszBuf1, pszBuf2, ulLen);
}

/*****************************************************************************/
/*! Get length of string
*     \param szText  Text buffer
*     \return Length of given string                                         */
/*****************************************************************************/
int OS_Strlen(const char* szText)
{
  return strlen(szText);
}

/*****************************************************************************/
/*! Copy string to destination buffer
*     \param szText   Destination string
*     \param szSource Source string
*     \param ulLen    Maximum length to copy
*     \return Pointer to szDest                                              */
/*****************************************************************************/
char* OS_Strncpy(char* szDest, const char* szSource, uint32_t ulLen)
{
  return strncpy(szDest, szSource, ulLen);
}

#ifdef CIFX_TOOLKIT_ENABLE_DSR_LOCK
static volatile int s_iIrq;
/*****************************************************************************/
/*! This functions needs to provide a lock against the interrupt service 
*   routine of the device. The easiest way is an IRQ lock but some operating 
*   systems provide a way to lock against a specific interrupt
*     \param pvODDependent OS Dependent parameter in DEVICEINSTANCE          */
/*****************************************************************************/
void OS_IrqLock(void* pvOSDependent)
{
  NX50_lock_irqfiq_save(s_iIrq);   
}

/*****************************************************************************/
/*! This function re-enables the device's interrupt service routine.
*     \param pvODDependent OS Dependent parameter in DEVICEINSTANCE          */
/*****************************************************************************/
void OS_IrqUnlock(void* pvOSDependent)
{
  NX50_lock_irqfiq_restore(s_iIrq);
}
#endif
