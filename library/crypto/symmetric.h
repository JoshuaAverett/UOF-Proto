// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>
#include <library/crypto/asymmetric.h>

typedef struct{
	U32 schedule[16];
	U32 keystream[16];
	U32 available;
} ae_symetric_context;

void symetric_context_create(in_out ae_symetric_context* obj, in ae_shared_key* key, in U64 nonce);
void symetric_context_set_counter(in_out ae_symetric_context* obj, in U64 counter);

void symetric_encrypt(out U8* dest, in_out ae_symetric_context* obj, in U8* data, in U32 length);
void symetric_decrypt(out U8* dest, in_out ae_symetric_context* obj, in U8* data, in U32 length);
