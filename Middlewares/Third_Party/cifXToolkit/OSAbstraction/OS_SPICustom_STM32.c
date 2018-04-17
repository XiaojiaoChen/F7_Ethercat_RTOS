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
  $Id: OS_SPICustom_STM32.c 3242 2017-07-19 13:12:41Z dirk $

  Description:
  	 This is one part of the hardware/OS abstraction layer for the cifX toolkit.
  	 The functions in this C-Module are called from the cifX Toolkit.
  	 It is adapted for STM32 Microcontroller targets, using STM32_HAL function calls.

  	 In this C-Module, hardware dependent communication functions for serial access to the
  	 netX via SPM (Serial Dual Port Memory) are implemented.

  	 Please refer to the document "cifX/netX Toolkit Manual", available under https://kb.hilscher.com/x/WYWhAQ
     for further information.

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2017-02-16  initial version

 **************************************************************************************/


/*****************************************************************************/
/*! \file OS_SPICustom.c
 *    Sample SPI abstraction layer. Implementation must be done
 *    according to used target system                                         */
/*****************************************************************************/

#include "OS_Spi.h"
#include "OS_Dependent.h"
#include "main.h"
#include "stddef.h"
#include "spi.h"

/*****************************************************************************/
/*!  \addtogroup CIFX_TK_OS_ABSTRACTION Operating System Abstraction
 *    \{                                                                      */
/*****************************************************************************/



/*****************************************************************************/
/*! Assert chip select
 *   \param pvOSDependent OS Dependent parameter to identify card             */
/*****************************************************************************/
void OS_SpiAssert(void* pvOSDependent)
{
	HAL_GPIO_WritePin(SPM_CS_GPIO_Port, SPM_CS_Pin, GPIO_PIN_RESET);
}

/*****************************************************************************/
/*! Deassert chip select
 *   \param pvOSDependent OS Dependent parameter to identify card             */
/*****************************************************************************/
void OS_SpiDeassert(void* pvOSDependent)
{
	HAL_GPIO_WritePin(SPM_CS_GPIO_Port, SPM_CS_Pin, GPIO_PIN_SET);
}

/*****************************************************************************/
/*! Transfer byte stream via SPI
 *   \param pvOSDependent OS Dependent parameter to identify card
 *   \param pbSend        Send buffer (NULL for polling)
 *   \param pbRecv        Receive buffer (NULL if discard)
 *   \param ulLen         Length of SPI transfer                              */
/*****************************************************************************/
void OS_SpiTransfer(void* pvOSDependent, uint8_t* pbSend, uint8_t* pbRecv, uint32_t ulLen)
{
	HAL_StatusTypeDef tRet=HAL_OK;
	static uint32_t ulErrCnt=0;

	/*no receive data requested (just transmit) */
	if(pbRecv==NULL){
		tRet=HAL_SPI_Transmit_IT(&hspi_Ethercat, pbSend, (uint16_t) ulLen);

	}
	/*no transmit data (just receive) */
	else if(pbSend==NULL) {
		tRet=HAL_SPI_Receive_IT(&hspi_Ethercat, pbRecv, (uint16_t) ulLen);
	}
	else {
		tRet=HAL_SPI_TransmitReceive_IT(&hspi_Ethercat, pbSend, pbRecv, (uint16_t) ulLen);
	}


	if(tRet!=HAL_OK){
		ulErrCnt++;
	}

	/*blocking SPI transfer, wait until all bytes are transferred*/
	while(HAL_SPI_STATE_READY != HAL_SPI_GetState(&hspi_Ethercat));
}

/*****************************************************************************/
/*! \}                                                                       */
/*****************************************************************************/
