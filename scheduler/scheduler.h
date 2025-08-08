/*
    Developer: Ofri Rozner
    Reviwer: Israel Weiss
    Date: 28/09/23
    scheduler - header file
*/

/* DESCRIPTION:
 * An API for a task scheduler, allowing fot timed tasks.
 * The scheduler manages executives tasks in terms of timing, adding, and removing.
 */
 
 
#ifndef __ILRD_OL149_SCHEDULER_H__
#define __ILRD_OL149_SCHEDULER_H__

#include "../uid/uid.h"
#include "task/task.h"
#include "../../ds/pqueue/pqueue.h"

typedef struct scheduler scheduler_t;


/**
 * Creates a new scheduler.
 * 
 * @return A handle to the created scheduler.
 * @note The caller is responsible for freeing the scheduler when done using SchedDestroy.
 * @complexity Time: O(1), Space: O(1)
 */
scheduler_t *SchedCreate(void);

/**
 * Destroys a scheduler.
 * 
 * @param sched A handle to the scheduler to destroy.
 * @note This function should be called to clean up resources when the 
 * scheduler is no longer needed.
 * @complexity Time: O(n), Space: O(1).
 */
void SchedDestroy(scheduler_t *sched);

/**
 * Adds a new task to the scheduler.
 * 
 * @param sched A handle to the scheduler.
 * @param interval The interval between task runs in seconds.
 * @param time_to_run The initial time (in seconds) to run the task.
 * @param action_func A function for task execution.
 * @param act_params A reference to parameters for the action function.
 * @param cleanup_func A function for function cleanup.
 * @param cleanup_params A reference to parameters for the cleanup function.
 * @return A UID representing the scheduled task.
 * @note Upon failure a BAD_UID is returned.
 * @complexity Time: O(1), Space: O(1).
 */
ilrd_uid_t SchedAdd(scheduler_t *sched, size_t interval, time_t time_to_run, 
			int (*action_func)(void *act_params), void *act_params, 
			void (*cleanup_func)(void *cleanup_params), void *cleanup_params);
			
/**
 * Runs the tasks scheduled in the scheduler.
 * 
 * @param sched A hanlde to a scheduler.
 * @return 0 if successful, or an error code upon failure of the task execution.
 * @note Upon failure of a task, function terminates (pending tasks may exist)
 * @complexity Time: O(n), Space: O(1).
 */			
int SchedRun(scheduler_t *sched);

/**
 * Removes a scheduled task from the scheduler.
 * 
 * @param sched A handle to the scheduler.
 * @param task_id The UID of the task to be removed.
 * @complexity Time: O(n), Space: O(1).
 */
void SchedRemove(scheduler_t *sched, ilrd_uid_t task_id);

/**
 * Gets the number of tasks in the scheduler.
 * 
 * @param sched A handle to the scheduler.
 * @return The number of tasks currently pending and running in the scheduler.
 * @note passing a null-scheduler is undefined behavior.
 * @complexity Time: O(1), Space: O(1)
 */
size_t SchedCount(scheduler_t *sched);

/**
 * Checks if the scheduler is empty.
 * 
 * @param sched A handle to the scheduler.
 * @return 1 if the scheduler is empty, 0 otherwise.
 * @note passing a null-scheduler will result in an undefined behavior.
 * @complexity Time: O(1), Space: O(1)
 */
int SchedIsEmpty(scheduler_t *sched);

/**
 * stops the scheduler
 * 
 * @param sched A handle to the scheduler.
 * @note This function stops the execution of scheduled tasks but does not 
 * remove them.
 * @note passing a null-scheduler will result in an undefined behavior.
 * @complexity Time: O(1), Space: O(1)
 */
void SchedStop(scheduler_t *sched);

/**
 * Destroys all tasks in the scheduler.
 * 
 * @param sched A hanlde to the scheduler.
 * @note passing a null-scheduler is an undefined behavior.
 * @complexity Time: O(n), Space: O(1), where n is the number of scheduled tasks.
 */
void SchedClear(scheduler_t *sched);


#endif /* __ILRD_OL149_SCHEDULER_H__ */
