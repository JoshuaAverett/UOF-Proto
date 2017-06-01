// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <library/collections/hash-table.h>

DEFINE_HASH_TABLE(U32, U32)

void hash_table_test(){
	HASH_TABLE(U32, U32) uut;

	test_start("Create hash table")
		CREATE_HASH_TABLE(U32, U32)(&uut);
	test_end()

	test_start("Set and get value")
		HASH_TABLE_SET(U32, U32)(&uut, 1234, 4321);
		U32 test;
		assert(HASH_TABLE_GET(U32, U32)(&uut, 1234, &test));
		assert(test == 4321);
	test_end()

	test_start("Destroy hash table")
		DESTROY_HASH_TABLE(U32, U32)(&uut);
	test_end()

	test_passed();
}
