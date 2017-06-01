// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <library/master.h>

#include <boost/preprocessor/library.hpp>

_Static_assert(_Generic(0, int: true, default: false), "Compiler fails generic test");

void compiler_test(){
	printf("Compiler name: %s\n", COMPILER_NAME);
	printf("Compiler C version: %s\n", COMPILER_C_VERSION);

	// Test if typeof is correct and compiles
	int a;
	typeof(a) b;
	assert(_Generic(b, int: true, default: false));

	test_passed();
}
