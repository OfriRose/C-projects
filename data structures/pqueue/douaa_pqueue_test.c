/* ----------------------------------------------------------
 * Filename:    pqueue_test.c
 * Author:      Douaa Satel
 * Reviewer:    Shahar Molina
 * Date:        26.09.2023
 * Lab:         OL-149
 * Description: Test file for the  implementation 
 * of priority queue 
 * ----------------------------------------------------------*/

#include <stdio.h> /* printf */
#include <assert.h> /*assert*/

#include "pqueue.h"
#include "test_util.h"

typedef struct
{
    int id;
    double priority;
} task_t;

typedef struct
{
    int id;
    int grade;
} student_t;

static int TestPQCreateInt(void);
static int TestPQEnqueuePeekDequeueInt(void);
static int TestPQCreateStruct(void);
static int TestPQEnqueuePeekDequeueStruct(void);
static int TestPQSizeIsEmpty(void);
static int TestPQClear(void);
static int TestPQErase(void);
static int TestPQErase2(void);
static int CompareInts(const void *a, const void *b);
static int CompareTasks(const void *a, const void *b);
static int MatchCompareInts(const void *data, void *param);
static int CompareStudentsByGrade(const void *student1, const void *student2);
static int IsGrade99(const void *data, void *param);


int main(void)
{
    int failures = 0;
    int total_test_cases = 17;

    failures += TestPQCreateInt();
    failures += TestPQEnqueuePeekDequeueInt();

    failures += TestPQCreateStruct();
    failures += TestPQEnqueuePeekDequeueStruct();

    failures += TestPQSizeIsEmpty();
    failures += TestPQClear();
    failures += TestPQErase();
    failures += TestPQErase2();

    PrintProgressBar(100 * (total_test_cases - failures) / total_test_cases);

    if (failures == 0)
    {
        printf(GREEN "All tests passed!\n" RESET);
    }
    else
    {
        printf(RED "Some tests failed! Total failures: %d\n" RESET, failures);
    }

    return failures;
}

static int TestPQCreateInt(void)
{
    pqueue_t *pq;
    int failures = 0;

    pq = PQCreate(CompareInts);
    failures += Expected(pq != NULL, "TestPQCreateInt: PQCreate failed!");

    PQDestroy(pq);
    return failures;
}

static int TestPQEnqueuePeekDequeueInt(void)
{
    pqueue_t *pq;
    int values[] = {4, 2, 7, 1, 9, 5};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    size_t i;
    int failures = 0;

    pq = PQCreate(CompareInts);
    failures += Expected(pq != NULL,
     "TestPQEnqueuePeekDequeueInt: PQCreate failed!");

    for (i = 0; i < num_values; ++i)
    {

        failures += Expected(PQEnqueue(pq, &(values[i])) == 0,
         "TestPQEnqueuePeekDequeueInt: PQEnqueue failed!");

    }

    failures += Expected(*(int *)PQPeek(pq) == 9,
     "TestPQEnqueuePeekDequeueInt: PQPeek failed!");

    for (i = 0; i < num_values; ++i)
    {
        PQDequeue(pq);
    }

    PQDestroy(pq);

    return failures;
}

static int TestPQCreateStruct(void)
{
    pqueue_t *pq;
    int failures = 0;

    pq = PQCreate(CompareTasks);
    failures += Expected(pq != NULL,
     "TestPQCreateStruct: PQCreate failed!");

    PQDestroy(pq);
    return failures;
}

static int TestPQEnqueuePeekDequeueStruct(void)
{
    pqueue_t *pq;
    task_t tasks[] = {{1, 4.5}, {2, 2.3}, {3, 7.1}, {4, 1.0}, {5, 9.8}};
    size_t num_tasks = sizeof(tasks) / sizeof(tasks[0]);
    size_t i;
    int failures = 0;

    pq = PQCreate(CompareTasks);
    failures += Expected(pq != NULL,
     "TestPQEnqueuePeekDequeueStruct: PQCreate failed!");

    for (i = 0; i < num_tasks; ++i)
    {
        failures += Expected(PQEnqueue(pq, &( tasks[i])) == 0,
         "TestPQEnqueuePeekDequeueStruct: PQEnqueue failed!");
    }

    failures += Expected(((task_t *)PQPeek(pq))->id == 5,
     "TestPQEnqueuePeekDequeueStruct: PQPeek failed!");

    for (i = 0; i < num_tasks; ++i)
    {
        PQDequeue(pq);
    }

    PQDestroy(pq);

    return failures;
}

