
#include <stdio.h>			/*printf*/
#include <stddef.h> 		/*size_t*/

#include "trie.h"			/*Typedefs, Function declarations*/
#include "test_utility.h"	/*Test Functions*/

#define BYTES_IN_ADD 4

static void TrieCreateDestroyTest(void);
static void TrieInsertTest(void);
static void TrieRemoveTest(void);
static void TrieSearchTest(void);
static void TrieLeafCountTest(void);

static void PrintAdd(unsigned char *add);

int main(void)
{
	TrieCreateDestroyTest();
	TrieInsertTest();
	TrieRemoveTest();
	TrieSearchTest();
	TrieLeafCountTest();
	
	
	Test();
	
	return 0;
}


/********************************************/
/*			   Test Functions				*/
/********************************************/


void TrieCreateDestroyTest(void)
{
	trie_t *trie = TrieCreate(8);
	
	TrieDestroy(trie);
}


void TrieInsertTest(void)
{
	trie_t *trie = TrieCreate(8);
	unsigned char add[4] = {'7', '1', '2', '3'};
	unsigned char add_recieved1[4] = {'0', '1', '2', '3'};
	unsigned char add_recieved2[4] = {'0', '1', '2', '3'};
	unsigned char add_recieved3[4] = {'0', '1', '2', '3'};
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved1));
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved2));

	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved3));
	
	TrieDestroy(trie);
}


void TrieRemoveTest(void)
{
	trie_t *trie = TrieCreate(8);
	unsigned char add[4] = {'7', '1', '2', '3'};
	unsigned char add_recieved1[4] = {'0', '1', '2', '3'};
	unsigned char add_recieved2[4] = {'0', '1', '2', '3'};
	unsigned char add_recieved3[4] = {'0', '1', '2', '3'};
	unsigned char add_recieved4[4] = {'0', '1', '2', '3'};
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved1));
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved2));

	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieRemove(trie, add));
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved3));
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved4));
	
	TrieDestroy(trie);
}


void TrieSearchTest(void)
{
	trie_t *trie = TrieCreate(8);
	unsigned char add[4] = {'7', '1', '2', '3'};
	unsigned char add_recieved1[4] = {'0', '1', '2', '3'};
	unsigned char add_recieved2[4] = {'0', '1', '2', '3'};
	unsigned char add_recieved3[4] = {'0', '1', '2', '3'};
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_NOT_IN == TrieSearch(trie, add));
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved1));
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieSearch(trie, add));
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved2));

	TrieRemove(trie, add);
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_NOT_IN == TrieSearch(trie, add));
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved3));
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieSearch(trie, add));
	
	TrieDestroy(trie);
}

void TrieLeafCountTest(void)
{
	trie_t *trie = TrieCreate(8);
	unsigned char add[4] = {'7', '1', '2', '3'};
	unsigned char add_recieved1[4] = {'0', '1', '2', '3'};
	unsigned char add_recieved2[4] = {'0', '1', '2', '3'};
	unsigned char add_recieved3[4] = {'0', '1', '2', '3'};
	unsigned char add_recieved4[4] = {'0', '1', '2', '3'};

	TestSizeT("TrieLeafCountTest", __FILE__, __LINE__, 0, TrieLeafCount(trie));
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved1));
	
	TestSizeT("TrieLeafCountTest", __FILE__, __LINE__, 1, TrieLeafCount(trie));
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved2));
	
	TestSizeT("TrieLeafCountTest", __FILE__, __LINE__, 2, TrieLeafCount(trie));
	
	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved3));

	TestSizeT("TrieLeafCountTest", __FILE__, __LINE__, 3, TrieLeafCount(trie));

	TestInt("TrieSearchTest", __FILE__, __LINE__, 1, TRIE_SUCCESS == TrieInsert(trie, add, add_recieved4));

	TestSizeT("TrieLeafCountTest", __FILE__, __LINE__, 4, TrieLeafCount(trie));

	TrieDestroy(trie);

}


/********************************************/
/*			   Help Functions				*/
/********************************************/


void PrintAdd(unsigned char *add)
{
	size_t i = 0;
	
	for (; i < BYTES_IN_ADD; ++i)
	{
		printf("%c. ", *add);
		++add;
	}
	
	printf("\n");
}













