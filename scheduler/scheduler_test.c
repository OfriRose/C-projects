
#include <stdio.h> /* printf */
#include <string.h> /* strlen */
#include <stdlib.h> /* malloc */

#include "scheduler.h" /* task API */

#define FILE_NAME_TO_STOP "is_stop.txt"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

#define EXPECTED(success_exp, text, test_fails)  \
    if (!(success_exp)) { \
        printf(RED "---> Fail \tTest: %s \n" RESET, text); \
        ++(*test_fails);\
    } else { \
        printf(GREEN"Success" RESET); \
        printf(" \tTest: %s \n" , text); \
}

#define CLEAN_UP(sched_p) { \
    SchedDestroy(sched_p); \
}

#define PRINT_TEST_RESULTS(test_fails) \
    if (0 == test_fails) { \
        printf(GREEN"\n--> All tests passed!\n\n" RESET); \
    } else { \
        printf(RED "\n--> %d tests failed.\n\n" RESET, test_fails); \
    }
    
#define TESTING_SET_HEADER(text) \
    { \
        size_t i = 0; \
        printf("\nTesting Set: %s\n", text); \
        printf("-------------"); \
        for (i = 0; i < strlen(text); i++) { \
            putchar('-'); \
        } \
        putchar('\n'); \
    } 
    
/*--------------------------------------------<Typedefs>
*/
typedef struct action_task
{
	scheduler_t *scheduler;
	ilrd_uid_t uid;
}action_task_t;


typedef struct student 
{
    int id;
    float grade; 
    int age;
    void *next;
} student_t;

typedef struct adv_task
{
	scheduler_t *scheduler;
	ilrd_uid_t uid;
	student_t student;
}advanced_task_t;

typedef struct student_sched
{
    student_t *student; 
    scheduler_t *sched; 
} student_sched_t; 

/*-------------------------------<Function Declarations>
*/
static void TestSchedCreate(int *test_fails);
static void TestSchedAddRemove(int *test_fails);
static void TestSchedRun(int *test_fails);
static void TestSchedRunPeriodic(int *test_fails);
static void TestSchedClear(int *test_fails);
static void TestSchedAdvancedFunctions(int *test_fails);

static int IncreaseGradeBy5(void *action_params);
static int StopAt100(void *action_params);
static int SchedulerStopper(void *action_params);
static int IncreaseTo100AndRemove(void *action_params);
static int TaskRemove(void *action_params);

/*---------------------------------------<Main Function>
*/

int main(void)
{
	int test_fails = 0;
	
	TestSchedCreate(&test_fails);
    TestSchedAddRemove(&test_fails);
    TestSchedClear(&test_fails);
    TestSchedRun(&test_fails);
	TestSchedRunPeriodic(&test_fails);
	TestSchedAdvancedFunctions(&test_fails);
	
	PRINT_TEST_RESULTS(test_fails);
	
    return (0);
}

/*--------------------------------------<Test Functions>
*/

static void TestSchedCreate(int *test_fails)
{
    scheduler_t *sched = SchedCreate();
	
	TESTING_SET_HEADER("Creating and destroying a scheduler");

    EXPECTED(NULL != sched, "Scheduler generated", test_fails);
	EXPECTED(1 == SchedIsEmpty(sched), "Scheduler is empty",test_fails);
	
	CLEAN_UP(sched);

}


static void TestSchedAddRemove(int *test_fails)
{
    scheduler_t *sched = SchedCreate();
    ilrd_uid_t task_id ;

	TESTING_SET_HEADER("Adding and removing tasks");

    task_id = SchedAdd(sched, 5, 1, NULL, NULL, NULL, NULL);
    
    EXPECTED(!UIDIsSame(task_id, bad_uid), 
	"Adding a task to scheduler", test_fails);
    EXPECTED(1 == SchedCount(sched), "Scheduler has one task", test_fails);

	SchedRemove(sched, task_id);
	EXPECTED(0 == SchedCount(sched), "Task removed", test_fails);

	CLEAN_UP(sched);

}


static void TestSchedClear(int *test_fails)
{
    scheduler_t *sched = SchedCreate();
	
	TESTING_SET_HEADER("Clearing a scheduler");

    SchedAdd(sched, 1, 1, NULL, NULL, NULL, NULL);
    SchedAdd(sched, 2, 2, NULL, NULL, NULL, NULL);

    SchedClear(sched);

    EXPECTED(0 == SchedCount(sched), "Scheduler is empty", test_fails);

	CLEAN_UP(sched);

}


