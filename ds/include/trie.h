#ifndef __TRIE_H__
#define __TRIE_H__

typedef enum trie_status
{
  TRIE_SUCCESS,	
  TRIE_MEMORY_FALIURE,
  TRIE_DHCP_FULL,
  TRIE_BAD_SUBNET,
  TRIE_DOUBLE_FREE,
  TRIE_NOT_IN
} e_status_t;

typedef struct trie trie_t;

typedef struct trie_node *trie_iter_t;


trie_t *TrieCreate(size_t tree_depth);
void TrieDestroy(trie_t *trie);

e_status_t TrieInsert(trie_t* trie, unsigned char *key, unsigned char *received_ip);
e_status_t TrieRemove(trie_t* trie, unsigned char *ip_to_free);
e_status_t TrieSearch(trie_t* trie, unsigned char *ip_to_find);
size_t TrieLeafCount(trie_t *trie);

#endif /*__TRIE_H__*/
