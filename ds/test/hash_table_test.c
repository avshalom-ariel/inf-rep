
#include <stdio.h> 				/*printf, FILE, flopen, flclose*/
#include <string.h> 			/*strcmp, strlen*/
#include <ctype.h>				/*toupper*/
#include <stddef.h> 			/*size_t*/
#include <stdlib.h>				/*malloc free*/
#include <assert.h>				/*assert*/
#include <math.h> 				/* pow */

#include <hash_table.h> 		/*typedefs HashTable function declaration*/
#include "test_utility.h" 		/*Test functions*/

#define ARRAY_SIZE 10000
#define DICTIONARY_SIZE 104335 	/*wc -l /usr/share/dict/words*/

static size_t HashFunc(const void *key);
static size_t SimpleHashFunc(const void *key);
static int CompFunc(const void *data, const void *key);
static int ActionFunc(void *data, void *params);

static void HashTableCreateDestroyTest(void);
static void HashTableInsertTest(void);
static void HashTableSizeInsertTest(void);
static void HashTableRemoveTest(void);
static void HashTableIsEmptyTest(void);
static void HashTableFindTest(void);
static void HashTableForEachTest(void);

static void HashTableStandardDeviationLoadTest(void);

static hash_table_t *LaodDictionary(char **ditionary_holder);
static int SpellCheck(void);


int main(void)
{
	HashTableCreateDestroyTest();
	HashTableInsertTest();
	HashTableSizeInsertTest();
	HashTableRemoveTest();
	HashTableIsEmptyTest();
	HashTableFindTest();
	HashTableForEachTest();

	HashTableStandardDeviationLoadTest();

	SpellCheck();

	Test();
	
	return 0;
}


/*****************************************/
/*			Test Functions				 */
/*****************************************/


void HashTableCreateDestroyTest(void)
{
	hash_table_t *table = HashTableCreate(HashFunc, CompFunc, ARRAY_SIZE);
	
	HashTableDestroy(table);
}

void HashTableInsertTest(void)
{
	hash_table_t *table = HashTableCreate(HashFunc, CompFunc, ARRAY_SIZE);
	
	char *data1 = "avshi\n math grade: 100\n physics grade: 100";
	char *key1 = "avshi";
	
	char *data2 = "shahar\n math grade: 50\n physics grade: 50";
	char *key2 = "shahar";
	
	TestSizeT("HashTableInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key1, data1));
	TestSizeT("HashTableInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key2, data2));
	
	HashTableDestroy(table);
}

void HashTableSizeInsertTest(void)
{
	hash_table_t *table = HashTableCreate(HashFunc, CompFunc, ARRAY_SIZE);
	
	char *data1 = "avshi\n math grade: 100\n physics grade: 100";
	char *key1 = "avshi";
	
	char *data2 = "shahar\n math grade: 50\n physics grade: 50";
	char *key2 = "shahar";
	
	char *data3 = "idan\n math grade: 70\n physics grade: 80";
	char *key3 = "idan";
	
	char *data4 = "oded\n math grade: 90\n physics grade: 10";
	char *key4 = "oded";
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableSize(table));
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key1, data1));
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 1, HashTableSize(table));
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key2, data2));
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 2, HashTableSize(table));
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key3, data3));
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 3, HashTableSize(table));
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key4, data4));
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 4, HashTableSize(table));
	
	HashTableDestroy(table);
}

void HashTableRemoveTest(void)
{
	hash_table_t *table = HashTableCreate(HashFunc, CompFunc, ARRAY_SIZE);
	
	char *data1 = "avshi\n math grade: 100\n physics grade: 100";
	char *key1 = "avshi";
	
	char *data2 = "shahar\n math grade: 50\n physics grade: 50";
	char *key2 = "shahar";
	
	char *data3 = "idan\n math grade: 70\n physics grade: 80";
	char *key3 = "idan";
	
	char *data4 = "oded\n math grade: 90\n physics grade: 10";
	char *key4 = "oded";
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableSize(table));
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key1, data1));
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 1, HashTableSize(table));
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key2, data2));
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 2, HashTableSize(table));
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key3, data3));
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 3, HashTableSize(table));
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key4, data4));
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 4, HashTableSize(table));
	
	HashTableRemove(table, key1);
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 3, HashTableSize(table));
	
	HashTableRemove(table, key2);
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 2, HashTableSize(table));
	
	HashTableRemove(table, key2);
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 2, HashTableSize(table));
	
	HashTableRemove(table, key3);
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 1, HashTableSize(table));
	
	HashTableRemove(table, key4);
	
	TestSizeT("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableSize(table));
	
	HashTableDestroy(table);
}

