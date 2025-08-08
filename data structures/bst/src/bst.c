/*
    Developer: Ofri Rozner
    Reviwer: Mentor
    Date: 24/10/23
    bst - src file
*/
    
#include <assert.h>  /* assert */
#include <stdlib.h> /* malloc */

#include "bst.h" /* bst API */

#define GET_ROOT bst->root_stub

enum {
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

struct bst
{
    bst_node_t *root_stub;
    bst_cmp_func_t cmp_func;
};

struct bst_node
{
    void *data;  
    bst_node_t *parent;
    bst_node_t *children[NUM_OF_CHILDREN];
};


/******************Service function decleration*************************/
static bst_node_t *CreateNode(void *data, bst_node_t *parent);
static bst_iter_t NodeToIter(bst_node_t *node);
static bst_node_t *IterToNode(bst_iter_t iter);
static int IsLeaf(bst_node_t *node);
bst_iter_t InOrderIter(bst_iter_t iter, int direction);

/****************************Implementation*****************************/
bst_t *BSTCreate(bst_cmp_func_t cmp_func)
{
    bst_node_t *root;
    size_t max_value = (-1);

    bst_t *new_bst = (bst_t *)malloc(sizeof(bst_t));
    if (NULL == new_bst)
    {
        return NULL;
    }

    root = CreateNode(&max_value, NULL);
    if (NULL == root)
    {
        free(new_bst);
        return NULL;
    }

    new_bst->root_stub = root;
    new_bst->cmp_func = cmp_func;

    return new_bst;
}


void BSTDestroy(bst_t *bst)
{
    bst_node_t *current = NULL;
    bst_node_t *curr_parent = NULL;

    assert(bst);

    current = GET_ROOT;

    while (!BSTIsEmpty(bst)) 
    {
        if (NULL != current->children[LEFT])
        {
            current = current->children[LEFT];
        }
        else if (NULL != current->children[RIGHT])
        {
            current = current->children[RIGHT];
        }
        else
        {
            curr_parent = current->parent;            
            curr_parent->children[NULL == current->parent->children[LEFT]] = NULL;

            free(current);
            current = curr_parent;
        }        
    }

    free(bst->root_stub);
    bst->root_stub = NULL;

    free(bst);
    bst = NULL;
}

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
    bst_node_t *current = NULL;
    bst_node_t *new_node = NULL;
    int res = 0;

    assert(bst);

    current = GET_ROOT;

    while (NULL != current->children[res > 0])
    {
        current = current->children[res > 0];
        res = bst->cmp_func(data, current->data);   

        assert (0 != res);
    }

    new_node = CreateNode(data, current);
    if (NULL == new_node)
    {
        return BSTEnd(bst);
    }

    current->children[res > 0] = new_node;

    return NodeToIter(new_node);
}

void BSTRemove(bst_iter_t iter)
{
    bst_node_t *node_to_remove;
    bst_node_t *parent;
    bst_node_t *left_child;
    bst_node_t *right_child;
    bst_node_t *runner;

    assert(iter);

    node_to_remove = IterToNode(iter);
    parent = node_to_remove->parent;
    left_child = node_to_remove->children[LEFT];
    right_child = node_to_remove->children[RIGHT];
    runner = right_child;

    parent->children[LEFT] = right_child;

    if (IsLeaf(node_to_remove))
    {
        if (parent->children[LEFT] == node_to_remove)
        {
            parent->children[LEFT] = NULL;
        }
        else
        {
            parent->children[RIGHT] = NULL;
        }
    }
    else if (!IsLeaf(node_to_remove)) 
    {
        if (NULL != right_child)
        {
            right_child->parent = parent;
        }
        else
        {
            runner = parent;
        }

        while (NULL != runner->children[LEFT])
        {
            runner = runner->children[LEFT];    
        }

        left_child->parent = runner;
        runner->children[LEFT] = left_child;
    }


    free(node_to_remove);
}

int BSTForEach(bst_iter_t from, bst_iter_t to,
               bst_callback_t callback_func, void *param)
{	
	int func_status = 0;
	
	assert(from);
	assert(to);
	assert(callback_func);

	while ((!BSTIterIsEqual(from, to)) && (0 == func_status))
	{
		func_status = callback_func((void *)BSTIterGetData(from), param);
		from = BSTNext(from);
	}
	
	return func_status;
}

bst_iter_t BSTBegin(bst_t *bst)
{
    bst_node_t *current = GET_ROOT;
    while (current->children[LEFT] != NULL)
    {
        current = current->children[LEFT];
    }

    return NodeToIter(current);
}

bst_iter_t BSTEnd(bst_t *bst)
{
    return NodeToIter(bst->root_stub);
}

void *BSTIterGetData(bst_iter_t iter)
{
    bst_node_t *node = NULL;

	assert(iter);

    node = IterToNode(iter);

	return node->data;
}
    
int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	return (iter1 == iter2);
}

size_t BSTSize(bst_t* bst)
{
    size_t size = 0;
    bst_iter_t current;

    assert(bst);

    current = BSTBegin(bst);
    while (!BSTIterIsEqual(current, BSTEnd(bst)))
    {
        ++size;
        current = BSTNext(current);
    }

    return size;
}

int BSTIsEmpty(bst_t *bst)
{    
    assert(bst);

    return (NULL == GET_ROOT->children[LEFT]);
}

bst_iter_t BSTNext(bst_iter_t iter)
{
    assert(iter);

    return InOrderIter(iter, RIGHT);
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
    assert(iter);

    return InOrderIter(iter, LEFT);
}

bst_iter_t BSTFind(const bst_t *bst, void *data) 
{
    bst_node_t *current;
    int cmp_result = 0;

    assert(bst);
    assert(data);

    current = GET_ROOT;
    current = current->children[LEFT];

    while (current != NULL)
    {
        cmp_result = bst->cmp_func(current->data, data);

        if (0 == cmp_result)
        {
            return NodeToIter(current);
        }
            current = current->children[cmp_result < 0];
    }

    return NodeToIter(bst->root_stub);
}

/*********************Service function impl*****************************/
 static bst_node_t *CreateNode(void *data, bst_node_t *parent)
{
    bst_node_t *new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
    if (NULL == new_node)
    {
        return NULL;
    }

    new_node->data = data;
    new_node->parent = parent;
    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;

    return new_node;
}

bst_iter_t InOrderIter(bst_iter_t iter, int direction)
{
    bst_node_t *node = NULL;

    assert(iter);

    node = IterToNode(iter);

    if (node->children[direction] != NULL) 
    {
        node = node->children[direction];

        while (node->children[!direction] != NULL) 
        {
            node = node->children[!direction];
        }
    }
    else 
    {
        while (node->parent != NULL && node == node->parent->children[direction]) 
        {
            node = node->parent;
        }

        node = node->parent;
    }

    return NodeToIter(node);
}

static int IsLeaf(bst_node_t *node)
{
    return (NULL == node->children[RIGHT]) && (NULL == node->children[LEFT]);
}

static bst_iter_t NodeToIter(bst_node_t *node)
{
    return ((bst_iter_t)node);
}

static bst_node_t *IterToNode(bst_iter_t iter)
{
    return ((bst_node_t *)iter);
}

