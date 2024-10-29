
#include <stddef.h>		/*size_t*/
#include <stdlib.h>		/*malloc free*/
#include <string.h>		/*memcpy*/
#include <assert.h> 	/*assert*/
#include <stdio.h>		/*printf for visualization*/

#include <stdbool.h> 	/*bool*/

#include "trie.h" 		/*typedefs, function declarations*/

#define BITS_IN_BYTE 8
#define BYTES_IN_ADD 4
#define NUM_OF_CHILDS 2
#define CHILD(node, direction) node->childs[direction]
#define TRUE 1
#define FALSE 0

typedef enum is_free
{
	FREE,
	NOT_FREE
}e_is_free_t;


typedef struct trie_node
{
	struct trie_node *childs[NUM_OF_CHILDS];
    unsigned int is_full;
}trie_node_t;

struct trie
{
	trie_node_t *root;
	size_t subnet_prefix;
};

/*static unsigned int BitsMirror(unsigned int num);*/
static void PostOrderFree(trie_node_t *node);
static trie_node_t *CreateNode(void);
static void IsFullUpdate(trie_node_t *node);
static size_t LeafCountRecursion(trie_node_t *node);
static e_status_t RemoveRecursion(trie_node_t *parent, unsigned char *add, unsigned int level);
static e_status_t SearchRecursion(trie_node_t *parent, unsigned char *add, unsigned int level);
static e_status_t InsertRecursion(trie_node_t *parent, unsigned char *add, unsigned char *result, unsigned int level);

static int IsLeaf(trie_node_t *node);

/*static unsigned int FlipBytesInt(unsigned int bank);*/


/********************************************/
/*			   API Functions				*/
/********************************************/


trie_t *TrieCreate(size_t subnet_prefix)
{
	trie_t *trie = (trie_t *)malloc(sizeof(trie_t));
	if (!trie)
	{
		return NULL;
	}
	
	trie->root = CreateNode();
	if (!trie->root)
	{
		free(trie);
		return NULL;
	}
	
	trie->subnet_prefix = (unsigned int)subnet_prefix;
	
	return trie;
}

void TrieDestroy(trie_t *trie)
{
	assert(trie);
	
	PostOrderFree(trie->root);
	
	free(trie);
}


e_status_t TrieInsert(trie_t* trie, unsigned char *requested_ip, unsigned char *received_ip)
{
	size_t subnet_in_bytes = (trie->subnet_prefix) / BITS_IN_BYTE;
	size_t tree_height = BITS_IN_BYTE * BYTES_IN_ADD;
	e_status_t status = 0;

	assert(trie);
	assert(requested_ip);
	
	if (trie->root->is_full)
	{
		return TRIE_DHCP_FULL;
	}
	
	status = InsertRecursion(trie->root, requested_ip +subnet_in_bytes, received_ip+subnet_in_bytes, tree_height - trie->subnet_prefix - 1);
	printf("\n");
	
	return status;
}


e_status_t TrieRemove(trie_t* trie, unsigned char *ip_to_free)
{
	size_t subnet_in_bytes = (trie->subnet_prefix) / BITS_IN_BYTE;
	size_t tree_height = BITS_IN_BYTE * BYTES_IN_ADD;
	e_status_t status = 0;
	
	assert(trie);
	assert(ip_to_free);
	
	status = RemoveRecursion(trie->root, ip_to_free + subnet_in_bytes, tree_height - trie->subnet_prefix - 1);
	
	return status;
}


e_status_t TrieSearch(trie_t* trie, unsigned char *ip_to_find)
{
	e_status_t status = 0;
	
	assert(trie);
	assert(ip_to_find);
	
	status = SearchRecursion(trie->root, ip_to_find, trie->subnet_prefix - 1);
	
	return status;
}


size_t TrieLeafCount(trie_t *trie)
{
	assert(trie);
	
	return LeafCountRecursion(trie->root);
}


/********************************************/
/*			   Help Functions				*/
/********************************************/


void PostOrderFree(trie_node_t *node)
{
	size_t i = 0;

	if(!node)
	{
		return;
	}
	
	for (; NUM_OF_CHILDS > i; ++i)
	{
		PostOrderFree(CHILD(node, i));
	}

	free(node);
}


trie_node_t *CreateNode(void)
{
	size_t i = 0;
	trie_node_t *new_node = (trie_node_t *)malloc(sizeof(trie_node_t));
	if (!new_node)
	{
		return NULL;
	}
	
	for (; i < NUM_OF_CHILDS; ++i)
	{
		CHILD(new_node, i) = NULL;
	}
	
	new_node->is_full = FALSE;
	
	return new_node;
}


