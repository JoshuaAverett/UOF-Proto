// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>

// Interface
void random_stir();
void random_add_entropy(in U8* data, in U32 length);
void random_get_bytes(out U8* dest, in U32 length);
U32 random_get_uniform(in U32 upper_bound);

// Platform
void random_stir_platform();
void random_add_entropy_platform(in U8* data, in U32 length);
void random_get_bytes_platform(out U8* dest, in U32 length);
U32 random_get_uniform_platform(in U32 upper_bound);
