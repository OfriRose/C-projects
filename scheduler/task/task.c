
/*
    Developer: Ofri Rozner
    Reviwer: 
    Date: 27/09/23
    task - src file
*/
    
#include <assert.h>  /* assert */
#include <stdlib.h> /* malloc */
#include <stddef.h> /*size_t*/


#include "task.h" /* task API */


/******************Service function decleration*************************/


/****************************Implementation*****************************/
task_t *TaskCreate(ilrd_uid_t uid, size_t interval, time_t time_to_run,
		int (*action_func)(void *param), void (*cleanup_func)(void *param_cleanup),
		void *act_params, void *param_cleanup)
{
	task_t *task = (task_t *)malloc(sizeof(task_t));
	if (NULL == task)
	{
		return NULL;
	}
	
	task->interval = interval;
	task->time_to_run = time_to_run;
	task->uid = uid;
	task->action_func = action_func;
	task->cleanup_func = cleanup_func;
	task->act_params = act_params;
	task->cleanup_params = param_cleanup;
	
	return task;
}


void TaskDestroy(task_t *task)
{
	assert(task);
	
	free(task);
	task = NULL;
}


int TaskRun(task_t *task)
{
    int status = task->action_func(task->act_params); 

    if (NULL != task->cleanup_func)
    {
        task->cleanup_func(task->cleanup_params);
    }
	
	return status;
}



ilrd_uid_t TaskGetUID(task_t *task)
{
	assert(task);
	
	return task->uid;
}


void TaskUpdateTime(task_t *task, time_t run_time)
{
	task->time_to_run = time(NULL) - run_time + task->interval;
}
/*********************Service function impl*****************************/
    

    
    
