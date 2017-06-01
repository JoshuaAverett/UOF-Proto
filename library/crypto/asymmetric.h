// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>

typedef struct{
	U8 value[32];
} ae_private_key;

typedef struct{
	U8 value[32];
} ae_public_key;

typedef struct{
	U8 value[32];
} ae_shared_key;

void asymetric_generate(out ae_private_key* us_pri, out ae_public_key* us_pub);
void asymetric_exchange(out ae_shared_key* shared, in ae_private_key* us_pri, in ae_public_key* them_pub);
