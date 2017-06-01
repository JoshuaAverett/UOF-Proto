// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>
#include <library/collections/vector.h>

#include <boost/preprocessor/library.hpp>

typedef struct packed{
	const U8* data;
	U32 index;
} ae_deserializer;

void create_deserializer(in_out ae_deserializer* obj, in U8* data);

U32 deserializer_index(in ae_deserializer* obj);

#define deserialize(source, type, ...) \
	(source)->index += BOOST_PP_CAT(deserialize_, type)(__VA_ARGS__, &(source)->data[(source)->index])

U32 deserialize_U8(out U8* dest, in U8* source);
U32 deserialize_U16(out U16* dest, in U8* source);
U32 deserialize_U32(out U32* dest, in U8* source);
U32 deserialize_U64(out U64* dest, in U8* source);

#define deserialize_varint(dest, source) \
	_Generic(dest, U32*: deserialize_varintU32, U64*: deserialize_varintU64, \
		S32*: deserialize_varintS32, S64*: deserialize_varintS64)(dest, source)

U32 deserialize_varintU32(out U32* dest, in U8* source);
U32 deserialize_varintU64(out U64* dest, in U8* source);
U32 deserialize_varintS32(out S32* dest, in U8* source);
U32 deserialize_varintS64(out S64* dest, in U8* source);

U32 deserialize_block(out U8** const data, in U32 length, in U8* source);
U32 deserialize_string(out char** data, in U8* source);
