/*
 * scheduler.h
 *
 *  Created on: Jul 1, 2023
 *      Author: adinor
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_


/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>				// For standard type definitions

/******************************************************************************
* Constants
*******************************************************************************/

/******************************************************************************
* Configuration
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
/**
 * Define the system tick interval in microseconds
 */
#define SYS_TICK_INTERVAL	 1000UL

/**
 * The interval to call the 10 ms tasks
 */
#define INTERVAL_10MS        (10000UL / SYS_TICK_INTERVAL)

/**
 * The interval to call the 50 ms tasks
 */
#define INTERVAL_50MS        (50000UL / SYS_TICK_INTERVAL)

/**
 * The interval to call the 100 ms tasks
 */
#define INTERVAL_100MS       (100000UL / SYS_TICK_INTERVAL)

/**
 * The interval to call the 500 ms tasks
 */
#define INTERVAL_500MS       (500000UL / SYS_TICK_INTERVAL)

/**
 * The interval to call the 1000 ms tasks
 */
#define INTERVAL_1000MS       (1000000UL / SYS_TICK_INTERVAL)

/******************************************************************************
* Typedefs
*******************************************************************************/
/**
 * Struct TaskType
 * TaskType structure is used to define the parameters required in order to
 * configure a task.
 */
typedef struct
{
  	uint16_t Interval;			/**< Defines how often a task will run  */
  	uint32_t LastTick;			/**< Stores the last tick task was ran  */
  	void (*Func)(void);			/**< Function pointer to the task  */
}Task_t;

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif
void OS_Init(void);
void OS_Run(void);

#endif /* INC_SCHEDULER_H_ */
