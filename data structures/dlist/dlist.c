
/*
    Developer: Ofri Rozner
    Reviwer: Amitai Milshtain
    Date: 10/09/23
    dlist - src file
*/
    
/******************INCLUDES*************************/
#include <assert.h>  /* assert */
#include <stdlib.h> /* malloc */

#include "dlist.h" /* dlist API */

/******************STRUCTS*************************/
typedef struct dlist_node dlist_node_t;

struct dlist_node
{
	void *data;
	dlist_iter_t prev;
	dlist_iter_t next;
};

struct dlist
{
	struct dlist_node *head;
	struct dlist_node *tail;
};

/******************Service function decleration*************************/
#ifdef DEBUG 
static int IsFromSameList(dlist_iter_t from, dlist_iter_t to);
static int IsOutsideRange(dlist_iter_t from, dlist_iter_t to,
                          dlist_iter_t where);
#endif 

static dlist_node_t *IterToNode(dlist_iter_t iter);
static dlist_iter_t NodeToIter(dlist_node_t *node);
static struct dlist_node *CreateNode
			     (void *data, dlist_iter_t prev, dlist_iter_t next);  

/****************************Implementation*****************************/

dlist_t *DListCreate()
{
	struct dlist_node *dummy_head = NULL;
	struct dlist_node *dummy_tail = NULL;
	
	dlist_t *dlist = (dlist_t *)malloc(sizeof(dlist_t));
	if (NULL == dlist)
	{
		return NULL;
	}
	
	dummy_head = CreateNode(NULL, NULL, NULL);
	if (NULL == dummy_head)
	{
		free(dlist);
		return NULL;
	}
	
	dummy_tail = CreateNode(NULL, NULL, NULL);
	if (NULL == dummy_tail)
	{
		free(dummy_head);
		free(dlist);
		return NULL;
	}
	
	dlist->head = dummy_head;
	dlist->tail = dummy_tail;
	
	dlist->head->next = dlist->tail;
	dlist->tail->prev = dlist->head;
	
	return dlist;
}


void DListDestroy(dlist_t *list)
{
	dlist_iter_t node_to_delete = NULL;
	dlist_iter_t node_to_delete_next = NULL;

	assert(list);

	node_to_delete = list->head;
	node_to_delete_next = list->head;

	while (node_to_delete != list->tail)
	{
		node_to_delete_next = DListNext(node_to_delete);
		free(node_to_delete);
		node_to_delete = node_to_delete_next;
	}
	
	free(list->tail);
	node_to_delete = NULL;
	
	free(list);
	list = NULL;
}


dlist_iter_t DListInsertBefore(dlist_t *list, dlist_iter_t where, void *data)
{
	struct dlist_node *new_node = NULL;
	dlist_iter_t prev_node = NULL;
	
	assert(list);
	assert(where);
	assert(data);
	
	prev_node = DListPrev(where);
	new_node = CreateNode(data, prev_node, where);
	if (NULL == new_node)
	{
		return list->tail;
	}
					
	where->prev = new_node;
	prev_node->next = new_node;
	
	return new_node;
}


dlist_iter_t DListRemove(dlist_iter_t iter)
{
	dlist_iter_t prev_iter = NULL;
	dlist_iter_t next_iter = NULL;

	assert(iter);
	/*assert(NULL != DListNext(iter));
	assert(NULL != DListPrev(iter));*/
	
	prev_iter = DListPrev(iter);
	next_iter = DListNext(iter);
	
	prev_iter->next = next_iter;
	next_iter->prev = prev_iter;
	
	free(iter);
	iter = NULL;

	return next_iter;
} 


size_t DListCount(const dlist_t *list)
{
	size_t count = 0;
	dlist_iter_t runner = DListBegin(list);
	
	while (DListEnd(list) != runner)
	{
		++count;
		runner = DListNext(runner);
	}
	
	return count;
}


dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to,
                       dlist_is_match_func_t match_func, void *param)
{
	assert(NULL != match_func);
	assert(NULL != from);
	assert(NULL != to);    

	while (from != to)
	{
		if (match_func(from->data, param))
		{
			return from;
		}
		
	from = DListNext(from);
	}
	
	return to;
}


int DListMultiFind(dlist_iter_t from, dlist_iter_t to, 
           dlist_is_match_func_t match_func, void *param, dlist_t *output_list)
{
	size_t counter = 0;
	dlist_iter_t statues = 0;
    
	assert((size_t)(to - from) <= sizeof(output_list));
	assert(NULL != match_func);
	assert(NULL != from);
	assert(NULL != to);    
    
	while (from != to )
	{
		from = DListFind(from, to, match_func, (void*)param);
		if (from != to)
		{
			statues = DListPushBack(output_list, DListGetData(from));
			if(NULL == statues)
			{
				return -1;
			}
			
			++counter;
			from = DListNext(from);
		}
	}
	
		return counter;
}


