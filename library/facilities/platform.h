// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

// Operating system
#if defined(__linux__)
#  define AE_PLATFORM_LINUX 1
#elif defined(_WIN32)
#  define AE_PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
#  define AE_PLATFORM_APPLE 1
#else
#  error Unknown platform!
#endif

#if defined(AE_PLATFORM_LINUX)
#  define _GNU_SOURCE 1
#endif

// CPU
#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(__amd64__) || defined(_M_AMD64) || defined(_M_X64)
#  define AE_CPU_64_BIT 1
#  define AE_CPU_X86 1
#elif defined(__i386) || defined(__i386__) || defined(_M_IX86)
#  define AE_CPU_32_BIT 1
#  define AE_CPU_X86 1
#else
#  error Unknown CPU
#endif

#if defined(AE_CPU_X86)
#  include <x86intrin.h>
#endif
