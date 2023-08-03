/**
 * @file uart_user.c
 * @brief User UART routine
 *
 * @section License
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2021-2022 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneBOOT Open.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 2.1.0
 **/

//Dependencies
#include "stm32wlxx.h"
#include "stm32wlxx_hal.h"
#include "os_port.h"
#include "main.h"
#include "iap/iap.h"
#include "iap_user_settings.h"
#include "uart_user.h"
#include "common.h"
#include "ymodem.h"
#include "error.h"
#include "core/cboot_error.h"
#include "debug.h"

//Y-Modem uart handler
UART_HandleTypeDef UartHandle;

//CycloneBOOT Iap Context
IapContext iapContext;
//CycloneBOOT Iap Settings
IapSettings iapSettings;

//IAP mutex handler
extern osMutexId iapMutexHandle;

//Extern Y-Modem filename buffer holder
extern uint8_t aFileName[FILE_NAME_LENGTH];


/**
 * @brief Download a file via serial port
 **/

void uartUserDownload(void)
{
   uint8_t number[11] = {0};
   uint32_t size = 0;
   COM_StatusTypeDef result;

   cboot_error_t cboot_error;

   //Get exclusive access
   osMutexWait(iapMutexHandle, osWaitForever);

   //Suspend scheduler
   osThreadSuspendAll();

#if 1
   //Debug message
   TRACE_INFO("\r\n");
   TRACE_INFO("Starting firmware update...\r\n");



   //Get default IAP settings
   iapGetDefaultSettings(&iapSettings);

#if defined(IAP_SCENARIO_2)
   //User IAP settings configuration
   iapSettings.imageInCrypto.verifySettings.verifyMethod    = IAP_VERIFY_METHOD;
   iapSettings.imageInCrypto.verifySettings.authAlgo        = IAP_SETTING_AUTH_ALGO;
   iapSettings.imageInCrypto.verifySettings.authHashAlgo    = IAP_SETTING_AUTH_HASH_ALGO;
   iapSettings.imageInCrypto.verifySettings.authKey         = IAP_SETTING_AUTH_KEY;
   iapSettings.imageInCrypto.verifySettings.authKeyLen      = IAP_SETTING_AUTH_KEY_LEN;
   iapSettings.imageInCrypto.cipherAlgo                     = IAP_SETTING_CIPHER_ALGO;
   iapSettings.imageInCrypto.cipherMode                     = IAP_SETTING_CIPHER_MODE;
   iapSettings.imageInCrypto.cipherKey                      = IAP_SETTING_CIPHER_KEY;
   iapSettings.imageInCrypto.cipherKeyLen                   = IAP_SETTING_CIHPER_KEY_LEN;
#elif defined(IAP_SCENARIO_3)
   //User IAP settings configuration
   iapSettings.imageInCrypto.verifySettings.verifyMethod    = IAP_VERIFY_METHOD;
   iapSettings.imageInCrypto.verifySettings.signAlgo        = IAP_SETTING_SIGN_ALGO;
   iapSettings.imageInCrypto.verifySettings.signHashAlgo    = IAP_SETTING_SIGN_HASH_ALGO;
   iapSettings.imageInCrypto.verifySettings.signKey         = IAP_SETTING_SIGN_KEY;
   iapSettings.imageInCrypto.verifySettings.signKeyLen      = IAP_SETTING_SIGN_KEY_LEN;
   iapSettings.imageInCrypto.cipherAlgo                     = IAP_SETTING_CIPHER_ALGO;
   iapSettings.imageInCrypto.cipherMode                     = IAP_SETTING_CIPHER_MODE;
   iapSettings.imageInCrypto.cipherKey                      = IAP_SETTING_CIPHER_KEY;
   iapSettings.imageInCrypto.cipherKeyLen                   = IAP_SETTING_CIHPER_KEY_LEN;
#else
   //User IAP settings configuration
   iapSettings.imageInCrypto.verifySettings.verifyMethod    = IAP_VERIFY_METHOD;
   iapSettings.imageInCrypto.verifySettings.integrityAlgo   = IAP_SETTING_INTEGRITY_ALGO;
#endif
   //User IAP primary(internal flash) memory driver
   iapSettings.primaryFlashDriver             = IAP_SETTING_PRM_MEM_DRIVER;
   //User IAP secondary(external flash) memory driver
   iapSettings.secondaryFlashDriver           = IAP_SETTING_SRD_MEM_DRIVER;

   //User IAP first secondary memory slot configuration
   iapSettings.addrSlot1                       = IAP_SETTING_SRD_MEM_SLOT_1_ADDR;
   iapSettings.sizeSlot1                       = IAP_SETTING_SRD_MEM_SLOT_1_SIZE;
#if (IAP_FALLBACK_SUPPORT == ENABLED)
   //User IAP first secondary memory slot configuration
   iapSettings.addrSlot2                       = IAP_SETTING_SRD_MEM_SLOT_2_ADDR;
   iapSettings.sizeSlot2                       = IAP_SETTING_SRD_MEM_SLOT_2_SIZE;
#endif
#if (IAP_EXT_MEM_ENCRYPTION_SUPPORT == ENABLED)
   // User IAP PSK settings initialization
   iapSettings.psk                              = IAP_SETTINGS_PSK;
   iapSettings.pskSize                          = IAP_SETTINGS_PSK_SIZE;
#endif

#if defined(APP_DEMO_3)
   iapSettings.appVersion = 0x00030000;
#elif defined(APP_DEMO_2)
   iapSettings.appVersion = 0x00020000;
#else
   iapSettings.appVersion = 0x00010000;
#endif

   //Initialize IAP Application context
   cboot_error = iapInit(&iapContext, &iapSettings);
   //Is any error?
   if(cboot_error != CBOOT_NO_ERROR)
   {
      //Debug message
      TRACE_ERROR("Failed to initialize IAP!\r\n");
   }
   else
#endif
   {
      Serial_PutString((uint8_t *)"Waiting for the file to be sent ... (press 'a' to abort)\r\n");
      result = Ymodem_Receive( &size );
      if (result == COM_OK)
      {
         Serial_PutString((uint8_t *)"\n\n\r Programming Completed Successfully!\n\r--------------------------------\r\n Name: ");
         Serial_PutString(aFileName);
         Int2Str(number, size);
         Serial_PutString((uint8_t *)"\r\n Size: ");
         Serial_PutString(number);
         Serial_PutString((uint8_t *)" Bytes\r\n");
         Serial_PutString((uint8_t *)"-------------------\r\n");
#if 1
         cboot_error = iapFinalize(&iapContext);
         if(cboot_error != CBOOT_NO_ERROR)
         {
            //Debug message
            TRACE_ERROR("Failed to finalize firmware update!\r\n");
         }
         else
         {
        	//DEbug message
        	TRACE_INFO("Update image successfully processed. Rebooting to finalize update...\r\n");

            cboot_error = iapReboot(&iapContext);
            if(cboot_error != CBOOT_NO_ERROR)
            {
               //Debug message
               TRACE_ERROR("Failed to reboot!\r\n");
            }
         }
#endif
      }
      else if (result == COM_LIMIT)
      {
         Serial_PutString((uint8_t *)"\r\n\r\nThe image size is higher than the allowed space memory!\r\n");
      }
      else if (result == COM_DATA)
      {
         Serial_PutString((uint8_t *)"\r\n\r\nVerification failed!\r\n");
      }
      else if (result == COM_ABORT)
      {
         Serial_PutString((uint8_t *)"\r\n\nAborted by user.\r\n");
      }
      else
      {
         Serial_PutString((uint8_t *)"\r\nFailed to receive the file!\r\n");
      }
   }

   //Suspend scheduler
   osThreadResumeAll();

   //Release exclusive access
   osMutexRelease(iapMutexHandle);
}


