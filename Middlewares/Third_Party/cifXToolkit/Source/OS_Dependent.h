/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: OS_Dependent.h 6601 2014-10-02 09:37:56Z stephans $:

  Description:
    OS Dependent function declaration. These functions must be implemented for the
    toolkit, to allow abstraction from the operating system

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2011-11-29  Added OS_Time() function
    2011-05-25  OS_Init was still using long instead of int32_t as return
    2010-03-29  Added define CIFX_TOOLKIT_ENABLE_DSR_LOCK to allow lockout against
                ISR (used in DSR). This needs the functions OS_IrqLock / OS_IrqUnlock
                which should lock at least against the Device Interrupt
    2008-06-17  Function OS_MapUserPointer() and OS_UnmapUserPointer() extended by
                a new parameter pcOSDependent
    2007-04-19  OS_Strnicmp function included
    2007-03-27  Mutex functions included
    2007-03-21  Support enabling and disabling on interrupts on the card (used for assign
                PCI interrupts and enabling the host to process the DPM/PCI Irqs)
    2006-07-07  intitial version

**************************************************************************************/

#ifndef __OS_DEPENDENT__H
#define __OS_DEPENDENT__H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define CIFX_EVENT_SIGNALLED  0
#define CIFX_EVENT_TIMEOUT    1

int32_t  OS_Init(void);
void     OS_Deinit(void);

void*    OS_Memalloc(uint32_t ulSize);
void     OS_Memfree(void* pvMem);
void*    OS_Memrealloc(void* pvMem, uint32_t ulNewSize);

void     OS_Memset(void* pvMem, unsigned char bFill, uint32_t ulSize);
void     OS_Memcpy(void* pvDest, void* pvSrc, uint32_t ulSize);
int      OS_Memcmp(void* pvBuf1, void* pvBuf2, uint32_t ulSize);
void     OS_Memmove(void* pvDest, void* pvSrc, uint32_t ulSize);

void*    OS_ReadPCIConfig(void* pvOSDependent);
void     OS_WritePCIConfig(void* pvOSDependent, void* pvPCIConfig);
void     OS_EnableInterrupts(void* pvOSDependent);
void     OS_DisableInterrupts(void* pvOSDependent);

void*    OS_FileOpen(char* szFilename, uint32_t* pulFileSize);
uint32_t OS_FileRead(void* pvFile, uint32_t ulOffset, uint32_t ulSize, void* pvBuffer);
void     OS_FileClose(void* pvFile);

uint32_t OS_GetMilliSecCounter(void);
void     OS_Sleep(uint32_t ulSleepTimeMs);

void*    OS_CreateLock(void);
void     OS_EnterLock(void* pvLock);
void     OS_LeaveLock(void* pvLock);
void     OS_DeleteLock(void* pvLock);

void*    OS_CreateMutex(void);
int      OS_WaitMutex(void* pvMutex, uint32_t ulTimeout);
void     OS_ReleaseMutex(void* pvMutex);
void     OS_DeleteMutex(void* pvMutex);

void*    OS_CreateEvent(void);
void     OS_SetEvent(void* pvEvent);
void     OS_ResetEvent(void* pvEvent);
void     OS_DeleteEvent(void* pvEvent);
uint32_t OS_WaitEvent(void* pvEvent, uint32_t ulTimeout);

int      OS_Strcmp(const char* pszBuf1, const char* pszBuf2);
int      OS_Strnicmp(const char* pszBuf1, const char* pszBuf2, uint32_t ulLen);
int      OS_Strlen(const char* szText);
char*    OS_Strncpy(char* szDest, const char* szSource, uint32_t ulLen);

void*    OS_MapUserPointer(void* pvDriverMem, uint32_t ulMemSize, void** ppvMappedMem, void* pvOSDependent);
int      OS_UnmapUserPointer(void* phMapping, void* pvOSDependent);

#ifdef CIFX_TOOLKIT_ENABLE_DSR_LOCK
  void OS_IrqLock(void* pvOSDependent);
  void OS_IrqUnlock(void* pvOSDependent);
#endif

#ifdef CIFX_TOOLKIT_TIME
  uint32_t OS_Time( uint32_t *ptTime);
#endif

#ifdef __cplusplus
}
#endif


#endif /* __OS_DEPENDENT__H */
