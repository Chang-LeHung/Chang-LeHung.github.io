
#include <stdlib.h>
#include <string.h>

typedef struct hash_elem_t {
	struct hash_elem_t* next; 
	void* data;
	char key[]; 
} hash_elem_t;

typedef struct {
	unsigned int capacity;
	unsigned int e_num;
	hash_elem_t** table;
} hashtable_t;

typedef struct {
	hashtable_t* ht; 	
	unsigned int index;	
	hash_elem_t* elem; 
} hash_elem_it;

#define HT_ITERATOR(ht) {ht, 0, ht->table[0]}

char err_ptr;
void* HT_ERROR = &err_ptr; 

static unsigned int ht_calc_hash(char* key)
{
	unsigned int h = 5381;
	while(*(key++))
		h = ((h << 5) + h) + (*key);
	return h;
}


hashtable_t* ht_create(unsigned int capacity)
{
	hashtable_t* hasht = malloc(sizeof(hashtable_t));
	if(!hasht)
		return NULL;
	if((hasht->table = malloc(capacity*sizeof(hash_elem_t*))) == NULL)
	{
		free(hasht->table);
		return NULL;
	}
	hasht->capacity = capacity;
	hasht->e_num = 0;
	unsigned int i;
	for(i = 0; i < capacity; i++)
		hasht->table[i] = NULL;
	return hasht;
}


void* ht_put(hashtable_t* hasht, char* key, void* data)
{
	if(data == NULL)
		return NULL;
	unsigned int h = ht_calc_hash(key) % hasht->capacity;
	hash_elem_t* e = hasht->table[h];

	while(e != NULL)
	{
		if(!strcmp(e->key, key))
		{
			void* ret = e->data;
			e->data = data;
			return ret;
		}
		e = e->next;
	}

	if((e = malloc(sizeof(hash_elem_t)+strlen(key)+1)) == NULL)
		return HT_ERROR;
	strcpy(e->key, key);
	e->data = data;

	e->next = hasht->table[h];
	hasht->table[h] = e;
	hasht->e_num ++;

	return NULL;
}

void* ht_get(hashtable_t* hasht, char* key)
{
	unsigned int h = ht_calc_hash(key) % hasht->capacity;
	hash_elem_t* e = hasht->table[h];
	while(e != NULL)
	{
		if(!strcmp(e->key, key))
			return e->data;
		e = e->next;
	}
	return NULL;
}

void* ht_remove(hashtable_t* hasht, char* key)
{
	unsigned int h = ht_calc_hash(key) % hasht->capacity;
	hash_elem_t* e = hasht->table[h];
	hash_elem_t* prev = NULL;
	while(e != NULL)
	{
		if(!strcmp(e->key, key))
		{
			void* ret = e->data;
			if(prev != NULL)
				prev->next = e->next;
			else
				hasht->table[h] = e->next;
			free(e);
			e = NULL;
			hasht->e_num --;
			return ret;
		}
		prev = e;
		e = e->next;
	}
	return NULL;
}

void ht_list_keys(hashtable_t* hasht, char** k, size_t len)
{
	if(len < hasht->e_num)
		return;
	int ki = 0; 
	int i = hasht->capacity;
	while(--i >= 0)
	{
		hash_elem_t* e = hasht->table[i];
		while(e)
		{
			k[ki++] = e->key;
			e = e->next;
		}
	}
}

void ht_list_values(hashtable_t* hasht, void** v, size_t len)
{
	if(len < hasht->e_num)
		return;
	int vi = 0; 
	int i = hasht->capacity;
	while(--i >= 0)
	{
		hash_elem_t* e = hasht->table[i];
		while(e)
		{
			v[vi++] = e->data;
			e = e->next;
		}
	}
}

hash_elem_t* ht_iterate(hash_elem_it* iterator)
{
	while(iterator->elem == NULL)
	{
		if(iterator->index < iterator->ht->capacity - 1)
		{
			iterator->index++;
			iterator->elem = iterator->ht->table[iterator->index];
		}
		else
			return NULL;
	}
	hash_elem_t* e = iterator->elem;
	if(e)
		iterator->elem = e->next;
	return e;
}

char* ht_iterate_keys(hash_elem_it* iterator)
{
	hash_elem_t* e = ht_iterate(iterator);
	return (e == NULL ? NULL : e->key);
}

/* Iterate through values. */
void* ht_iterate_values(hash_elem_it* iterator)
{
	hash_elem_t* e = ht_iterate(iterator);
	return (e == NULL ? NULL : e->data);
}

void ht_clear(hashtable_t* hasht, int free_data)
{
	hash_elem_it it = HT_ITERATOR(hasht);
	char* k = ht_iterate_keys(&it);
	while(k != NULL)
	{
		free_data ? free(ht_remove(hasht, k)) : ht_remove(hasht, k);
		k = ht_iterate_keys(&it);
	}
}

void ht_destroy(hashtable_t* hasht)
{
	ht_clear(hasht, 1);
	free(hasht->table);
	free(hasht);
}


#include <stdio.h>
int main()
{
	hashtable_t *ht = ht_create(1024);
  printf("执行插入操作\n");
	ht_put(ht, "foo", "bar");
  printf("执行查找操作\n");
	printf("%s\n", (char*)ht_get(ht, "foo"));
	ht_put(ht, "foo", "rab");
	printf("%s\n", (char*)ht_get(ht, "foo"));
  printf("执行删除操作\n");
	ht_remove(ht, "foo");
	if(!ht_get(ht, "foo"))
		printf("foo removed\n");

	ht_put(ht, "foo", "bar");
	ht_put(ht, "toto", "titi");

	printf("查看所有的关键字\n");
	char* str[ht->e_num];
	unsigned int i;
	ht_list_keys(ht, str, ht->e_num);
	for(i = 0; i < ht->e_num; i++)
		printf("%s\n", str[i]);
	
	printf("遍历哈希表中的数据\n");
	ht_list_values(ht, (void**)str, ht->e_num);
	for(i = 0; i < ht->e_num; i++)
		printf("%s\n", str[i]);

	hash_elem_it it = HT_ITERATOR(ht);
	hash_elem_t* e = ht_iterate(&it);
	while(e != NULL)
	{
		printf("%s = %s \n", e->key, (char*)e->data);
		e = ht_iterate(&it);
	}
	return 0;
}