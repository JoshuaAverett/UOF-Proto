// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "allocator.h"

#include <library/master.h>

#if defined(AE_PLATFORM_APPLE)
#include <malloc/malloc.h>
#elif defined(AE_PLATFORM_LINUX)
#include <malloc.h>
#endif

DEFINE_DEFAULT_ALLOCATOR(default, )

void CREATE_ALLOCATOR(default)(ALLOCATOR(default)* obj){
}

void DESTROY_ALLOCATOR(default)(ALLOCATOR(default)* obj){
}

void* ALLOCATE_METHOD(default)(in ae_type_info* type, in U32 count, in_out ALLOCATOR(default)* obj){
	return malloc(type->size * count);
}

void DEALLOCATE_METHOD(default)(in_out void* value, in_out ALLOCATOR(default)* obj){
	free(value);
}
