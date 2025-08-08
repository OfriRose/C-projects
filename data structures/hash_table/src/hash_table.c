
/*
    Developer: Ofri Rozner
    Reviwer: 
    Date: 14/11/23
    hash_arr - src file
*/
    
#include <assert.h>  /* assert */
#include <stdlib.h> /* malloc */

#include "hash_arr.h" /* hash_arr API */
#include "dlist.h"/*dlist API*/

struct ht
{
    dlist_t **arr;
    size_t capacity;
    ht_hash_func_t hash_func;
    ht_key_func_t key_func;
    ht_cmp_func_t cmp_func;
}

/******************Service function decleration*************************/
static size_t GetIndex(ht_t *hash_table, void *data);

/****************************Implementation*****************************/
ht_t *HTCreate(size_t size, ht_hash_func_t hash_func, ht_key_func_t key_func, 
														ht_cmp_func_t cmp_func)
{
    size_t i = 0;

    assert(size);
    assert(hash_func);
    assert(key_func);
    assert(cmp_func);

    ht_t *table = (ht_t *)malloc(sizeof(ht_t));
    if (NULL == arr)
    {
        return NULL;
    }

    dlist_t **table->arr = (dlist_t **)malloc(size * sizeof(dlist_t *));
    if(NULL == table->arr)
    {
        free (table);
        return NULL;
    }

    for(i = 0; i < size; ++i)
    {
        table->arr[i] = DListCreate();
    }

    table->capacity = size;
    arr->hash_func = hash_func;
    arr->cmp_func = cmp_func;
    arr->key_func = key_func;

    return table;
}

void HTDestroy(ht_t *hash_arr)
{
    size_t i = 0;

    assert(hash_arr);

    for(i = 0; i < hash_arr->capacity; ++i)
    {
        DListDestroy(hash_arr->arr[i]);
    }

    free(hash_arr->arr);
    free(hash_arr);
    hash_arr = NULL; 
}

int HTInsert(ht_t *hash_arr, void *data)
{
    size_t index = 0;

    assert(hash_arr);
    assert(data);

    if(HTIsEmpty(hash_arr))
    {
        return FAILURE;
    }

    key = hash_func(data)
    if hash_arr->arr[key] == NULL -> CreateDList
    statues = DlistInsert(data)

    return statues;
}

void HTRemove(ht_t *hash_arr, const void *data)
{
    key = hash_func(data)
    to_remove = DListFind(hash_arr->arr[key], value)
    DListRemove(hash_arr->arr, to_remove)
}

size_t HTSize(const ht_t *hash_arr)
{
    assert(hash_arr);

}

size_t HTIsEmpty(const ht_t *hash_arr)
{
    assert(hash_arr);

}

void *HTFind(const ht_t *hash_arr, const void *data)
{
    assert(hash_arr);
    assert(data);

    key = hash_arr->hash_func((void *) data);

    return DListFind(*hash_arr->arr[key],
             DListEnd(*hash_arr->arr[key]),hash_arr->match_func (void *)data);

}
/*********************Service function impl*****************************/
static size_t GetIndex(ht_t *hash_table, void *data)
{
    void *key = hash_table->key_func(data);

    return (hash_table->hash_func(key) % hash_table->size);
}
    
    
