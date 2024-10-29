
#include <stddef.h>		/*size_t*/
#include <stdio.h>		/*printf*/

typedef void (*method_t)();

typedef char* (*to_string_t)();
typedef void* (*finialize_t)();
typedef int (*get_num_masters_t)();

typedef struct class {
	char *name;
	size_t object_size;
	method_t *vtable;
	struct class *super_metadata;
} class_t;

#define EQUALS_INDEX 0
#define HASH_CODE_INDEX 1
#define TO_STRING_INDEX 2
#define FINIALIZE_INDEX 3
#define SAY_HELLO_INDEX 4
#define GET_NUM_MASTERS_INDEX 5

/**************** Objcd ..ect ********************/

typedef struct object
{
	class_t *metadata;
} object_t;


char *Object_ToString(object_t *this, char *display)
{
	sprintf(display, "%s@%d", this->metadata->name, Object_HashCode(this));

	return display;

}

int Object_Equals_object_t(object_t *this, object_t *other)
{
	return this == other;
}

int Object_HashCode(object_t *this) 
{
    return (int)(size_t)this;
}

void Object_Finalize(object_t *this)
{
	(void)this;
	printf("finalize Object\n");
}

class_t object_metadata;

char object_name[] = "Object";

method_t object_vtable[] = {
		(method_t)&Object_Equals_object_t, 
		(method_t)&Object_HashCode, 
		(method_t)&Object_ToString, 
		(method_t)&Object_Finalize
};

/************** Object Helpers ****************/


object_t CreateObject()
{
	object_t instance = {0};
	
	object_metadata.name = object_name;
	object_metadata.object_size = sizeof(object_t);
	object_metadata.vtable = object_vtable;
	
	instance.metadata = &object_metadata;
	
	return instance;
}


/**************** Animal ********************/

typedef struct animal
{
	object_t super;
	int num_masters;
	int num_legs;
	int ID;
} animal_t;

int animal_is_load;

int animal_counter;

char animal_name[] = "Animal";

void Animal_ShowCounter(void);
void Animal_SayHello(animal_t *this);
void AnimalInstanceInit(animal_t *animal);

void CtorAnimal(animal_t *this)
{
	char buffer[30] = {0};
	
	AnimalInstanceInit(this);
	
	printf("Animal Ctor\n");
	this->ID = ++animal_counter;
	this->super.metadata->vtable[SAY_HELLO_INDEX](this);
	
	Animal_ShowCounter();
	
	printf("%s", ((to_string_t)this->super.metadata->vtable[TO_STRING_INDEX])(this, buffer));
	printf("%s\n", Object_ToString((object_t *)this, buffer));
}

void CtorAnimal_int(animal_t *this, int num_masters)
{
	AnimalInstanceInit(this);
	
	printf("Animal Ctor int\n");
	this->ID = ++animal_counter;
	this->num_masters = num_masters;
}


void Animal_SayHello(animal_t *this)
{	
	printf("Animal Hello!\nI have %d legs\n", this->num_legs);
}

void Animal_ShowCounter(void)
{
	printf("%d\n", animal_counter);
}

int Animal_GetNumMasters(animal_t *this)
{
	return this->num_masters;
}

char *Animal_ToString(animal_t *this, char *display)
{
	sprintf(display, "Animal with ID: %d\n", ((animal_t *)this)->ID);
	
	return display;
}

void Animal_Finalize(animal_t *this)
{
	printf("finalize Animal with ID:%d\n", this->ID);
	(this->super.metadata->vtable[FINIALIZE_INDEX])(this);
}

class_t animal_metadata;

method_t animal_vtable[] = {
		(method_t)Object_Equals_object_t, 
		(method_t)Object_HashCode, 
		(method_t)Animal_ToString, 
		(method_t)Animal_Finalize,
		(method_t)Animal_SayHello, 
		(method_t)Animal_GetNumMasters
};

/**************** Animal Helpers ********************/


void AnimalStaticInit(void)
{
	/* Setup metadata*/
	animal_metadata.name = animal_name;
	animal_metadata.object_size = sizeof(animal_t);
	animal_metadata.vtable = animal_vtable;
	
	/*Static blocks*/
	printf("Static block Animal 1\n");
	printf("Static block Animal 2\n");
	
	/*static fields*/
	animal_counter = 0;
	
	animal_is_load = 1;
}

void AnimalInstanceInit(animal_t *animal)
{
	/*instance fields*/
	animal->num_masters = 1;
	animal->num_legs = 5;
	animal->ID = 0;
	
	/*instance blocks*/
	printf("Instance initialization block Animal\n");
}

