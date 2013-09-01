#include <string.h>
#include <stdlib.h>

#include "arraylist.h"


arraylist_t *arraylist_create(int initial_cap, size_t elem_size, float grow_factor, float sink_threshold, float sink_factor)
	{
	arraylist_t *list=malloc(sizeof(arraylist_t));
	if(list==NULL)
		return NULL;
	list->data=malloc(initial_cap*elem_size);
	if(list->data==NULL)
		{
		free(list);
		return NULL;
		}
	list->alloc_size=initial_cap;
	list->len=0;
	list->elem_size=elem_size;
	list->grow_factor=grow_factor;
	list->sink_factor=sink_factor;
	list->sink_threshold=sink_threshold;
	return list;
	}

int arraylist_add(arraylist_t *list, void *e)
	{
	if(list->len==list->alloc_size)
		{
		int new_size=list->alloc_size*list->grow_factor;
		void *ptr=realloc(list->data, new_size);
		if(ptr==NULL)
			return 1;
		list->data=ptr;
		list->alloc_size=new_size;
		}

	memcpy(arraylist_get(list, list->len++), e, list->elem_size);
	return 0;
	}

void *arraylist_get(arraylist_t *list, int i)
	{
	if(i<0 || i>=list->len)
		return NULL;
	return list->data+list->elem_size*i;
	}
void *arraylist_remove(arraylist_t *list, int i)
	{
	if(i<0 || i>=list->len)
		return NULL;
	void *e=malloc(list->elem_size);
	if(e==NULL)
		return NULL;
	memcpy(e, arraylist_get(list, i), list->elem_size);
	list->len--;
	memmove(arraylist_get(list, i), arraylist_get(list, i+1), list->elem_size*(list->len-i));

	if((float)list->alloc_size/(float)list->len<list->sink_threshold)
		{
		size_t new_size=list->alloc_size*list->sink_factor;
		list->data=realloc(list->data, new_size);
		list->alloc_size=new_size;
		}
	return e;
	}

void arraylist_destroy(arraylist_t *list)
	{
	free(list->data);
	free(list);
	}
