// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <library/collections/hash-table.h>
#include <library/system/random.h>

DEFINE_HASH_TABLE(U32, U32)

int comp (const void * elem1, const void * elem2)
{
    U32 f = *((U32*)elem1);
    U32 s = *((U32*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

void hash_table_test(){
	HASH_TABLE(U32, U32) uut;

	test_start("Create hash table")
		CREATE_HASH_TABLE(U32, U32)(&uut);
	test_end()

	// Generate test keys
	U32 test_keys[10000];
	random_get_bytes((U8*)&test_keys, sizeof(U32)*10000);
	// The left half of the test_keys array will be keys to delete, and the right half will be keys to retrieve after the deletion process. Therefore we can't have duplicate keys across the two sides.
	// Ensure that a key will be on the same side of the array as its duplicates
	qsort(test_keys, 10000, sizeof(U32), comp);
	if (test_keys[4999] == test_keys[5000]) test_keys[5000]++;
	int i;
	// Left half key shuffle
	for (i = 0; i < 5000; ++i) {
		U32 swapwith = random_get_uniform(5000);
		U32 tmp;
		tmp = test_keys[i];
		test_keys[i] = test_keys[swapwith];
		test_keys[swapwith] = tmp;
	}
	// Right half key shuffle
	for (i = 5000; i < 10000; ++i) {
		U32 swapwith = random_get_uniform(5000) + 5000;
		U32 tmp;
		tmp = test_keys[i];
		test_keys[i] = test_keys[swapwith];
		test_keys[swapwith] = tmp;
	}

	// Generate test values
	U32 test_values[10000];
	random_get_bytes((U8*)&test_values, sizeof(U32)*10000);

	test_start("Fill hash table")
		int i;
		for (i = 0; i < 10000; ++i){
			HASH_TABLE_SET(U32, U32)(&uut, test_keys[i], test_values[i]);
		}
	test_end()

	test_start("Delete half the keys")
		int i;
		for (i = 0; i < 5000; ++i) {
			HASH_TABLE_DELETE(U32, U32)(&uut, test_keys[i]);
		}
	test_end()

	test_start("Retrieve the other half of the keys")
		int i;
		for (i = 5000; i < 10000; ++i) {
			U32 fetched_val;
			assert(HASH_TABLE_GET(U32, U32)(&uut, test_keys[i], &fetched_val));
			assert(fetched_val == test_values[i]);
		}
	test_end()

	test_start("Destroy hash table")
		DESTROY_HASH_TABLE(U32, U32)(&uut);
	test_end()

	test_passed();
}