static int TestPQSizeIsEmpty(void)
{
    pqueue_t *pq;
    size_t i = 0;
    int failures = 0;
    task_t tasks[] = {{1, 4.5}, {2, 2.3}, {3, 7.1}, {4, 1.0}, {5, 9.8}};
    size_t num_tasks = sizeof(tasks) / sizeof(tasks[0]);

    pq = PQCreate(CompareInts);
    failures += Expected(pq != NULL, "TestPQSizeIsEmpty: PQCreate failed!");

    failures += Expected(PQSize(pq) == 0, "TestPQSizeIsEmpty: PQSize failed!");
    failures += Expected(PQIsEmpty(pq) == 1,
     "TestPQSizeIsEmpty: PQIsEmpty failed!");

    for (i = 0; i < num_tasks; ++i)
    {
        failures += Expected(PQEnqueue(pq, &( tasks[i])) == 0,
         "TestPQEnqueuePeekDequeueStruct: PQEnqueue failed!");
    }

    failures += Expected(PQSize(pq) == num_tasks,
     "TestPQSizeIsEmpty: PQSize failed!");
    failures += Expected(PQIsEmpty(pq) == 0,
     "TestPQSizeIsEmpty: PQIsEmpty failed!");

    PQDestroy(pq);

    return failures;
}

static int TestPQClear(void)
{
    pqueue_t *pq;
    int values[] = {4, 2, 7, 1, 9, 5};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    size_t i;
    int failures = 0;

    pq = PQCreate(CompareInts);
    failures += Expected(pq != NULL, "TestPQClear: PQCreate failed!");

    for (i = 0; i < num_values; ++i)
    {
        failures += Expected(PQEnqueue(pq, &(values[i])) == 0,
         "TestPQClear: PQEnqueue failed!");
    }

    failures += Expected(PQSize(pq) != 0,
     "TestPQClear: PQSize after PQClear failed!");
    failures += Expected(PQIsEmpty(pq) == 0,
     "TestPQClear: PQIsEmpty after PQClear failed!");

    PQClear(pq);

    failures += Expected(PQSize(pq) == 0,
     "TestPQClear: PQSize after PQClear failed2!");
    failures += Expected(PQIsEmpty(pq) == 1,
     "TestPQClear: PQIsEmpty after PQClear failed2!");

    PQDestroy(pq);

    return failures;
}

static int TestPQErase(void)
{
    pqueue_t *pq;
    int values[] = {4, 2, 7, 1, 9, 5};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    size_t i;
    int failures = 0;
    int param = 5;
    void *removed = NULL;

    pq = PQCreate(CompareInts);
    failures += Expected(pq != NULL, "TestPQErase: PQCreate failed!");

    for (i = 0; i < num_values; ++i)
    {
        failures += Expected(PQEnqueue(pq, &(values[i])) == 0,
         "TestPQErase: PQEnqueue failed!");
    }

    param = 5;
    removed = PQErase(pq, MatchCompareInts, &param);

    failures += Expected(*(int *)removed == 5,
     "TestPQErase: Erased value doesn't match expected!");

    param = 20; 
    removed = PQErase(pq, MatchCompareInts, &param);

    failures += Expected(removed == NULL,
     "TestPQErase: Erased value doesn't match expected!");

    PQDestroy(pq);

    return failures;
}

static int TestPQErase2(void)
{
    int failures = 0;
    pqueue_t *pq = PQCreate(CompareStudentsByGrade);
    student_t student1 = {1, 90};
    student_t student2 = {2, 99};
    student_t student3 = {3, 95};

    PQEnqueue(pq, &student1);
    PQEnqueue(pq, &student2);
    PQEnqueue(pq, &student3);

    failures += Expected(NULL != PQErase(pq, IsGrade99, NULL),
                         RED "TestPQErase Failed!\n" RESET);

    PQDestroy(pq);

    if (failures == 0)
    {
        printf(GREEN "TestPQErase Passed!\n" RESET);
    }

    return failures;
}

/*-------Helper funcs----*/

static int CompareInts(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

static int CompareTasks(const void *a, const void *b)
{
    return ((task_t *)b)->priority > ((task_t *)a)->priority ? 1 : -1;
}

static int MatchCompareInts(const void *data, void *param)
{
    int *element = (int *)data;
    int *value = (int *)param;
    return (*element == *value);
}

static int CompareStudentsByGrade(const void *student1, const void *student2)
{
    int grade1 = 0;
    int grade2 = 0;

    assert(student1);
    assert(student2);

    grade1 = ((const student_t *)student1)->grade;
    grade2 = ((const student_t *)student2)->grade;

    return grade1 - grade2;
}

static int IsGrade99(const void *data, void *param)
{
    student_t *student = (student_t *)data;
    (void)param;

    return (student->grade == 99);
}
