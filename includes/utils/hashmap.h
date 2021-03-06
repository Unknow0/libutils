/*******************************************************************************
 * This file is part of libutils.
 *
 * libutils is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with libutils; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 ******************************************************************************/
#ifndef _HASHMAP_H
#define _HASHMAP_H

#include <stdlib.h>
#include <utils/iterator.h>

typedef struct
	{
	size_t (*hash)(void *);
	void (*destructor)(void *);
	float load_factor;
	size_t entries_count;
	size_t map_size;
	void **map_entries;
	} hashmap_t;

struct hashmap_it
	{
	iterator_t it;
	hashmap_t *map;
	size_t off;
	};

/**
 * allocate a new hashmap
 * initial capacity is 2^log2s
 * return null on error
 */
hashmap_t *hashmap_create(unsigned char log2s, float load_factor, size_t (*hash_func)(void*), void (*destructor)(void*));

/**
 * put an element into the map.
 * return 0 on success, 1 if failed to grow and 2 if map==NULL || e==NULL
 */
int hashmap_add(hashmap_t *map, void *e);

/**
 * get an element from the map with it's hash.
 * return NULL on error or if element don't exist
 */
void *hashmap_get(hashmap_t *map, size_t hash);

/**
 * remove element from map.
 * return 0 on success, 2 if the hash isn't found
 */
int hashmap_remove(hashmap_t *map, size_t hash);

/**
 * free the hashmap.
 */
void hashmap_destroy(hashmap_t *map);

iterator_t *hashmap_iterator(hashmap_t *map);

#endif
