#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h>	/* size_t */

typedef struct avl avl_t;

/*
Description: typedef to pointer function that compare the two argument
Params: (void *, void *) two elements to compare
Return Value: int that represent the status of the matching:
   positive if the first argument is bigger,
   zero if they are equal
   negative if the second argument is bigger.
*/
typedef int (*avl_cmp_func_t)(const void *data, const void *new_data);

/*
Description: typedef of a pointer to function. The function performs an action on the passed data of list element  
Params: (void *, void *) first param - pointer to data in an element, second param - pointer to data sent by the user
Return Value: int that represent status. 0 for success , non 0 for failure
*/
typedef int (*avl_action_func_t)(void *data, void *params);


/*
AVLCreate
description: create a binary search avl
input: a pointer to a compare function 
return: Pointer to binary avl. NULL if failed
time complexity: O(1)
space complexity: O(1)
*/
avl_t *AVLCreate(avl_cmp_func_t compare);

/*
AVLDestroy
description: destroy all the elements in the avl (Post-Ordered)
input: binary avl
return: nothing 
time complexity: O(n)
space complexity: O(1)
*/
void AVLDestroy(avl_t *avl);

/*
AVLSize
description: return the number of elements in the binary search avl (in pre ordered traverse) 
input:  binary avl
return: number of elements in the binary search avl
time complexity: O(n)
space complexity: O(1)
*/
size_t AVLCount(const avl_t *avl);

/*
AVLHeight
description: return the maximum depth of any leaf from the root
input:  binary avl pointer
return: maximum depth if any leaf from the root
time complexity: O(1)
space complexity: O(1)
*/
size_t AVLHeight(const avl_t *avl);

/*
AVLIsEmpty
description: check if AVL is empty
input:  binary avl pointer
return: non-0 if empty, 0 if not empty
time complexity: O(1)
space complexity: O(1)
*/
int AVLIsEmpty(const avl_t *avl);

/*
AVLInsert
description: insert a new element to the AVL
input: a binary avl and new data
return: 0 for success, non-0 for failure
time complexity: O(log n)
space complexity: O(1)
*/
int AVLInsert(avl_t *avl, void *data);

/*
AVLRemove
description: remove an element from the avl
input: a binary avl and new data
return: nothing
time complexity: O(log n)
space complexity: O(1)
*/
void AVLRemove(avl_t *avl, void *data);

/*
AVLFind
description: searches the avl for a certain element. 
input: a binary avl and data to search for
return: a generic pointer to the data if found, NULL otherwise
time complexity: O(log n)
space complexity: O(1)
*/
void *AVLFind(const avl_t *avl, const void *data);

/* 
AVLForEach
description: does a certain action on all the avl (do not change the key it self) In-order
input: binary avl, an action func and a parameter
return: the last status the action function returned
time complexity: O(n)
space complexity: O(1)
*/
int AVLForEach(avl_t *avl, avl_action_func_t action, void* params);


#endif /*__AVL_H__*/
