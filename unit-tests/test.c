// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "test.h"

#include <stdlib.h>

void test_passed(){
	printf("Module passed.\n");
}

void test_failed(){
	printf("Module failed!\n");
	exit(1);
}