static void TestSchedRun(int *test_fails)
{
	student_t student = 
    {
        1,
        90.0,
        24,
        NULL
    };

    scheduler_t *sched = SchedCreate();
    FILE* control_file = NULL;
    ilrd_uid_t task_id = bad_uid;

	TESTING_SET_HEADER("Running and stopping a scheduler with noncyclic tasks");
    
	task_id = SchedAdd(sched, 0, 1, IncreaseGradeBy5, &student, NULL, NULL);
	EXPECTED(!UIDIsSame(task_id, bad_uid), "Task UID is valid", test_fails); 

    task_id = SchedAdd(sched, 0, 2, SchedulerStopper, sched, NULL, NULL); 
	EXPECTED(!UIDIsSame(task_id, bad_uid), "Task UID is valid", test_fails); 

    task_id = SchedAdd(sched, 0, 3, IncreaseGradeBy5, &student, NULL, NULL);
	EXPECTED(!UIDIsSame(task_id, bad_uid), "Task UID is valid", test_fails); 

    EXPECTED(3 == SchedCount(sched), "Three tasks added", test_fails); 
    

    control_file = fopen(FILE_NAME_TO_STOP, "w");
    if (NULL == control_file) 
    {
        perror("Unable to open the control file");
        return;
    }

    fputc('1', control_file);
    fclose(control_file);

    SchedRun(sched);
    

    EXPECTED(!SchedIsEmpty(sched), 
	"Scheduler ran all tasks correctly", test_fails);
    EXPECTED(1 == SchedCount(sched), 
	"One task remainig to execute(planned scene)", test_fails); 
    EXPECTED(student.grade == 95, 
	"Opertation function correctly executed", test_fails);
    
    control_file = fopen(FILE_NAME_TO_STOP, "w");
    if (NULL == control_file) 
    {
        perror("Unable to open the control file");
        return;
    }

    fputc('0', control_file);
    fclose(control_file);

    SchedRun(sched);
    EXPECTED(student.grade == 100, 
	"Opertation function correctly executed", test_fails);
	EXPECTED(SchedIsEmpty(sched), 
	"Scheduler ran all tasks and terminated", test_fails);

	CLEAN_UP(sched);

}


static void TestSchedRunPeriodic(int *test_fails)
{
    student_t student = 
    {
        1,
        90.0,
        24,
        NULL
    };

    scheduler_t *sched = SchedCreate();
    FILE* control_file = NULL;
    
    student_sched_t student_sched;
    student_sched.student = &student;
    student_sched.sched = sched;

	TESTING_SET_HEADER
    ("Running a scheduler with periodic tasks and terminating it");

    SchedAdd(sched, 1, 0, IncreaseGradeBy5, &student, NULL, NULL); 
    SchedAdd(sched, 1, 0, StopAt100, &student_sched, NULL, NULL); 

    control_file = fopen(FILE_NAME_TO_STOP, "w");
    if (NULL == control_file) 
    {
        perror("Unable to open the control file");
        return;
    }

    fputc('0', control_file);
    fclose(control_file);

    SchedRun(sched);
    
    EXPECTED(!SchedIsEmpty(sched), 
	"Scheduler ran a periodic task and stopping task", test_fails);

    EXPECTED(student.grade == 100, 
    "Periodic task correctly executed (element contents)", test_fails);
	
    CLEAN_UP(sched);

}


static void TestSchedAdvancedFunctions(int *test_fails)
{
    ilrd_uid_t task_id = bad_uid;
	ilrd_uid_t task_id2 = bad_uid;
    student_t student = 
    {
        1,
        90.0,
        24,
        NULL
    };

    scheduler_t *sched = SchedCreate();

    advanced_task_t adv_task;
    adv_task.scheduler = sched;
    adv_task.student = student;

    TESTING_SET_HEADER
    ("Running advanced task operations");

    task_id = SchedAdd(sched, 1, 0, IncreaseTo100AndRemove, &adv_task, NULL, NULL); 
    adv_task.uid = task_id;

    SchedRun(sched);
    
  	EXPECTED(SchedIsEmpty(sched), 
	"Scheduler ran a task that removed itself", test_fails)
	
    task_id = SchedAdd(sched, 1, 0, IncreaseGradeBy5, &student, NULL, NULL);
    task_id2 = SchedAdd(sched, 0, 0, IncreaseTo100AndRemove, &adv_task, NULL, NULL); 
    adv_task.uid = task_id;
    
    SchedRun(sched);
    EXPECTED(SchedIsEmpty(sched), 
	"Scheduler ran a task that removed itself", test_fails);
	
	(void)task_id2;
	
    CLEAN_UP(sched);

}

/*------------------------------------<Helper Functions>
*/

static int IncreaseGradeBy5(void *action_params)
{
    student_t *student = (student_t *)action_params;
    
    if (student->grade < 100)
    {
        student->grade += 5;
    }

    return (0);
}

static int StopAt100(void *action_params)
{
    student_sched_t *student_sched = (student_sched_t *)action_params;

    if (student_sched->student->grade >= 100)
    {
        SchedStop(student_sched->sched);
    }

    return (0);
}

static int SchedulerStopper(void *action_params)
{
    scheduler_t *sched = (scheduler_t *)action_params;

    SchedStop(sched);

    return (0);
}

static int IncreaseTo100AndRemove(void *action_params)
{
    advanced_task_t *task = (advanced_task_t *)action_params;

    task->student.grade += 5;
    /*printf("Grade currently: %f\n", task->student.grade); */

    if (task->student.grade >= 100)
    {
        SchedAdd(task->scheduler, 0, 0, TaskRemove, task, NULL, NULL);
    }

    return (0);

}

static int TaskRemove(void *action_params)
{
    advanced_task_t *task = (advanced_task_t *)action_params;

    SchedRemove(task->scheduler, task->uid);

    return (0);

}