/**
 * @brief Y-Modem Receive User callback
 * @param[in] data Pointer to the received data
 * @param[in] length Length of the received data
 * @retuen Error code
 **/

cboot_error_t Ymodem_Receive_UserCallback(uint8_t *data, size_t length)
{
   cboot_error_t cboot_error;

   //Write received bytes in flash
   cboot_error = iapUpdate(&iapContext, data, length);
   //Is any error?
   if(cboot_error != CBOOT_NO_ERROR)
   {
      //Debug message
      TRACE_ERROR("Failed to update firmware!\r\n");
   }

   //Status code
   return cboot_error;
}


/**
 * @brief Initialize user uart
 **/

void uartUserInit(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;

   //
   // Setup UART against MX_UART_Init(). May not be needed if we keep MX_UART_Init().
   //

   HAL_UART_MspDeInit(Get_DebugHandle());

   //Enable GPIOA clock
   __HAL_RCC_GPIOA_CLK_ENABLE();
   //Enable USART2 clock
   __HAL_RCC_USART2_CLK_ENABLE();

   //Configure USART2_TX (PA2)
   GPIO_InitStructure.Pin = GPIO_PIN_2;
   GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
   GPIO_InitStructure.Pull = GPIO_NOPULL;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
   GPIO_InitStructure.Alternate = GPIO_AF7_USART2;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

   //Configure USART2_RX (PA3)
   GPIO_InitStructure.Pin = GPIO_PIN_3;
   GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
   GPIO_InitStructure.Pull = GPIO_NOPULL;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
   GPIO_InitStructure.Alternate = GPIO_AF7_USART2;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

   UartHandle.Instance = USART2;
   UartHandle.Init.BaudRate = 115200;
   UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
   UartHandle.Init.StopBits = UART_STOPBITS_1;
   UartHandle.Init.Parity = UART_PARITY_NONE;
   UartHandle.Init.Mode = UART_MODE_TX_RX;
   UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
   HAL_UART_Init(&UartHandle);
}


