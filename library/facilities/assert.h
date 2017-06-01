// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <stdio.h>
#include <stdlib.h>

#ifdef assert
#undef assert
#endif

#define assert(x) \
	if(!(x)){ printf("Assert failed: %s\n", #x); exit(1); }
