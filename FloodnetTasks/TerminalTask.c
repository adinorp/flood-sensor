/*
 * TerminalTask.c
 *
 *  Created on: May 7, 2023
 *      Author: adinor
 */


//#include "Uart_Driver.h"
#include "TerminalTask.h"
#include "Uart.h"


char cValuetoPost;
uint8_t uartData[1];


#define QUEUE_TIMEOUT 10
#define RX_WORD_LENGTH 255
#define MAX_COMMAND_LEN 120
#define DEVICE_COMMAND_TABLE_LEN 200
#define COMMAND_TABLE_LEN 35

static char gCommandBuffer[MAX_COMMAND_LEN + 1];


char TerminalMsgBuffer[TERMINAL_MSG_BUFFER];



typedef struct
{
	char *name;
	void (*function)(char *Arg);
}command_t;


BaseType_t xHigherPrioritTaskWoken;


/* STM32 Command Table */
command_t const gCommandTable[DEVICE_COMMAND_TABLE_LEN] =
{
		{"STDEVICEID",NULL},
};


#define UART_RECEIVE_SIZE 1
#define BLE_DMA_RECEIVE_SIZE 1
#define TO_UPPER(x) (((x >= 'a') && (x <= 'z')) ? ((x) - ('a' - 'A')) : (x))

int CommandLineBuildCommand(char nextChar);
void CommandLineProcessCommand(char * buffer);



/* USER CODE END Header_terminalTaskHandler */
void terminalTaskHandler(void const * argument)
{
	/* USER CODE BEGIN 5 */
	int tCommandReady = 0;
	char tRxedChar;
	HAL_UART_Receive_IT(Get_DebugHandle(),(uint8_t*)uartData,UART_RECEIVE_SIZE);
	/* Infinite loop */
	for(;;)
	{
		/* Process Terminal Commands */
		if(xQueueReceive(Get_TerminalQueueHandle(),&tRxedChar,QUEUE_TIMEOUT))
		{
			tCommandReady = CommandLineBuildCommand(tRxedChar);
			if(tCommandReady)
			{
				CommandLineProcessCommand(gCommandBuffer);
				tCommandReady = 0;
			}
		}
		osDelay(1);
	}
	/* USER CODE END 5 */
}


static uint16_t commandBuilderIdx = 0;
int CommandLineBuildCommand(char nextChar)
{
	/* Don't store any new line characters or spaces. */
	if ((nextChar == '\n') || (nextChar == ' ') || (nextChar == '\t'))
	{
		return false;
	}
	/* The completed command has been received. Replace the final carriage
	 * return character with a NULL character to help with processing the
	 * command. */
	if (nextChar == '\r')
	{
		gCommandBuffer[commandBuilderIdx] = '\0';
		commandBuilderIdx = 0;
		return true;
	}
	/* Convert the incoming character to uppercase. This matches the case
	 * of commands in the command table. Then store the received character
	 * in the command buffer. */
	gCommandBuffer[commandBuilderIdx] = TO_UPPER(nextChar);
	commandBuilderIdx++;
	/* If the command is too long, reset the index and process
	 * the current command buffer. */
	if (commandBuilderIdx >= MAX_COMMAND_LEN)
	{
		commandBuilderIdx = 0;
		return true;
	}

	return false;

}

void CommandLineProcessCommand(char * buffer)
{

	int idx;
	int CommandFound = false;
	//char *Com= strtok(buffer,"+");
	char *Arg = strtok(NULL,"+");

	/* Search for the command in the command table until it is found or
	 * the end of the table is reached. If the command is found, break
	 * out of the loop. */
	for (idx = 0; gCommandTable[idx].name != NULL; idx++)
	{
		if (strncmp(gCommandTable[idx].name, buffer,strlen(gCommandTable[idx].name)) == 0)
		{
			CommandFound = true;
			(*gCommandTable[idx].function)(Arg);
			break;
		}
	}
	/* If the command was found, call the command function. Otherwise,
	 * output an error message. */
	if (CommandFound==false)
	{
		snprintf(TerminalMsgBuffer, sizeof(TerminalMsgBuffer), "ERROR,Command not found\n");
		serialPutStr(TerminalMsgBuffer);
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if(huart->Instance==USART2)
	{
		HAL_UART_Receive_IT(Get_DebugHandle(),(uint8_t*)uartData,UART_RECEIVE_SIZE);
		cValuetoPost = (char)uartData[0];
		xQueueSendToBackFromISR(Get_TerminalQueueHandle(),(void*)&cValuetoPost,&xHigherPrioritTaskWoken);
	}
}






