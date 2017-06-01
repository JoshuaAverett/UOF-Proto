// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <stdio.h>

#define assert(x) \
	if(!(x)) test_failed();

#define test_start(name) \
	printf("Test: %s\n", name); \
	{

#define test_end() \
	}

void test_passed();
void test_failed();
