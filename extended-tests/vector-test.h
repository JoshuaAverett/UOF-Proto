// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <library/master.h>
#include <library/collections/vector.h>

void vector_test(){
	VECTOR(U32) uut;
	test_start("create vector")
		CREATE_VECTOR(U32)(&uut);
	test_end()

	test_start("vetor append")
		VECTOR_APPEND(U32)(&uut, 1234);
		assert(VECTOR_GET(U32)(&uut, 0) == 1234);
	test_end()

	test_start("vector set")
		VECTOR_SET(U32)(&uut, 0, 4321);
		assert(VECTOR_GET(U32)(&uut, 0) == 4321);
	test_end()

	test_start("destroy vector")
		DESTROY_VECTOR(U32)(&uut);
	test_end()

	test_passed();
}
