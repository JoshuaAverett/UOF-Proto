// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>

// Data types

#define ATOMIC_BIT_VECTOR(size) \
	BOOST_PP_CAT(ae_, ATOMIC_BIT_VECTOR_TAGLESS(size))

// Methods

#define CREATE_ATOMIC_BIT_VECTOR(size) \
	BOOST_PP_CAT(create_, ATOMIC_BIT_VECTOR_TAGLESS(size))

#define DESTROY_ATOMIC_BIT_VECTOR(size) \
	BOOST_PP_CAT(destroy_, ATOMIC_BIT_VECTOR_TAGLESS(size))

#define ATOMIC_BIT_VECTOR_ARRAY_LENGTH(size) \
	BOOST_PP_CAT(ATOMIC_BIT_VECTOR_TAGLESS(size), _array_length)

#define ATOMIC_BIT_VECTOR_SET(size) \
	BOOST_PP_CAT(ATOMIC_BIT_VECTOR_TAGLESS(size), _set)

#define ATOMIC_BIT_VECTOR_CLEAR(size) \
	BOOST_PP_CAT(ATOMIC_BIT_VECTOR_TAGLESS(size), _clear)

#define ATOMIC_BIT_VECTOR_DEQUEUE_0(size) \
	BOOST_PP_CAT(ATOMIC_BIT_VECTOR_TAGLESS(size), _dequeue_0)

#define ATOMIC_BIT_VECTOR_DEQUEUE_1(size) \
	BOOST_PP_CAT(ATOMIC_BIT_VECTOR_TAGLESS(size), _dequeue_1)

// Internal

#define ATOMIC_BIT_VECTOR_TAGLESS(size) \
	BOOST_PP_CAT(atomic_bit_vector_, size)

#define DEFINE_ATOMIC_BIT_VECTOR(size) \
	DEFINE_CONSTANT(ATOMIC_BIT_VECTOR_ARRAY_LENGTH(size), size / 64 + 1) \
	\
	typedef struct{ \
		atomic_U64 data[ATOMIC_BIT_VECTOR_ARRAY_LENGTH(size)]; \
	} ATOMIC_BIT_VECTOR(size); \
	\
	static void CREATE_ATOMIC_BIT_VECTOR(size)(in_out ATOMIC_BIT_VECTOR(size)* obj){ \
		for(U32 i = 0; i < ATOMIC_BIT_VECTOR_ARRAY_LENGTH(size); ++i){ \
			atomic_store(&obj->data[i], 0); \
		} \
	} \
	\
	static void DESTROY_ATOMIC_BIT_VECTOR(size)(in_out ATOMIC_BIT_VECTOR(size)* obj){ \
	} \
	\
	static void ATOMIC_BIT_VECTOR_SET(size)(in_out ATOMIC_BIT_VECTOR(size)* obj, in U32 index){ \
		atomic_fetch_or(&obj->data[index / 64], 1ULL << (index % 64)); \
	} \
	\
	static void ATOMIC_BIT_VECTOR_CLEAR(size)(in_out ATOMIC_BIT_VECTOR(size)* obj, in U32 index){ \
		atomic_fetch_and(&obj->data[index / 64], ~(1ULL << (index % 64))); \
	} \
	\
	static S32 ATOMIC_BIT_VECTOR_DEQUEUE_0(size)(in_out ATOMIC_BIT_VECTOR(size)* obj){ \
		for(U32 i = 0; i < ATOMIC_BIT_VECTOR_ARRAY_LENGTH(size); ++i){ \
			U64 data = atomic_load(&obj->data[i]); \
			while(data){ \
				S32 index = find_first_set(~data); \
				if(atomic_compare_exchange_strong(&obj->data[i], &data, data | (1 << index))){ \
					return index + i * 64; \
				} \
			} \
		} \
		return -1; \
	} \
	\
	static S32 ATOMIC_BIT_VECTOR_DEQUEUE_1(size)(in_out ATOMIC_BIT_VECTOR(size)* obj){ \
		S32 index; \
		for(U32 i = 0; i < ATOMIC_BIT_VECTOR_ARRAY_LENGTH(size); ++i){ \
			U64 data = atomic_load(&obj->data[i]); \
			while(data){ \
				S32 index = find_first_set(data); \
				if(atomic_compare_exchange_strong(&obj->data[i], &data, data & ~(1 << index))){ \
					return index + i * 64; \
				} \
			} \
		} \
		return -1; \
	}