/**
 * @brief Uart user task routine
 **/

void uartUserTaskHandler(void *param)
{
   uint8_t key = 0;
   uint8_t state = 0;
   HAL_StatusTypeDef status;

   //Init uart
   uartUserInit();

   while(1)
   {
      if(state == 0)
      {
         Serial_PutString((uint8_t*) "\r\n");
         Serial_PutString((uint8_t*) "=======================\r\n");
         Serial_PutString((uint8_t*) "= Y-MODEM update menu =\r\n");
         Serial_PutString((uint8_t*) "=======================\r\n");
         Serial_PutString((uint8_t*) "Choices:\r\n");
         Serial_PutString((uint8_t*) "  1 -> Download update image\r\n");
         Serial_PutString((uint8_t*) "  2 -> Get current application version\r\n");
         Serial_PutString((uint8_t*) "\r\n");

         //Change state
         state = 1;
      }
      else if(state == 1)
      {
         /* Clean the input path */
         __HAL_UART_FLUSH_DRREGISTER(&UartHandle);

         /* Receive key */
         status = HAL_UART_Receive(&UartHandle, &key, 1, RX_TIMEOUT);

         if(status == HAL_OK)
         {
            switch(key)
            {
               case '1':
                  Serial_PutString((uint8_t*) "Downloading update image...\r\n");
                  //Start downloading file
                  uartUserDownload();
                  break;

               case '2':
#if defined(APP_DEMO_V1)
                  Serial_PutString((uint8_t*) "v1.0.0\r\n");
#elif defined(APP_DEMO_V2)
                  Serial_PutString((uint8_t*) "v2.0.0\r\n");
#else
                  Serial_PutString((uint8_t*) "v3.0.0\r\n");
#endif
                  break;

               default:
                  Serial_PutString((uint8_t*) "Unknown number!\r\n");
                  Serial_PutString((uint8_t*) "Number should be 1 or 2!\r\n");
                  break;
            }
            Serial_PutString((uint8_t*) "\r\n");

            //Change state
            state = 0;
         }
      }
      else
      {
         //For sanity
      }

      //Os delay
      osDelayTask(200);
   }
}
