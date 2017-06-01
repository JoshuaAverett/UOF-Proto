// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <boost/preprocessor/library.hpp>

// Generate compiler type macros

#if defined(__clang__)
#  define AE_COMPILER_CLANG 1
#elif defined(__GNUC__)
#  define AE_COMPILER_GCC 1
#else
#  error Unknown compiler!
#endif

// Generate compiler name and version info

#if AE_COMPILER_CLANG
#  define COMPILER_TYPE "Clang"
#  define COMPILER_MAJOR BOOST_PP_STRINGIZE(__clang_major__)
#  define COMPILER_MINOR BOOST_PP_STRINGIZE(__clang_minor__)
#  define COMPILER_PATCH_LEVEL BOOST_PP_STRINGIZE(__clang_patchlevel__)
#elif(AE_COMPILER_GCC)
#  define COMPILER_TYPE "GCC"
#  define COMPILER_MAJOR BOOST_PP_STRINGIZE(__GNUC__)
#  define COMPILER_MINOR BOOST_PP_STRINGIZE(__GNUC_MINOR__)
#  define COMPILER_PATCH_LEVEL BOOST_PP_STRINGIZE(__GNUC_PATCHLEVEL__)
#endif

#define COMPILER_NAME COMPILER_TYPE " v" COMPILER_MAJOR "." COMPILER_MINOR "." COMPILER_PATCH_LEVEL
#define COMPILER_C_VERSION BOOST_PP_STRINGIZE(__STDC_VERSION__)

// Generate a pragma macro
#define PRAGMA(x) _Pragma(#x)

// Generate diagnostic control macros

#if AE_COMPILER_CLANG || AE_COMPILER_GCC

	#define INCOMPATIBLE_POINTER_TYPES "-Wincompatible-pointer-types"
	#define RETURN_TYPE "-Wreturn-type"
	#define DISCARDS_QUALIFIERS "-Wincompatible-pointer-types-discards-qualifiers"
	#define REDECLARES_LIB_FUNCTION "-Wincompatible-library-redeclaration"
	#define TYPEDEF_REDEFINITION "-Wtypedef-redefinition"
	#define INVALID_INT_CONVERSION "-Wint-conversion"

	#define DISABLE_DIAGNOSTIC(diagnostic_name) \
	        PRAGMA(GCC diagnostic push) \
        	PRAGMA(GCC diagnostic ignored diagnostic_name)

	#define ENABLE_DIAGNOSTIC(diagnostic_name) \
        	PRAGMA(GCC diagnostic pop)

#endif

// Generate typeof

#if AE_COMPILER_CLANG
#  define typeof(x) __typeof__(x)
#endif

// Generate packed struct thing

#if AE_COMPILER_CLANG || AE_COMPILER_GCC
#  define packed __attribute__((__packed__))
#endif
