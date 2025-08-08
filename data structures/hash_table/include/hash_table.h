/* -------------------------------------------------------------------------- *
 * FILE:        HASH_TABLE.H                                                  *
 * AUTHOR:      OFRI ROZNER                                                   *
 * REVIEWER:                                                                  *
 * DATE:        13.11.2023                                                    *
 * LAB:         OL-149                                                        *
 * DESCRIPTION: API HASH_TABLE                                                *
 * -------------------------------------------------------------------------- */

/* ------------------------- Preprocessor Directives ------------------------ */

#ifndef __ILRD_OL149_H_HASHTABLE__
#define __ILRD_OL149_H_HASHTABLE__

#include <stddef.h> 	/* size_t */

/* ---------------------------- Type Definitions ---------------------------- */

typedef struct ht ht_t;

typedef size_t (*ht_hash_func_t)(const void *key);
typedef void *(*ht_key_func_t)(void *data);
typedef int (*ht_cmp_func_t)(const void *test_data, const void *base_data);

typedef int (*ht_callback_t)(void *data, void *param);

/* -------------------------- Function Declarations ------------------------- */

/** 
 * complexity: Time O(1), Space O(n)
 */
ht_t *HTCreate(size_t size, ht_hash_func_t hash_func, ht_key_func_t key_func, 
														ht_cmp_func_t cmp_func);

/** 
 * complexity: Time O(n), Space O(1)
 */
void HTDestroy(ht_t *hash_table);

/** 
 * complexity: Time avg: O(n) worst: O(n), Space  O(1)
 */
int HTInsert(ht_t *hash_table, void *data);

/** 
 * complexity: Time O(1), Space O(1)
 */
void HTRemove(ht_t*hash_table, const void *data);

/** 
 * complexity: Time avg: O(n) worst: O(n), Space  O(1)
 */
void *HTFind(const ht_t *hash_table, const void *data);

/** 
 * complexity: Time O(1), Space O(1)
 */
size_t HTSize(const ht_t *hash_table);

/** 
 * complexity: Time O(1), Space O(1)
 */
size_t HTIsEmpty(const ht_t *hash_table);

/** 
 * complexity: Time O(n), Space O(1)
 */
int HTForEach(ht_t *hash_table, ht_callback_t callback_func, void *param);


#endif /* __ILRD_OL149_H_AVL__ */
