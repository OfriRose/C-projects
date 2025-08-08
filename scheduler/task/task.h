
/*-----------------------------------------------------------/
 *  Developer: Yael Hava									*
 *  Reviwer: *****TO DO******								*
 *  Date: 27/09/23											*
 *  task - h file											*
------------------------------------------------------------*/

#ifndef __ILRD_OL149_TASK_H__
#define __ILRD_OL149_TASK_H__

#include <stddef.h> /* size_t */
#include <time.h> /* time_t */

#include "../../uid/uid.h"

typedef struct task
{
    size_t interval;
    time_t time_to_run;
    int (*action_func)(void *param);
    void *act_params;
    void (*cleanup_func)(void *param_cleanup);
    void *cleanup_params;
    ilrd_uid_t uid;
} task_t;



task_t *TaskCreate(ilrd_uid_t uid, size_t interval, time_t time_to_run,
		int (*action_func)(void *param), void (*cleanup_func)(void *param_cleanup),
		void *act_params, void *param_cleanup);

void TaskDestroy(task_t *task);

int TaskRun(task_t *task);

void TaskUpdateTime(task_t *task, time_t run_time);

void TaskCleanUp(task_t *task);

ilrd_uid_t TaskGetUID(task_t *task);




#endif /* __ILRD_OL149_TASK_H__ */












