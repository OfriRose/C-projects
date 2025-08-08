/*
*    Developer: Ofri Rozner
*    Reviwer: 
*    Date: 12/09/23
*    sorted_list - src file
*******************************************************************************/

#include <assert.h>  /* assert */
#include <stdlib.h> /* malloc */

#include "sorted_list.h" /* sorted_list API */

/***********************************Typedefs***********************************/
struct sorted_list
{
	dlist_t *dlist;
	sorted_list_compare_func_t cmp_func;
};

/************************Service function decleration*************************/

static sorted_list_iter_t DListIterToSortedListIter(dlist_iter_t diter,
                                                    const sorted_list_t *list);
static dlist_iter_t SortedListIterToDListIter(sorted_list_iter_t iter);
#ifndef NDEBUG
static int IsFromBeforeTo(sorted_list_iter_t from, sorted_list_iter_t to);
#endif
/********************************Implementation*******************************/
sorted_list_t *SortedListCreate(sorted_list_compare_func_t cmp_func)
{
	sorted_list_t *list = NULL;
	list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	if (NULL == list)
	{
		return NULL;
	}
	
	list->dlist = DListCreate();
	if (NULL == list->dlist)
	{
		free(list);
		return NULL;
	}
		
	list->cmp_func = cmp_func;
	
	return list;
}


void SortedListDestroy(sorted_list_t *list)
{
	DListDestroy(list->dlist);
	list->dlist = NULL;
	free(list);
	list = NULL; 
}


sorted_list_iter_t SortedListInsert(sorted_list_t *list, void *data)
{
	dlist_iter_t dlist_iter; 
	sorted_list_iter_t sorted_iter; 

	assert(list);
	assert(list->dlist);

	dlist_iter = DListBegin(list->dlist);
	
	while (!DListIsIterEqual(dlist_iter, DListEnd(list->dlist)) && 
			0 >= list->cmp_func(DListGetData(dlist_iter), data))
	{
		dlist_iter = DListNext(dlist_iter);
	}
	
	sorted_iter.iter = DListInsertBefore(list->dlist, dlist_iter, data);
	if (SortedListIsIterEqual(sorted_iter, SortedListEnd(list)))
	{
		return SortedListEnd(list);
	}
	
#ifndef NDEBUG
	sorted_iter.list = list;
#endif

	return sorted_iter;

}


sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter)
{
	sorted_list_iter_t sorted_iter;
	dlist_iter_t diter;
	const sorted_list_t *saved_list = NULL;
	
#ifndef NDEBUG
	saved_list = iter.list;
#endif

	diter = DListRemove(SortedListIterToDListIter(iter));

	sorted_iter = DListIterToSortedListIter(diter, saved_list);

	return sorted_iter;
}


sorted_list_iter_t SortedListFind(sorted_list_t *list, sorted_list_iter_t from, 
						sorted_list_iter_t to, void *data)
{
	assert(list);
	assert(from.list == to.list);
	assert(IsFromBeforeTo(from, to));	
	assert(IsFromBeforeTo(from, to));
	
	

	while (!SortedListIsIterEqual(to, from) &&
			(0 != list->cmp_func(SortedListGetData(from), data)))
	{
		from = SortedListNext(from);
	}
	
	return from;		
}


sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, 
    sorted_list_iter_t to, sorted_list_is_match_func_t match_func, void *param)
{
	sorted_list_iter_t iter;
	dlist_iter_t dlist_from;
	dlist_iter_t dlist_to;

	assert(from.list == to.list);
	assert(IsFromBeforeTo(from, to));
	assert(NULL != match_func);

	
	dlist_from = SortedListIterToDListIter(from);
	dlist_to = SortedListIterToDListIter(to);

	iter.iter = DListFind(dlist_from, dlist_to, match_func, param);
	
	return iter;

}


int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to,
                 sorted_list_action_func_t action_func, void *param)
{
	dlist_iter_t dlist_from;
	dlist_iter_t dlist_to;
	
	assert(NULL != action_func);
	assert(from.list == to.list);
	assert(IsFromBeforeTo(from, to));

	dlist_from = SortedListIterToDListIter(from);
	dlist_to = SortedListIterToDListIter(to);
	
	return DListForEach(dlist_from, dlist_to, action_func, param);
}
	
	
int SortedListIsEmpty(const sorted_list_t *list)
{
	assert(list);
	
	return DListIsEmpty(list->dlist);
}
	
	
size_t SortedListCount(const sorted_list_t *list)
{
	assert(list);
	
	return DListCount(list->dlist);
}  


