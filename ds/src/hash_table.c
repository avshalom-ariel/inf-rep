/*
Name: Avshalom Ariel
Reveiwer: Or
Date: 30/06/2024
status: Approved
*/

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* size_t malloc free */
#include <math.h> 		/* pow */

#include "hash_table.h" /* hashtable typedefs, hashtable function declarations */
#include "dllist.h"		/* dll typedefs, dll function calarations */

struct hash_table
{
	size_t hash_table_size;
	hash_func_t hash_func;
	hash_cmp_func_t cmp_func;
	dll_t **hash_table;
};


/********************************************/
/*			   API Functions				*/
/********************************************/


hash_table_t *HashTableCreate(hash_func_t hash_func, hash_cmp_func_t cmp_func, size_t hash_table_size)
{
	hash_table_t *hash = NULL;
	dll_t **bucket_runner = NULL;
	
	assert(hash_func);
	assert(cmp_func);
	assert(hash_table_size);
	
	hash = (hash_table_t *)malloc(sizeof(hash_table_t));
	if(!hash)
	{
		return NULL;
	}
	
	hash->hash_table = (dll_t **)malloc(hash_table_size * sizeof(dll_t *));
	if(!hash->hash_table)
	{
		free(hash);
		return NULL;
	}

	bucket_runner = hash->hash_table;
	
	while (bucket_runner < hash->hash_table + hash_table_size)
	{
		*bucket_runner = DLListCreate();
		if(!*bucket_runner)
		{
			hash->hash_table_size = (size_t)bucket_runner % (size_t)(hash->hash_table);
			HashTableDestroy(hash);
			return NULL;
		}
		
		++bucket_runner;
	}
	
	hash->hash_table_size = hash_table_size;
	hash->hash_func = hash_func;
	hash->cmp_func = cmp_func;
	
	return hash;
}

void HashTableDestroy(hash_table_t *table)
{
	dll_t **bucket_runner = NULL;
	
	assert(table);
	
	bucket_runner = table->hash_table;

	while (bucket_runner < table->hash_table + table->hash_table_size)
	{	
		DLListDestroy(*bucket_runner);
		
		++bucket_runner;
	}	
	
	free(table->hash_table);
	free(table);
}

int HashTableInsert(hash_table_t *table, const void *key, void *data)
{
	size_t index = 0;
	dll_iterator_t iter = {0};
	
	assert(table);
	assert(table->hash_func);
	assert(table->hash_table);
	assert(key);
	
	index = table->hash_func(key) % table->hash_table_size;
	iter = DLListBegin(*(table->hash_table + index));
	
	iter = DLListInsert(*(table->hash_table + index), iter, data);
	if(DLListIsEqualIter(iter, DLListEnd(*(table->hash_table + index))))
	{
		return 1;
	}
	
	return 0;
}

void HashTableRemove(hash_table_t *table, const void *key)
{
	size_t index = 0;
	dll_iterator_t iter = NULL;
	
	assert(table);
	
	index = table->hash_func((void *)key) % table->hash_table_size;
	
	iter = DLListFind(DLListBegin(*(table->hash_table + index)),
					  DLListEnd(*(table->hash_table + index)), (void *)key ,table->cmp_func);
						   
	if(DLListIsEqualIter(iter, DLListEnd(*(table->hash_table + index))))
	{
		return;
	}
	
	DLListRemove(iter);
}

size_t HashTableSize(const hash_table_t *table)
{
	dll_t **bucket_runner = NULL;
	size_t count = 0;
	
	assert(table);
	
	bucket_runner = table->hash_table;
	
	while (bucket_runner < table->hash_table + table->hash_table_size)
	{
		count += DLListCount(*bucket_runner);
		
		++bucket_runner;
	}
	
	return count;
}

int HashTableIsEmpty(const hash_table_t *table)
{
	dll_t **bucket_runner = NULL;
	
	assert(table);
	
	bucket_runner = table->hash_table;
	
	while(bucket_runner < table->hash_table + table->hash_table_size && 
													DLListIsEmpty(*bucket_runner))
	{
		++bucket_runner;
	}
	
	return table->hash_table + table->hash_table_size == bucket_runner;
}

void *HashTableFind(const hash_table_t *table, const void *key)
{
	size_t index = 0;
	dll_iterator_t iter = NULL;
	void *data_holder = NULL;
	
	assert(table);
	
	index = table->hash_func((void *)key) % table->hash_table_size;
	
	iter = DLListFind(DLListBegin(*(table->hash_table + index)), DLListEnd(*(table->hash_table + index)),
					  (void *)key, table->cmp_func);
						   
	if((DLListIsEqualIter(iter, DLListEnd(*(table->hash_table + index)))))
	{
		return NULL;
	}
	
	data_holder = DLListGetData(iter);
	
	iter = DLListInsert(*(table->hash_table + index), DLListBegin(*(table->hash_table + index)), data_holder);
	
	if(!(DLListIsEqualIter(iter, DLListEnd(*(table->hash_table + index)))))
	{		
		DLListRemove(iter);
	}
	
	return data_holder;
}

int HashTableForEach(hash_table_t *table, hash_action_func_t action, void *params)
{
	dll_t **bucket_runner = NULL;
	int status = 0;
	dll_iterator_t iter = NULL;
	
	assert(table);
	assert(action);
	
	bucket_runner = table->hash_table;
	
	while (bucket_runner < table->hash_table + table->hash_table_size && 0 == status)
	{	
		iter = DLListForEach(DLListBegin(*bucket_runner),
							   DLListEnd(*bucket_runner),  params, action);
		
		status = !DLListIsEqualIter(iter, DLListEnd(*bucket_runner));
		
		++bucket_runner;
	}
	
	return status;
}


/********************************************/
/*			   Help Functions				*/
/********************************************/


double HashTableLoad(const hash_table_t *table)
{
	double num_of_elements = 0;
	double num_of_buckets = 0;
	
	assert(table);
	
	num_of_elements = (double)HashTableSize(table);
	num_of_buckets = (double)table->hash_table_size;
	
	return num_of_elements / num_of_buckets;
}

double HashTableStandardDeviation(const hash_table_t *table)
{
	dll_t **bucket_runner = NULL;
	double variance = 0;
	double standard_deviation = 0;
	double avgrage = HashTableLoad(table);
	
	assert(table);
	
	bucket_runner = table->hash_table;
	
	while (bucket_runner < table->hash_table + table->hash_table_size)
	{
		variance += pow((DLListCount(*bucket_runner) - avgrage), 2);
		
		++bucket_runner;
	}

	standard_deviation = sqrt(variance / table->hash_table_size);
	
	return standard_deviation;
}


