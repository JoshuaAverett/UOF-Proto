// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>

#include <stdatomic.h>

typedef _Atomic(bool) atomic_bool;

typedef _Atomic(S8) atomic_S8;
typedef _Atomic(S16) atomic_S16;
typedef _Atomic(S32) atomic_S32;
typedef _Atomic(S64) atomic_S64;

typedef _Atomic(U8) atomic_U8;
typedef _Atomic(U16) atomic_U16;
typedef _Atomic(U32) atomic_U32;
typedef _Atomic(U64) atomic_U64;
