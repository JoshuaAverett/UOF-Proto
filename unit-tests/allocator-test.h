// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <library/allocator.h>
#include <library/master.h>

void allocator_test(){
	test_start("allocate, deallocate")
		U32* a = allocate(U32);
		*a = 1234;
		assert(*a == 1234);
		deallocate(a);
	test_end()

	test_start("allocate_array, deallocate")
		U32* a = allocate_array(U32, 10);
		a[0] = 1234;
		a[1] = 4321;
		assert(a[0] == 1234);
		assert(a[1] == 4321);
		deallocate(a);
	test_end()

	test_start("custom allocator")
		ALLOCATOR(default) alloc;
		CREATE_ALLOCATOR(default)(&alloc);

		U32* a = allocate(U32, default, &alloc);
		*a = 1234;
		assert(*a == 1234);
		deallocate(a);

		DESTROY_ALLOCATOR(default)(&alloc);
	test_end()

	test_passed();
}
