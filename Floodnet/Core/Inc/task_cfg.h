
/** @file tsk_cfg.h
 * @brief This file contains the header definitions for the task configuration.
 */
#ifndef TASK_CFG_H_
#define TASK_CFG_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include <scheduler.h>               // for TaskType


#ifdef __cplusplus
extern "C"{
#endif

Task_t *Task_ConfigGet(void);
uint8_t const Task_NumTasksGet(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*TSK_CFG_H_*/
/*** End of File **************************************************************/
