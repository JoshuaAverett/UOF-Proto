// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/facilities/compiler.h>

#include <boost/preprocessor/library.hpp>

#include <string.h>

// Clears a struct
#define memclear(...) BOOST_PP_CAT(memclear_, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__))(__VA_ARGS__)
#define memclear_1(obj) memset(&obj, 0, sizeof(obj))
#define memclear_2(obj, size) memset(obj, 0, size)

// Finds the first set bit in an input value
#define find_first_set(val) _Generic(val, U32: ffs_32(val), U64: ffs_64(val))

#define ffs_32(val) (__builtin_ffs(val) - 1)
#define ffs_64(val) (__builtin_ffs(val) - 1)
