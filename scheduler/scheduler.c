
/*
    Developer: Ofri Rozner
    Reviwer: Israel Weiss
    Date: 28/09/23
    scheduler - src file
*/
    
#include <assert.h>  /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h>  /* FILE, fopen, fgetc, fclose */
#include <unistd.h> /* sleep */

#include "scheduler.h" /* scheduler API */

struct scheduler
{
	task_t *curr_task;
	pqueue_t *pq;
	int stop;
};

#define STOP_FILE_NAME "stop_file.txt"
/******************Service function decleration*************************/
static void IsUserStopped(void *sched_ptr);
static int cmp_func(const void *task1, const void *task2);
static int match_func(const void *task, void *uid);

/****************************Implementation*****************************/
scheduler_t *SchedCreate()
{
	scheduler_t *scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if(NULL == scheduler)
	{
		return NULL;
	}
	
	scheduler->pq = PQCreate(cmp_func);
	if(NULL == scheduler->pq)
	{
		free (scheduler);
		return NULL;
	}
	
	scheduler->curr_task = NULL;
	scheduler->stop = 0;
	
	return scheduler;
}


void SchedDestroy(scheduler_t *sched)
{
	while (!PQIsEmpty(sched->pq))
	{
		task_t *curr_task = PQDequeue(sched->pq);
		TaskDestroy(curr_task);
	}

	PQDestroy(sched->pq);
	sched->pq = NULL;
	
	free(sched);
	sched = NULL;
}


ilrd_uid_t SchedAdd(scheduler_t *sched, size_t interval, time_t time_to_run, 
		     int (*action_func)(void *act_params), void *act_params, 
		     void (*cleanup_func)(void *cleanup_params), void *cleanup_params)
{
	task_t *task;
	ilrd_uid_t uid = UIDGet();
	if(UIDIsSame(bad_uid, uid))
	{
		return uid;
	}

	task = TaskCreate(uid, interval, time_to_run, action_func, 
					cleanup_func, act_params, cleanup_params);
	if(NULL == task)
	{
		return bad_uid;
	}
	
	if(-1 == (PQEnqueue(sched->pq, task)))
	{
		TaskDestroy(task);
		return bad_uid;
	}
	
	return uid;
}
	
	
int SchedRun(scheduler_t *sched)
{
	int status = 0;
	time_t run_start_time = time(NULL);
	time_t time_since_run = 0;
	time_t task_delay = 0;
	sched->stop = 0;

	while(!SchedIsEmpty(sched) && 0 == sched->stop)
	{
		sched->curr_task = PQDequeue(sched->pq);

		time_since_run = time(NULL) - run_start_time;
		task_delay = (sched->curr_task->time_to_run > time_since_run) ?
					sched->curr_task->time_to_run - time_since_run : 0;
					
		while (sched->curr_task->time_to_run > time(NULL))
		{			
			sleep(task_delay);
		}
		
		status = TaskRun(sched->curr_task);


		if (0 != status)
		{
			TaskDestroy(sched->curr_task);
			sched->curr_task = NULL;
			return status;
		}
		
		if (0 != sched->curr_task->interval)
		{
			TaskUpdateTime(sched->curr_task, run_start_time);
			status = PQEnqueue(sched->pq, sched->curr_task);
			if (0 != status)
			{
				return status;
			}
		}
		else
		{
			TaskDestroy(sched->curr_task);
			sched->curr_task = NULL;
		}
	IsUserStopped(sched);
	}
	return status;
}
		
	
void SchedRemove(scheduler_t *sched, ilrd_uid_t task_id)
{
	ilrd_uid_t *uid_ptr = &task_id;
	task_t *task_to_remove = NULL;
	
	assert(sched);
	
	if (sched->curr_task && UIDIsSame(sched->curr_task->uid, task_id))
	{
		sched->curr_task->interval = 0;
	}
	
	task_to_remove = PQErase(sched->pq, match_func, uid_ptr);
	
	if (task_to_remove)
	{
		TaskDestroy(task_to_remove);
	}
}


int SchedIsEmpty(scheduler_t *sched)
{
    assert(sched);

    return(PQIsEmpty(sched->pq) && (!sched->curr_task));
}


size_t SchedCount(scheduler_t *sched)
{
	size_t size = PQSize(sched->pq);
	
	if(NULL != sched->curr_task)
	{
		++size;
	}
	
	return size;
}


void SchedClear(scheduler_t *sched)
{
	while (!PQIsEmpty(sched->pq))
	{
		task_t *curr_task = PQDequeue(sched->pq);
		TaskDestroy(curr_task);
	}
}


void SchedStop(scheduler_t *sched)
{ 
	sched->stop = 1;
}
/*********************Service function impl*****************************/
    
static int cmp_func(const void *task1, const void *task2) 
{
	task_t *t1 = (task_t *)task1;
	task_t *t2 = (task_t *)task2;

	if (t1->time_to_run < t2->time_to_run) 
	{
		return -1;
	}
	else if (t1->time_to_run > t2->time_to_run) 
	{
		return 1;
	} 
	else 
	{
		return 0;
	}
}


static int match_func(const void *data, void *param)
{
	return UIDIsSame(((task_t *)data)->uid, (*(ilrd_uid_t *)param));
}
    

static void IsUserStopped(void *sched_ptr)
{
    int stop_flag = 0; 
    FILE* file = fopen(STOP_FILE_NAME, "r");
    if (NULL != file) 
    {
    	stop_flag = fgetc(file) - '0';
 	 	fclose(file);
    }
	if(stop_flag != 0)
	{
		SchedStop(sched_ptr);
	}
}