e_status_t InsertRecursion(trie_node_t *parent, unsigned char *add, unsigned char *result, unsigned int level)
{	
	unsigned int direction = (*(unsigned int *)add >> level) & 1;
	
	e_status_t status = TRIE_SUCCESS;

	if (CHILD(parent, direction) && CHILD(parent, direction)->is_full)
	{
		direction = !direction;
	}

	if (!CHILD(parent, direction))
	{
		CHILD(parent, direction) = CreateNode();
		if (!CHILD(parent, direction))
		{
			return TRIE_MEMORY_FALIURE;
		}
	}
	printf("-> %d ", direction);
	*(unsigned int *)result |= direction << level;
	
	if (!level)
	{
		CHILD(parent, direction)->is_full = TRUE;
		return TRIE_SUCCESS;
	}

	status = InsertRecursion(CHILD(parent, direction), add, result, level - 1);
	
	IsFullUpdate(parent);
	IsFullUpdate(CHILD(parent, direction));
	
	return status;
}


e_status_t RemoveRecursion(trie_node_t *parent, unsigned char *add, unsigned int level)
{	
	unsigned int direction = (*(unsigned int *)add >> level) & 1;
	e_status_t status = TRIE_SUCCESS;

	if (!CHILD(parent, direction))
	{
		return TRIE_DOUBLE_FREE;
	}
	
	if (!level && TRUE == CHILD(parent, direction)->is_full)
	{
		CHILD(parent, direction)->is_full = FALSE;
		return TRIE_SUCCESS;
	}
	else if (!level && FALSE == CHILD(parent, direction)->is_full)
	{
		return TRIE_DOUBLE_FREE;
	}

/*	printf("-> %d, ", direction);*/
	status = RemoveRecursion(CHILD(parent, direction), add, level - 1);
	
	IsFullUpdate(parent);
	IsFullUpdate(CHILD(parent, direction));
	
	return status;
}


e_status_t SearchRecursion(trie_node_t *parent, unsigned char *add, unsigned int level)
{	
	unsigned int direction = (*(unsigned int *)add >> level) & 1;
	e_status_t status = TRIE_SUCCESS;

	if (!CHILD(parent, direction))
	{
		return TRIE_NOT_IN;
	}
	
	if (!level && TRUE == CHILD(parent, direction)->is_full)
	{
		return TRIE_SUCCESS;
	}
	else if (!level && FALSE == CHILD(parent, direction)->is_full)
	{
		return TRIE_NOT_IN;
	}

	status = SearchRecursion(CHILD(parent, direction), add, level - 1);
	
	return status;
}



size_t LeafCountRecursion(trie_node_t *node)
{
	size_t count = 0;
	size_t i = 0;

	if (IsLeaf(node) && node->is_full)
	{		
		return 1;
	}
	else if (IsLeaf(node) && !(node->is_full))
	{
		return 0;
	}
	
	for(; i < NUM_OF_CHILDS; ++i)
	{
		if (CHILD(node, i))
		{
			count += LeafCountRecursion(CHILD(node, i));
		}
	}
	
	return count;
}


void IsFullUpdate(trie_node_t *node)
{
	size_t i = 0;
	
	for (; NUM_OF_CHILDS > i; ++i)
	{
		if (!CHILD(node, i) || !(CHILD(node, i)->is_full))
		{
			node->is_full = FALSE;
			return;
		}
	}
	
	node->is_full = TRUE;
}


int	IsLeaf(trie_node_t *node)
{
	size_t i = 0;

	for (; NUM_OF_CHILDS > i; ++i)
	{
		if (CHILD(node, i))
		{
			return FALSE;
		}
	}
	
	return TRUE;
}




/********************************************/
/*			   DHCP Functions				*/
/********************************************/



/*unsigned int FlipBytesInt(unsigned int bank)*/
/*{*/
/*	unsigned int result = 0;*/
/*	unsigned int byte_chunk = 255;*/
/*	*/
/*	unsigned int byte1 = (bank >> 8 * 3) & byte_chunk << 8 * 0;*/
/*	unsigned int byte2 = (bank >> 8 * 2) & byte_chunk << 8 * 1;*/
/*	unsigned int byte3 = (bank >> 8 * 1) & byte_chunk << 8 * 2;*/
/*	unsigned int byte4 = (bank >> 8 * 0) & byte_chunk << 8 * 3;*/
/*	*/
/*	result = byte1 | byte2 | byte3 | byte4;*/
/*	*/
/*	return result;*/
/*}*/

/*unsigned int BitsMirror(unsigned int num) */
/*{*/
/*    size_t num_bits = sizeof(num) * 8;*/
/*    size_t i = 0;*/
/*    unsigned int result = 0;*/

/*    for (; i < num_bits; i++) */
/*    {*/
/*        if (num & (1 << i)) */
/*        {*/
/*            result |= (1 << (num_bits - 1 - i));*/
/*        }*/
/*    }*/

/*    return result;*/
/*}*/


