void HashTableIsEmptyTest(void)
{
	hash_table_t *table = HashTableCreate(HashFunc, CompFunc, ARRAY_SIZE);
	
	char *data1 = "avshi\n math grade: 100\n physics grade: 100";
	char *key1 = "avshi";
	
	char *data2 = "shahar\n math grade: 50\n physics grade: 50";
	char *key2 = "shahar";
	
	char *data3 = "idan\n math grade: 70\n physics grade: 80";
	char *key3 = "idan";
	
	char *data4 = "oded\n math grade: 90\n physics grade: 10";
	char *key4 = "oded";
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 1, HashTableIsEmpty(table));
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key1, data1));
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableIsEmpty(table));
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key2, data2));
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key3, data3));	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableInsert(table, key4, data4));
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableIsEmpty(table));
	
	HashTableRemove(table, key1);
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableIsEmpty(table));
	
	HashTableRemove(table, key2);
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableIsEmpty(table));
	
	HashTableRemove(table, key2);
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableIsEmpty(table));
	
	HashTableRemove(table, key3);
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 0, HashTableIsEmpty(table));
	
	HashTableRemove(table, key4);
	
	TestInt("HashTableSizeInsertTest", __FILE__, __LINE__, 1, HashTableIsEmpty(table));
	
	HashTableDestroy(table);
}

void HashTableFindTest(void)
{
	hash_table_t *table = HashTableCreate(HashFunc, CompFunc, ARRAY_SIZE);
	
	char *data1 = "avshi\n math grade: 100\n physics grade: 100";
	char *key1 = "avshi";
	
	char *data2 = "shahar\n math grade: 50\n physics grade: 50";
	char *key2 = "shahar";
	
	char *data3 = "idan\n math grade: 70\n physics grade: 80";
	char *key3 = "idan";
	
	char *data4 = "oded\n math grade: 90\n physics grade: 10";
	char *key4 = "oded";
	
	char *key_not_in = "eviatar";
	
	TestSizeT("HashTableFindTest", __FILE__, __LINE__, 0, HashTableInsert(table, key1, data1));
	TestSizeT("HashTableFindTest", __FILE__, __LINE__, 0, HashTableInsert(table, key2, data2));
	TestSizeT("HashTableFindTest", __FILE__, __LINE__, 0, HashTableInsert(table, key3, data3));	
	TestSizeT("HashTableFindTest", __FILE__, __LINE__, 0, HashTableInsert(table, key4, data4));
	
	TestInt("HashTableFindTest", __FILE__, __LINE__, 0, strcmp(data1, HashTableFind(table, key1)));
	TestInt("HashTableFindTest", __FILE__, __LINE__, 0, strcmp(data2, HashTableFind(table, key2)));
	TestInt("HashTableFindTest", __FILE__, __LINE__, 0, strcmp(data3, HashTableFind(table, key3)));
	TestInt("HashTableFindTest", __FILE__, __LINE__, 0, strcmp(data4, HashTableFind(table, key4)));
	
	TestInt("HashTableFindTest", __FILE__, __LINE__, 1, NULL == HashTableFind(table, key_not_in));

	HashTableDestroy(table);
}

void HashTableForEachTest(void)
{
	hash_table_t *table = HashTableCreate(HashFunc, CompFunc, ARRAY_SIZE);
	
	char data1[100] = "avshi\nmath grade: 100\nphysics grade: 100";
	char key1[100] = "avshi";
	
	char data2[100] = "shahar\nmath grade: 50\nphysics grade: 50";
	char key2[100] = "shahar";
	
	char data3[100] = "idan\nmath grade: 70\nphysics grade: 80";
	char key3[100] = "idan";
	
	char data4[100] = "oded\nmath grade: 90\nphysics grade: 10";
	char key4[100] = "oded";
	
	char result1[100] = "Avshi\nmath grade: 100\nphysics grade: 100";
	char result2[100] = "Shahar\nmath grade: 50\nphysics grade: 50";
	char result3[100] = "Idan\nmath grade: 70\nphysics grade: 80";
	char result4[100] = "Oded\nmath grade: 90\nphysics grade: 10";
	
	char param[100] = "A";
	
	TestInt("HashTableForEachTest", __FILE__, __LINE__, 0, HashTableInsert(table, key1, data1));
	TestInt("HashTableForEachTest", __FILE__, __LINE__, 0, HashTableInsert(table, key2, data2));
	TestInt("HashTableForEachTest", __FILE__, __LINE__, 0, HashTableInsert(table, key3, data3));	
	TestInt("HashTableForEachTest", __FILE__, __LINE__, 0, HashTableInsert(table, key4, data4));

	TestInt("HashTableForEachTest", __FILE__, __LINE__, 0, HashTableForEach(table, ActionFunc, param));

	TestInt("HashTableForEachTest", __FILE__, __LINE__, 0, strcmp(data1, result1));
	TestInt("HashTableForEachTest", __FILE__, __LINE__, 0, strcmp(data2, result2));
	TestInt("HashTableForEachTest", __FILE__, __LINE__, 0, strcmp(data3, result3));
	TestInt("HashTableForEachTest", __FILE__, __LINE__, 0, strcmp(data4, result4));
	
	HashTableDestroy(table);
}


/*****************************************/
/*			  Dictionary Task		     */
/*****************************************/


