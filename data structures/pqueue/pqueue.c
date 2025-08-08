
/*
    Developer: Ofri Rozner
    Reviwer: Romi Kamin
    Date: 26/09/23
    pqueue - src file
*/
    
#include <assert.h>  /* assert */
#include <stdlib.h> /* malloc */

#include "pqueue.h" /* pqueue API */
#include "../sorted_list/sorted_list.h" /*sorted list*/

/***********************************Typedefs***********************************/
struct pqueue
{
	sorted_list_t *srt_list;
};


/****************************Implementation*****************************/
pqueue_t *PQCreate(cmp_func_t cmp_func)
{
	pqueue_t *pq = NULL;
	pq = (pqueue_t *)malloc(sizeof(pqueue_t));
	if (NULL == pq)
	{
		return NULL;
	}
	
	pq->srt_list = SortedListCreate(cmp_func);
	if (NULL == pq->srt_list)
	{
		free(pq);
		return NULL;
	}
	
	return pq;
}
 
 
void PQDestroy(pqueue_t *pq)
{
	assert(pq);

	SortedListDestroy(pq->srt_list);
	pq->srt_list = NULL;
	free(pq);
	pq = NULL; 
}


int PQEnqueue(pqueue_t *pq, void *data)
{
	assert(pq);
	
	return (SortedListIsIterEqual(SortedListInsert(pq->srt_list, data), 
		SortedListEnd(pq->srt_list)));
}


void *PQDequeue(pqueue_t *pq)
{
	assert(pq);
	assert(!PQIsEmpty(pq));
	
	return SortedListPopFront(pq->srt_list);
}
	
	
void *PQPeek(const pqueue_t *pq)
{
	assert(pq);
	assert(!PQIsEmpty(pq));
		
	return SortedListGetData(SortedListBegin(pq->srt_list));
}


size_t PQSize(const pqueue_t *pq)
{
	assert(pq);
	
	return SortedListCount(pq->srt_list);
}


int PQIsEmpty(const pqueue_t *pq)
{
	assert(pq);

	return SortedListIsEmpty(pq->srt_list);
}


void PQClear(pqueue_t *pq)
{
	assert(pq);

	while (!PQIsEmpty(pq))
	{
		 PQDequeue(pq);
	}
}
		
		
void *PQErase(pqueue_t *pq, match_func_t match_func, void *param)
{
	sorted_list_iter_t iter_to_remove;
	void *data = NULL;
	
	assert(pq);
	assert(NULL != match_func);

	iter_to_remove = SortedListFindIf(SortedListBegin(pq->srt_list), 
				  SortedListEnd(pq->srt_list), match_func, param);				  
	data = SortedListGetData(iter_to_remove);
				  
	if (SortedListIsIterEqual(iter_to_remove, SortedListEnd(pq->srt_list)))
	{
		return NULL;
	}
				  				  	
	SortedListRemove(iter_to_remove);
	
	return data;
}
	

    

    
    
