/*
 * scheduler.c
 *
 *  Created on: Jul 1, 2023
 *      Author: adinor
 */


#include <stdint.h>
#include "scheduler.h"
#include "task_cfg.h"
#include "sys_tick.h"

static uint32_t Tick = 0;						// System tick
static Task_t *TaskPointer;                		// Task pointer
static uint8_t TaskIndex = 0;					// Task index




void OS_Init(void)
{
	TaskPointer = Task_ConfigGet();    // Get a pointer to the task configuration
}


void OS_Run(void)
{
	const uint8_t NumTasks = Task_NumTasksGet();		// Number of tasks

	Tick = SysTick_Get();		// Get current system tick

	/* Loop through the task configuration block and calculate whether there is
	 * a task that is ready to execute. If there is, execute that task. Otherwise
	 * continue looping.
	 */
	for(TaskIndex = 0; TaskIndex < NumTasks; TaskIndex++)
	{
		if((Tick - TaskPointer[TaskIndex].LastTick) >= TaskPointer[TaskIndex].Interval)
		{
			(*TaskPointer[TaskIndex].Func)();         // Execute Task
			TaskPointer[TaskIndex].LastTick = Tick;  // Save last tick the task was ran.
		}
	}// end for
}


