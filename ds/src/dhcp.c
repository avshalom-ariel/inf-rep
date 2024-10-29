
#include <math.h> 	/*pow*/
#include <stdlib.h> /*malloc free*/
#include <string.h>	/*memcpy*/
#include <assert.h> /*assert*/

#include "trie.h"	/*Trie Typedef and Function declaration*/
#include "dhcp.h"	/*DHCP Typedef and Function declaration*/

#define BITS_IN_BYTE 8
#define BYTES_IN_ADD 4
#define BITS_IN_ADD 32
#define NUM_OF_PREALLOC_ADD 3

#define NETWORK {0}
#define BROADCAST {~0}
#define SERVER {~0 - 1}

struct DHCP_Server
{
	trie_t *trie;
	unsigned char *base_network_id;
	size_t subnet_prefix;
};

static status_e InitPreallocAdd(DHCP_Server_t *dhcp);

static unsigned char prealloc_lut_g[NUM_OF_PREALLOC_ADD][BYTES_IN_ADD];
static unsigned char prealloc_base_lut_g[NUM_OF_PREALLOC_ADD][BYTES_IN_ADD] = {NETWORK, BROADCAST, SERVER};


/********************************************/
/*			   API Functions				*/
/********************************************/


DHCP_Server_t *DHCPCreate(unsigned char *base_network_id, size_t subnet_prefix)
{
	DHCP_Server_t *dhcp = (DHCP_Server_t *)malloc(sizeof(DHCP_Server_t));
	if (!dhcp)
	{
		return NULL;
	}
	
	dhcp->trie = TrieCreate(subnet_prefix);
	if (!dhcp->trie)
	{
		free(dhcp);
		return NULL;
	}
		
	dhcp->base_network_id = base_network_id;
	dhcp->subnet_prefix = subnet_prefix;

	InitPreallocAdd(dhcp);
	
	return dhcp;
}


void DHCPDestroy(DHCP_Server_t *dhcp)
{
	if (!dhcp)
	{
		return;
	}
	
	TrieDestroy(dhcp->trie);
	
	free(dhcp);
}


status_e DHCPAllocateIP(DHCP_Server_t *dhcp, unsigned char *requested_ip, 
												unsigned char *received_ip)
{
	status_e status = SUCCESS;
	
	memcpy(received_ip, dhcp->base_network_id, BYTES_IN_ADD);
	
	status = (status_e)TrieInsert(dhcp->trie, requested_ip, received_ip);
	
	return status;
}


status_e DHCPFreeIP(DHCP_Server_t *dhcp, unsigned char *address)
{
	size_t subnet_in_bytes = (dhcp->subnet_prefix) / BITS_IN_BYTE;
	status_e status = SUCCESS;

	assert(dhcp);
	
	if (0 != memcmp(dhcp->base_network_id, address, subnet_in_bytes))
	{
		return BAD_SUBNET;
	}

	status = (status_e)TrieRemove(dhcp->trie, address);
	
	return status;
}


size_t DHCPCountFree(const DHCP_Server_t *dhcp)
{
	assert(dhcp);

	return pow(2, BYTES_IN_ADD * BITS_IN_BYTE - dhcp->subnet_prefix) - TrieLeafCount(dhcp->trie);
}


/********************************************/
/*			   Help Functions				*/
/********************************************/

status_e InitPreallocAdd(DHCP_Server_t *dhcp)
{
	size_t subnet_in_bytes = dhcp->subnet_prefix / BITS_IN_BYTE;
	unsigned char received_ip[BYTES_IN_ADD] = {0};
	status_e status = {0};
	size_t i = 0;

	for (; i < NUM_OF_PREALLOC_ADD; ++i)
	{
		memcpy(prealloc_lut_g[i], dhcp->base_network_id, BYTES_IN_ADD);
		memcpy(prealloc_lut_g[i] + subnet_in_bytes, prealloc_base_lut_g[i], BYTES_IN_ADD - subnet_in_bytes);

/*		memcpy(prealloc_base_lut_g[i], dhcp->base_network_id, subnet_in_bytes);*/
		
		status = (status_e)DHCPAllocateIP(dhcp, prealloc_lut_g[i], received_ip);
	}
	
	return status;
}


