// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>
#include <library/type-info.h>

#include <boost/preprocessor/library.hpp>

// Data types
typedef struct{
	cstring name;
} ae_allocator;

// Interface methods

#define ALLOCATOR(name) \
	BOOST_PP_CAT(ae_, ALLOCATOR_TAGLESS(name))

#define ALLOCATOR_TAGLESS(name) \
	BOOST_PP_CAT(allocator_, name)

#define DEFAULT_ALLOCATOR(name) \
	BOOST_PP_CAT(allocator_default_, name)

#define CREATE_ALLOCATOR(name) \
	BOOST_PP_CAT(create_allocator_, name)

#define DESTROY_ALLOCATOR(name) \
	BOOST_PP_CAT(destroy_allocator_, name)

#define ALLOCATE_METHOD(name) \
	BOOST_PP_CAT(ALLOCATOR_TAGLESS(name), _allocate)

#define DEALLOCATE_METHOD(name) \
	BOOST_PP_CAT(ALLOCATOR_TAGLESS(name), _deallocate)

// Allocations happen using the following framework

// void* allocate(type_id type, opt allocator_type alloc_type, opt allocator_obj obj)
#define allocate(...) \
	allocate_inner(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), __VA_ARGS__)

// void* allocate_array(type_id type, U32 count, opt allocator_type alloc_type, opt allocator_obj obj)
#define allocate_array(...) \
	allocate_array_inner(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), __VA_ARGS__)

// void deallocate(void* value, opt allocator_type alloc_type, opt allocator_obj obj)
#define deallocate(...) \
	deallocate_inner(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), __VA_ARGS__)

// Protection layer
#define allocate_inner(size, ...) \
	BOOST_PP_ASSERT_MSG(BOOST_PP_LESS_EQUAL(size, 3), "Invalid number of allocation arguments") \
	BOOST_PP_CAT(allocate_inner_, size)(__VA_ARGS__)

#define allocate_array_inner(size, ...) \
	BOOST_PP_ASSERT_MSG(BOOST_PP_AND(BOOST_PP_GREATER(size, 1), BOOST_PP_LESS_EQUAL(size, 4)), "Invalid number of array allocation arguments") \
	BOOST_PP_CAT(allocate_array_inner_, size)(__VA_ARGS__)

#define deallocate_inner(size, ...) \
	BOOST_PP_ASSERT_MSG(BOOST_PP_LESS_EQUAL(size, 3), "Invalid number of deallocation arguments") \
	BOOST_PP_CAT(deallocate_inner_, size)(__VA_ARGS__)

// Allocate
#define allocate_inner_1(type) \
	ALLOCATE_METHOD(default)(&TYPE_INFO(type), 1, &DEFAULT_ALLOCATOR(default))

#define allocate_inner_2(type, name) \
	ALLOCATE_METHOD(name)(&TYPE_INFO(type), 1, &DEFAULT_ALLOCATOR(name))

#define allocate_inner_3(type, name, obj) \
	ALLOCATE_METHOD(name)(&TYPE_INFO(type), 1, obj)

// Allocate array
#define allocate_array_inner_2(type, count) \
	ALLOCATE_METHOD(default)(&TYPE_INFO(type), count, &DEFAULT_ALLOCATOR(default))

#define allocate_array_inner_3(type, count, name) \
	ALLOCATE_METHOD(name)(&TYPE_INFO(type), count, &DEFAULT_ALLOCATOR(name))

#define allocate_array_inner_4(type, count, name, obj) \
	ALLOCATE_METHOD(name)(&TYPE_INFO(type), count, obj)

// Deallocate
#define deallocate_inner_1(value) \
	DEALLOCATE_METHOD(default)(value, &DEFAULT_ALLOCATOR(default))

#define deallocate_inner_2(value, name) \
	DEALLOCATE_METHOD(name)(value, &DEFAULT_ALLOCATOR(name))

#define deallocate_inner_3(value, name, obj) \
	DEALLOCATE_METHOD(name)(value, obj)

// Creation helpers
#define DECLARE_ALLOCATOR_STRUCTURE(name, info) \
	typedef struct{ \
		cstring alloc_name; \
		info \
	} ALLOCATOR(name); \
	\
	global ALLOCATOR(name) DEFAULT_ALLOCATOR(name);

#define DEFINE_DEFAULT_ALLOCATOR(name, info) \
	ALLOCATOR(name) DEFAULT_ALLOCATOR(name) = { .alloc_name = BOOST_PP_STRINGIZE(name), info };

DECLARE_ALLOCATOR_STRUCTURE(default, )

void CREATE_ALLOCATOR(default)(ALLOCATOR(default)*);
void DESTROY_ALLOCATOR(default)(ALLOCATOR(default)*);

void* ALLOCATE_METHOD(default)(in ae_type_info* type, in U32 count, in_out ALLOCATOR(default)* obj);
void DEALLOCATE_METHOD(default)(in_out void* value, in_out ALLOCATOR(default)* obj);