animal_t CreateAnimal(void)
{
	animal_t instance = {0};
	
	((object_t *)&instance)->metadata = &animal_metadata;
	((object_t *)&instance)->metadata->super_metadata = &object_metadata;
	
	if(!animal_is_load)
	{
		AnimalStaticInit();
	}
	
	CtorAnimal(&instance);
	
	return instance;
}


/********************* Dog *************************/


typedef struct dog
{
	animal_t super;
	int num_legs;
} dog_t;

void DogInstanceInit(dog_t *dog);

int dog_is_load;

char dog_name[] = "Dog";

void CtorDog(dog_t *this)
{
	CtorAnimal_int(&(this->super), 2);
	
	DogInstanceInit(this);
	
	printf("Dog Ctor\n");
}

void Dog_SayHello(dog_t *this)
{
	printf("Dog Hello!\nI have %d legs\n", this->num_legs);
}

void Dog_Finalize(dog_t *this)
{
	printf("finalize Dog with ID:%d\n", this->super.ID);
	(this->super.super.metadata->vtable[FINIALIZE_INDEX])(&(this->super));
}

char *Dog_ToString(dog_t *this, char *display)
{

	sprintf(display, "Dog with ID: %d\n", ((animal_t *)this)->ID);
	
	return display;

}

class_t dog_metadata;

method_t dog_vtable[] = {
		(method_t)Object_Equals_object_t,
		(method_t)Object_HashCode,
		(method_t)Dog_ToString,
		(method_t)Dog_Finalize,
		(method_t)Dog_SayHello,
		(method_t)Animal_GetNumMasters
};


/****************** Dog Helpers *********************/


void DogStaticInit(void)
{
	/* Setup metada*/
	dog_metadata.name = dog_name;
	dog_metadata.object_size = sizeof(dog_t);
	dog_metadata.vtable = dog_vtable;
	
	/*Static blocks*/
	printf("Static block Dog\n");
	
	/*static fields*/
	
	dog_is_load = 1;
}

void DogInstanceInit(dog_t *dog)
{
	/*instance fields*/
	dog->num_legs = 4;

	/*instance blocks*/
	printf("Instance initialization block Dog\n");
}


dog_t CreateDog(void)
{
	dog_t instance = {0};
	
	((object_t *)&instance)->metadata = &dog_metadata;
	((object_t *)&instance)->metadata->super_metadata = &animal_metadata;

	if(!animal_is_load)
	{
		AnimalStaticInit();
	}

	if(!dog_is_load)
	{
		DogStaticInit();
	}
	
	CtorDog(&instance);
	
	return instance;
}


/********************* Cat *************************/

char default_color[] = "black";
char cat_name[] = "Cat";

typedef struct cat
{
	animal_t super;
	char *colors;
	int num_masters;
} cat_t;

void CatInstanceInit(cat_t *cat);

int cat_is_load;
int is_cat_ctor;

void CtorCat_char_ptr(cat_t *this, char *colors)
{
	CtorAnimal(&(this->super));
	CatInstanceInit(this);
	
	this->colors = colors;
	printf("Cat Ctor with color: %s\n", this->colors);
}

void CtorCat(cat_t *this)
{
	CtorCat_char_ptr(this, default_color);
	
	printf("Cat Ctor\n");
	this->num_masters = 2;
}

void Cat_Finalize(cat_t *this)
{
	printf("finalize Cat with ID:%d\n", this->super.ID);
	this->super.super.metadata->vtable[FINIALIZE_INDEX](&(this->super));
}

char *Cat_ToString(cat_t *this, char *display)
{
	sprintf(display, "Cat with ID: %d\n", ((animal_t *)this)->ID);
	
	return display;
}

class_t cat_metadata;

method_t cat_vtable[] = {
		(method_t)Object_Equals_object_t,
		(method_t)Object_HashCode,
		(method_t)Cat_ToString,
		(method_t)Cat_Finalize,
		(method_t)Animal_SayHello,
		(method_t)Animal_GetNumMasters
};


/****************** Cat Helpers *********************/


void CatStaticInit(void)
{
	/* Setup metada*/
	cat_metadata.name = cat_name;
	cat_metadata.object_size = sizeof(cat_t);
	cat_metadata.vtable = cat_vtable;
	
	/*Static blocks*/
	printf("Static block Cat\n");
	
	cat_is_load = 1;
}

void CatInstanceInit(cat_t *cat)
{
	/*instance fields*/
	cat->num_masters = 5;
}

cat_t CreateCat()
{
	cat_t instance = {0};
	
	((object_t *)&instance)->metadata = &cat_metadata;
	((object_t *)&instance)->metadata->super_metadata = &animal_metadata;
	
	if(!animal_is_load)
	{
		AnimalStaticInit();
	}
	
	if(!cat_is_load)
	{
		CatStaticInit();
	}
	
	CtorCat(&instance);
	
	return instance;
}