int DListForEach(dlist_iter_t from, dlist_iter_t to,
       		          dlist_action_func_t action_func, void *param) 
{
	int func_status = 0;
	
	assert(from);
	assert(to);
	assert(action_func);
	#ifdef DEBUG
	assert(IsFromSameList(from, to));
	#endif

	while ((!DListIsIterEqual(from, to)) && (0 == func_status))
	{
		func_status = action_func(DListGetData(from), param);
		from = DListNext(from);
	}
	
	return func_status;
}


dlist_iter_t DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where)			  
{	
	dlist_node_t *to_prev_node = NULL;
	dlist_node_t *from_node = NULL;
	dlist_node_t *to_node = NULL;
	dlist_node_t *where_node = NULL;


	assert(NULL != IterToNode(from));
	assert(NULL != IterToNode(to));
	assert(NULL != IterToNode(where));

	#ifdef DEBUG
	assert(IsFromSameList(from, to));
	assert(IsOutsideRange(from, to, where));
	#endif

	from_node = IterToNode(from);
	to_node = IterToNode(to);
	where_node = IterToNode(where);
	to_prev_node = to_node->prev;

	from_node->prev->next = to_node;
	to_prev_node = to_node->prev;
	to_node->prev = from_node->prev;

	where_node->prev->next = from_node;
	from_node->prev = where_node->prev;
	where_node->prev = to_prev_node;
	to_prev_node->next = where_node;

	return NodeToIter(where_node->prev);
}


void *DListPopBack(dlist_t *list)
{
	void *data = list->tail->prev->data;
	DListRemove(list->tail->prev);
	
	return data;
}


void *DListPopFront(dlist_t *list)
{
	void *data = DListBegin(list)->data;
	DListRemove(DListBegin(list));
	
	return data;
}


dlist_iter_t DListPushBack(dlist_t *list, void *data)
{
	assert(list);
	
	return (DListInsertBefore(list, list->tail, data));
}


dlist_iter_t DListPushFront(dlist_t *list, void *data)
{
	assert(list);
	
	return (DListInsertBefore(list, list->head->next, data));
}

/*********************Iter functions*****************************/	

dlist_iter_t DListNext(dlist_iter_t iter)
{
	assert(iter);
	
	return iter->next;
}


dlist_iter_t DListPrev(dlist_iter_t iter)
{
	assert(iter);
	
	return iter->prev;
}


void *DListGetData(dlist_iter_t iter)
{
	assert(iter);

	return iter->data;
}


dlist_iter_t DListSetData(dlist_iter_t iter, void *data)
{
	assert(iter);

	iter->data = data;
	
	return iter;
}


int DListIsIterEqual(dlist_iter_t iter1, dlist_iter_t iter2)
{
	assert(iter1);
	assert(iter2);
	
	return (iter1 == iter2);
}


dlist_iter_t DListBegin(const dlist_t *list)
{
	assert(list);
	
	return list->head->next;
}


dlist_iter_t DListEnd(const dlist_t *list)
{
	assert(list);
	
	return list->tail;
}


int DListIsEmpty(const dlist_t *list)
{
	assert(NULL != list);

	return DListIsIterEqual(DListBegin(list), DListEnd(list));
}


/*********************Service function impl*****************************/

static struct dlist_node *CreateNode
				(void *data, dlist_iter_t prev, dlist_iter_t next)
{
	struct dlist_node *new_node = 
	                 (struct dlist_node *)malloc(sizeof(struct dlist_node));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->prev = prev;
	new_node->next = next;
	
	return new_node;
}

static dlist_node_t *IterToNode(dlist_iter_t iter)
{	
	return ((dlist_node_t *)iter);
}

static dlist_iter_t NodeToIter(dlist_node_t *node)
{
	assert(NULL != node);

	return ((dlist_iter_t)node);
}


#ifdef DEBUG

static int IsFromSameList(dlist_iter_t from, dlist_iter_t to)
{
	int is_in_list = 0;
	dlist_node_t *curr =IterToNode(from); 
	dlist_node_t *to_node = IterToNode(to);
	
	while ((NULL != curr) && !(is_in_list = (curr == to_node)))
	{
		curr = DListNext(curr);
	}
	
	return is_in_list; 
}

static int IsOutsideRange(dlist_iter_t from, dlist_iter_t to,
                          dlist_iter_t where)
{
	int is_outside_range = 1;
	dlist_iter_t curr;

	assert(NULL != IterToNode(from));
	assert(NULL != IterToNode(to));
	assert(NULL != IterToNode(where));

	curr = from;

	while (!(DListIsIterEqual(to, curr)) && (is_outside_range = (!(DListIsIterEqual(curr,where)))))
	{
		curr = DListNext(curr);
	}

	return is_outside_range;
}

#endif 