void *SortedListPopBack(sorted_list_t *list)
{
	assert(NULL != list);

	return (DListPopBack(list->dlist));
}


void *SortedListPopFront(sorted_list_t *list)
{
	assert(NULL != list);

	return (DListPopFront(list->dlist));
}


void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	sorted_list_iter_t from_src;
	sorted_list_iter_t to_src;
	sorted_list_iter_t runner_dest;
    
	assert(dest);
	assert(src);
    
	runner_dest = SortedListBegin(dest);
    
	while (!SortedListIsEmpty(src))
	{
		from_src = SortedListBegin(src);
        
		while (!SortedListIsIterEqual(runner_dest, SortedListEnd(dest)) &&
                        dest->cmp_func(SortedListGetData(runner_dest),
                        SortedListGetData(from_src)) <= 0)
		{
			runner_dest = SortedListNext(runner_dest);
		}
        
		if (SortedListIsIterEqual(runner_dest, SortedListEnd(dest)))
		{
			DListSplice(SortedListIterToDListIter(SortedListBegin(src)),
					SortedListIterToDListIter(SortedListEnd(src)),
					SortedListIterToDListIter(SortedListEnd(dest)));
		}
		
		else
		{
			to_src = SortedListNext(from_src);
        
			while (!SortedListIsIterEqual(to_src, SortedListEnd(src)) &&
                   		0 < dest->cmp_func(SortedListGetData(runner_dest),
                  					  SortedListGetData(to_src)))
		{
			to_src = SortedListNext(to_src);
		}
        
		DListSplice(SortedListIterToDListIter(from_src),
		 SortedListIterToDListIter(to_src), SortedListIterToDListIter(runner_dest));
		}
	}
}

/*************************Iterator function impl*******************************/

sorted_list_iter_t SortedListBegin(const sorted_list_t *list)
{	
	assert(NULL != list);

	return DListIterToSortedListIter(DListBegin(list->dlist), list);
}


sorted_list_iter_t SortedListEnd(const sorted_list_t *list)
{
	assert(NULL != list);

	return DListIterToSortedListIter(DListEnd(list->dlist), list);
}


void *SortedListGetData(sorted_list_iter_t iter)
{
	dlist_iter_t dlist_iter;


	dlist_iter = SortedListIterToDListIter(iter);
	
	return (DListGetData(dlist_iter));
}


sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{

#ifdef NDEBUG
	assert(iter.iter->next);
#endif	
	
	iter.iter = DListNext(iter.iter);
	
	return iter;
}


sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
	iter.iter = DListPrev(iter.iter);
	
	return iter;
}


int SortedListIsIterEqual(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{
	assert(iter1.iter);
	assert(iter2.iter);
	
	return DListIsIterEqual(SortedListIterToDListIter(iter1),
	                        SortedListIterToDListIter(iter2));
}
      	
/*************************Service function impl********************************/

static sorted_list_iter_t DListIterToSortedListIter(dlist_iter_t diter,
                                             const sorted_list_t *list)
{
	sorted_list_iter_t siter;
	siter.iter = diter;
#ifndef NDEBUG
	siter.list = (sorted_list_t *)list;
#endif
	(void)list;

	return siter;
}

static dlist_iter_t SortedListIterToDListIter(sorted_list_iter_t iter)
{
	return iter.iter;
}

#ifndef NDEBUG
static int IsFromBeforeTo(sorted_list_iter_t from, sorted_list_iter_t to)
{
	sorted_list_iter_t curr;
	sorted_list_iter_t end = SortedListEnd(from.list);

	curr = from;

	for (curr = from; !SortedListIsIterEqual(curr, end);
	     curr = SortedListNext(curr))
	{
		if (SortedListIsIterEqual(curr, to))
		{
			return 1;
		}
	}

	return SortedListIsIterEqual(curr, to);
}
#endif