cat_t CreateCat_char_ptr(char *color)
{
	cat_t instance = {0};
	
	((object_t *)&instance)->metadata = &cat_metadata;
	((object_t *)&instance)->metadata->super_metadata = &animal_metadata;
	
	if(!animal_is_load)
	{
		AnimalStaticInit();
	}
	
	if(!cat_is_load)
	{
		CatStaticInit();
	}
	
	CtorCat_char_ptr(&instance, color);
	
	return instance;
}


/********************* Legendary Animal *************************/


char legendary_name[] = "Legendary Animal";

typedef struct legendary
{
	cat_t super;
} legendary_t;

int legendary_is_load;

void CtorLegendary(legendary_t *this)
{
	CtorCat(&(this->super));
	
	printf("Legendary Ctor\n");
}

void Legendary_Finalize(legendary_t *this)
{
	printf("finalize LegendaryAnimal with ID:%d\n", this->super.super.ID);
	this->super.super.super.metadata->vtable[FINIALIZE_INDEX](&(this->super));
}

char *Legendary_ToString(legendary_t *this, char *display)
{
	sprintf(display, "LegendaryAnimal with ID:%d\n", this->super.super.ID);

	return display;
}

void Legendary_SayHello(legendary_t *this)
{
	(void)this;
	printf("Legendary Hello\n");
}

class_t legendary_metadata;

method_t legendary_vtable[] = {
		(method_t)Object_Equals_object_t,
		(method_t)Object_HashCode,
		(method_t)Legendary_ToString,
		(method_t)Legendary_Finalize,
		(method_t)Legendary_SayHello,
		(method_t)&Animal_GetNumMasters
};



/****************** Cat Helpers *********************/


void LegendaryStaticInit(void)
{
	/* Setup metada*/
	legendary_metadata.name = legendary_name;
	legendary_metadata.object_size = sizeof(legendary_t);
	legendary_metadata.vtable = legendary_vtable;

	/*static block*/
	printf("Static block Legendary Animal\n");

	legendary_is_load = 1;
}

legendary_t CreateLegendary(void)
{
	legendary_t instance = {0};
	
	((object_t *)&instance)->metadata = &legendary_metadata;
	((object_t *)&instance)->metadata->super_metadata = &cat_metadata;
	
	if(!animal_is_load)
	{
		AnimalStaticInit();
	}
	
	if(!cat_is_load)
	{
		CatStaticInit();
	}
	
	if(!legendary_is_load)
	{
		LegendaryStaticInit();
	}
	
	CtorLegendary(&instance);

	return instance;
}


/********************* Main *************************/


void foo(animal_t *a)
{
	char buffer[30] = {0};
	
	printf(((to_string_t)(a->super.metadata->vtable[TO_STRING_INDEX]))(a, buffer));
}


int main(void)
{
/*	object_t obj = {0};*/
	animal_t animal = CreateAnimal();
	dog_t dog = CreateDog();
	cat_t cat = CreateCat();
	legendary_t la = CreateLegendary();
	
	animal_t *array[5] = {0};
	
	dog_t arr_dog = {0};
	cat_t arr_cat = {0};
	cat_t arr_cat_white = {0};
	legendary_t arr_legendary = {0};
	animal_t arr_animal = {0};
	
	char white[] = "white";
	size_t i = 0;
	
	Animal_ShowCounter();
	
	printf("%d\n", animal.ID);
	printf("%d\n", ((animal_t *)&dog)->ID);
	printf("%d\n", ((animal_t *)&cat)->ID);
	printf("%d\n", ((animal_t *)&la)->ID);
	
	arr_dog = CreateDog();
	arr_cat = CreateCat();
	arr_cat_white = CreateCat_char_ptr(white);
	arr_legendary = CreateLegendary();
	arr_animal = CreateAnimal();

	array[0] = (animal_t *)&arr_dog;
	array[1] = (animal_t *)&arr_cat;
	array[2] = (animal_t *)&arr_cat_white;
	array[3] = (animal_t *)&arr_legendary;
	array[4] = (animal_t *)&arr_animal;
	
	for (; i < 5; ++i)
	{
		array[i]->super.metadata->vtable[SAY_HELLO_INDEX](array[i]);
		printf("%d\n", 
		((get_num_masters_t)(array[i]->super.metadata->vtable[GET_NUM_MASTERS_INDEX]))(array[i]));
	}
	
	for (i = 0; i < 5; ++i)
	{
		foo(array[i]);
	}

	return 0;
}


