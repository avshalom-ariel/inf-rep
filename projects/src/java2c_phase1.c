#include <stdlib.h>			/*malloc free*/
#include <stdio.h>			/*printf*/

#define CLASS_NAME_SIZE 30
#define NUM_OF_METHODS 3
#define VTABLE_SIZE 30
#define EQUALS_INDEX 0
#define HASH_CODE_INDEX 1
#define TO_STRING_INDEX 2


typedef void* (*method_t)();
typedef void (*constructor_t)(void*);


typedef struct class {
	const char *name;
	size_t object_size;
	method_t *vtable;
} class_t;

typedef struct object
{
	class_t *metadata;
	struct object *super;
} object_t;

typedef struct mutable_integer
{
	class_t *metadata;
	object_t *super;
	int value;
} mutable_integer_t;


static int Equals(void *obj1, void *obj2);
static int HashCode(void *obj);
static char* ToString(void *obj);
static int mutable_integer_Equals_Object_mutable_integer_t(mutable_integer_t *obj, mutable_integer_t *this);


char *obj_name = "object";
char *mut_int_name = "mutable integer";

class_t *object_metadata;
class_t *mutable_integer_metadata;


/*********************************************************/


object_t *CreateObject()
{
    object_t *instance = NULL;

	if(!object_metadata)
	{
		object_metadata = (class_t *)malloc(sizeof(class_t));
		if (NULL == object_metadata)
		{
		    return NULL;
		}

		object_metadata->vtable = (method_t *)malloc(sizeof(method_t) * NUM_OF_METHODS);
		if (NULL == object_metadata->vtable)
		{
		    free(object_metadata);
		    return NULL;
		}
		
		object_metadata->vtable[EQUALS_INDEX] = (method_t)&Equals;
		object_metadata->vtable[HASH_CODE_INDEX] = (method_t)&HashCode;
		object_metadata->vtable[TO_STRING_INDEX] = (method_t)&ToString;
	    
	    object_metadata->object_size = sizeof(object_t);
    	object_metadata->name = obj_name;
	}

    instance = (object_t *)malloc(sizeof(object_t));
    if (NULL == instance)
    {
        return NULL;
    }

    instance->metadata = object_metadata;
	instance->super = NULL;

    return instance;
}


mutable_integer_t *CreateMutableInteger()
{
	mutable_integer_t *instance = NULL;
    
    if (!mutable_integer_metadata)
    {
		mutable_integer_metadata = (class_t *)malloc(sizeof(class_t));
		if (!mutable_integer_metadata)
		{
			return NULL;
		}
		
		mutable_integer_metadata->vtable = (method_t *)malloc(sizeof(method_t) * NUM_OF_METHODS);
		if (!mutable_integer_metadata->vtable)
		{
			free(mutable_integer_metadata->vtable);
			return NULL;
		}
		
		mutable_integer_metadata->vtable[EQUALS_INDEX] =
    				 (method_t)&mutable_integer_Equals_Object_mutable_integer_t;
    				 
    	mutable_integer_metadata->name = mut_int_name;
		mutable_integer_metadata->object_size = sizeof(mutable_integer_t);
    }
    
    instance = (mutable_integer_t *)malloc(sizeof(mutable_integer_t));
    if (!instance)
    {
        free(mutable_integer_metadata->vtable);
        free(mutable_integer_metadata);
        return NULL;
    }
    
	instance->metadata = mutable_integer_metadata;

    instance->super = CreateObject();
    if (!instance->super)
    {
    	free(mutable_integer_metadata->vtable);
        free(mutable_integer_metadata);
    	free(instance);
    	return NULL;
    }
    
    return instance;
}

void MetadataCleanUp(void)
{
	free(mutable_integer_metadata->vtable);
	free(mutable_integer_metadata);
	free(object_metadata->vtable);
	free(object_metadata);
}


/***************** Object ********************/


int Equals(void *obj1, void *obj2) 
{
    return obj1 == obj2;
}

int HashCode(void *obj) 
{
    return (int)(size_t)obj;
}

char* ToString(void *obj) 
{
    static char buffer[100];
    sprintf(buffer, "Object at address %ld", (size_t)obj);
    return buffer;
}

const char *GetClassObject(object_t *obj)
{
	return ((mutable_integer_t*)obj)->metadata->name;
}

/***************** Mutable int ********************/


void mutable_integer_int(int val, mutable_integer_t *this)
{
	this->value = val;
}

void mutable_integer_Set(int val, mutable_integer_t *this)
{
	this->value = val;
}

int mutable_integer_Get(mutable_integer_t *this)
{
	return this->value;
}

int mutable_integer_Equals_Object_mutable_integer_t(mutable_integer_t *other, mutable_integer_t *this)
{
	return (mutable_integer_Get(this) == mutable_integer_Get(other));
}

void MutableIntegerConstructor(int value, mutable_integer_t *this) 
{
	this->value = value;
}


int main(void)
{
	object_t *num1 = (object_t *)CreateMutableInteger();
	object_t *num2 = (object_t *)CreateMutableInteger();
	
	MutableIntegerConstructor(5, (mutable_integer_t*)num1);
	MutableIntegerConstructor(5, (mutable_integer_t*)num2);
	
	if (mutable_integer_metadata->vtable[EQUALS_INDEX]((mutable_integer_t*)num1, (mutable_integer_t*)num2))
    {
        printf("Yes!\n");
    } else
    {
        printf("No!\n");
    }
	
	printf("%s\n", GetClassObject(num1));

	
	MetadataCleanUp();
	free(num1->super);
	free(num2->super);
	free(num1);
	free(num2);
	
	return 0;
}