hash_table_t *LaodDictionary(char **ditionary_holder)
{
	hash_table_t *dictionary = HashTableCreate(HashFunc, CompFunc, ARRAY_SIZE);
	char word[100] = {0};
	size_t i = 0;
	FILE *file = fopen("/usr/share/dict/words", "r");
    if (file == NULL) 
    {
        printf("file loading failed!");
		return NULL;
    }
    
    while (fgets(word, sizeof(word), file) != NULL) 
    {
/*      Remove newline character if present*/
        if (word[strlen(word) - 1] == '\n')
        {
            word[strlen(word) - 1] = '\0';
        }
        
        ditionary_holder[i] = (char *)calloc(strlen(word) + 1, sizeof(char));
        
        strncpy(ditionary_holder[i], word, strlen(word));
        
        HashTableInsert(dictionary, ditionary_holder[i], ditionary_holder[i]);
        
        ++i;
    }

    fclose(file);
    
	return dictionary;
}


int SpellCheck(void)
{
	char **ditionary_holder = (char **)calloc(DICTIONARY_SIZE, sizeof(char *));
	hash_table_t *dictionary = LaodDictionary(ditionary_holder);
	char str_to_check[100] = {0};
	size_t i = DICTIONARY_SIZE - 1;
	
	printf("To leave SpellChecker inter '`'\n");
	while ('`' != *str_to_check)
	{
		fgets(str_to_check, sizeof(str_to_check), stdin);
/*      Remove newline character if present*/
		if (str_to_check[strlen(str_to_check) - 1] == '\n') 
        {
            str_to_check[strlen(str_to_check) - 1] = '\0';
        }
		
		if(NULL != HashTableFind(dictionary, str_to_check))
		{
			printf("In Dictionary\n"); 
		}
		else
		{
			printf("Not In Dictionary!\n"); 
		}
	}
	
	while (0 < i)
	{
		free(*(ditionary_holder + i));
		--i;
	}
	
	free(*(ditionary_holder + i));
	free(ditionary_holder);

   	HashTableDestroy(dictionary);

	return 0;
}


/*****************************************/
/*			  Advanced Task  			 */
/*****************************************/


void HashTableStandardDeviationLoadTest(void)
{
	hash_table_t *table = HashTableCreate(SimpleHashFunc, CompFunc, 4);
	
	char *data1 = "avshi\n math grade: 100\n physics grade: 100";
	int key1 = 0;
	
	char *data2 = "shahar\n math grade: 50\n physics grade: 50";
	int key2 = 1;
	
	char *data3 = "idan\n math grade: 70\n physics grade: 80";
	int key3 = 2;
	
	char *data4 = "oded\n math grade: 90\n physics grade: 10";
	int key4 = 3;
	
	char *data5 = "rina\n math grade: 100\n physics grade: 100";
	int key5 = 0;
	
	char *data6 = "yarden\n math grade: 50\n physics grade: 50";
	int key6 = 3;
	
	char *data7 = "jorge\n math grade: 70\n physics grade: 80";
	int key7 = 2;
	
	char *data8 = "itay\n math grade: 90\n physics grade: 10";
	int key8 = 3;
	
	TestInt("HashTableSDLoadTest", __FILE__, __LINE__, 0, HashTableInsert(table, &key1, data1));
	TestInt("HashTableSDLoadTest", __FILE__, __LINE__, 0, HashTableInsert(table, &key2, data2));
	TestInt("HashTableSDLoadTest", __FILE__, __LINE__, 0, HashTableInsert(table, &key3, data3));	
	TestInt("HashTableSDLoadTest", __FILE__, __LINE__, 0, HashTableInsert(table, &key4, data4));
	TestInt("HashTableSDLoadTest", __FILE__, __LINE__, 0, HashTableInsert(table, &key5, data5));
	TestInt("HashTableSDLoadTest", __FILE__, __LINE__, 0, HashTableInsert(table, &key6, data6));
	TestInt("HashTableSDLoadTest", __FILE__, __LINE__, 0, HashTableInsert(table, &key7, data7));	
	TestInt("HashTableSDLoadTest", __FILE__, __LINE__, 0, HashTableInsert(table, &key8, data8));
	
	TestDouble("HashTableSDLoadTest", __FILE__, __LINE__, sqrt(0.5), HashTableStandardDeviation(table));	

	HashTableDestroy(table);
}


/*****************************************/
/*			Help Functions				 */
/*****************************************/


size_t HashFunc(const void *key)
{
	char *runner = (char *)key;
	size_t index = 0;
	
	while (*runner)
	{
		index += (size_t)(*runner);
		++runner;
	}
	
	return index % ARRAY_SIZE;
}

int CompFunc(const void *data, const void *key)
{
	char *data_runner = (char *)data;
	char *key_runner = (char *)key;
	int result = 1;
	
	if (!data || !key)
	{
		return -1;
	}
	
	while (*data_runner != '\n' && *key_runner != '\n' && *key_runner != '\0')
	{
		result *= (*data_runner == *key_runner);
		++data_runner;
		++key_runner;
	}
	
	return result;
}

int ActionFunc(void *data, void *params)
{
	if (!data || !params)
	{
		return -1;
	}
	
	*(char *)data = toupper(*(char *)data);
	
	return 0;
}

size_t SimpleHashFunc(const void *key)
{
	assert(key);
	
	return *(int *)key;
}


