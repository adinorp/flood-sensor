
/******************************************************************************
* Includes
*******************************************************************************/
#include <scheduler.h>				// For task interval definitions
#include <task.h>                   // For continuous tasks
#include <task_100ms.h>             // For 100 ms tasks
#include <task_10ms.h>             	// For 10 ms tasks
#include <TerminalTask.h>
#include <SensorsTask.h>

/**
 * Task configuration table.  Holds the task interval, last time executed, and
 * the function to be executed.  A continuous task is defined as a task with
 * an interval of 0.  Last time executed is set to 0.
 */
static Task_t Tasks[] =
{
	{ INTERVAL_10MS ,  0, Task_10ms   },
  	{ INTERVAL_100MS,  0, Task_100ms  },
	{ INTERVAL_10MS,   0, Task_Terminal},
	{INTERVAL_10MS,    0, SensorReadTask},
  	{ 0             ,  0, Task        },
};

/**
 * Defines the number of tasks that are currently scheduled to run.
 */
static uint8_t const TaskTotalNumber = sizeof(Tasks) / sizeof(*Tasks);


Task_t *Task_ConfigGet(void)
{
   	return Tasks;
}


uint8_t const Task_NumTasksGet(void)
{
	return TaskTotalNumber;
}

/*** End of File **************************************************************/

