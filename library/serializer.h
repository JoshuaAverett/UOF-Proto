// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/collections/vector.h>

#include <boost/preprocessor/library.hpp>

typedef VECTOR(U8) ae_serializer;

// To make sizeof work, we say a varint is the largest it can be.
typedef U8 varint[10];

// This is a dummy to allow sizeof(block) to compile.
typedef U8 block;
typedef U8 string;
typedef U8 blank;

// Create and destroy a serializer, which allows you to write data
// on to a U8 vector.
void create_serializer(in_out ae_serializer* obj);
void destroy_serializer(in_out ae_serializer* obj);

// Reserve space for an object, without increasing the length of the
// vector, which allows for safe direct manipulation of the data array
void serializer_reserve(in_out ae_serializer* obj, in U32 length);

// Get the length of the serialized data
U32 serializer_length(in ae_serializer* obj);

// Get the actual data pointer from the serializer
U8* serializer_data(in ae_serializer* obj);

// Helper macro to deal with special types whose serialized size is not sizeof(type)
#define CHECK_TYPE(type, test) \
	((void*)BOOST_PP_CAT(serialize_, type) == (void*)BOOST_PP_CAT(serialize_, test))

// Serializes data of a given type to the destination serializer
#define serialize(dest, type, ...) \
	BOOST_PP_CAT(serialize_, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__))(dest, type, __VA_ARGS__)

#define serialize_1(dest, type, value) \
	DISABLE_DIAGNOSTIC(INVALID_INT_CONVERSION) \
	DISABLE_DIAGNOSTIC(DISCARDS_QUALIFIERS) \
	serializer_reserve(dest, \
		CHECK_TYPE(type, string) ? strlen(value) + 1 : \
		CHECK_TYPE(type, blank) ? (U32)value : \
		sizeof(type)); \
	VECTOR_FINISH_CHECKOUT(U8)(dest, BOOST_PP_CAT(serialize_, type)(VECTOR_START_CHECKOUT(U8)(dest), value)); \
	ENABLE_DIAGNOSTIC(DISCARDS_QUALIFIERS) \
	ENABLE_DIAGNOSTIC(INVALID_INT_CONVERSION)

#define serialize_2(dest, type, val1, val2) \
	serializer_reserve(dest, val2); \
	VECTOR_FINISH_CHECKOUT(U8)(dest, BOOST_PP_CAT(serialize_, type)(VECTOR_START_CHECKOUT(U8)(dest), val1, val2));

// Internal functions for serializing different types
U32 serialize_U8(out U8* dest, in U8 value);
U32 serialize_U16(out U8* dest, in U16 value);
U32 serialize_U32(out U8* dest, in U32 value);
U32 serialize_U64(out U8* dest, in U64 value);

// Internal functions for serializing varints
U32 serialize_varint(out U8* dest, in U64 value);
U32 serialize_varint_signed(out U8* dest, in S64 value);

// Internal function for serializing a number of zero bytes
U32 serialize_blank(out U8* dest, in U32 length);

// Internal function for serializing a zero terminated string
U32 serialize_string(out U8* dest, in cstring val);

// Internal function of serializing a block of fixed size
U32 serialize_block(out U8* dest, in U8* data, in U32 len);
