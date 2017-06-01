// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/facilities/platform.h>

#include <stdbool.h>
#include <stdint.h>

#define nullptr ((void*)0)

typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef float F32;
typedef double F64;

typedef char* cstring;

#if defined(AE_CPU_32_BIT)
typedef S32 SW;
typedef U32 UW;
#elif defined(AE_CPU_64_BIT)
typedef S64 SW;
typedef U64 UW;
#endif

// Register these types, but only after they enough for us to actualy create the type info struct
#include <library/type-info.h>

DECLARE_TYPE(S8)
DECLARE_TYPE(S16)
DECLARE_TYPE(S32)
DECLARE_TYPE(S64)

DECLARE_TYPE(U8)
DECLARE_TYPE(U16)
DECLARE_TYPE(U32)
DECLARE_TYPE(U64)

DECLARE_TYPE(F32)
DECLARE_TYPE(F64)

DECLARE_TYPE(cstring)
