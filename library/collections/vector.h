// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>
#include <library/allocator.h>

#include <boost/preprocessor/library.hpp>

// Data types

#define VECTOR(T) \
	BOOST_PP_CAT(ae_, VECTOR_TAGLESS(T))

// Methods

// Creates a vector with the default initial size
#define CREATE_VECTOR(T) \
	BOOST_PP_CAT(create_, VECTOR_TAGLESS(T))

// Creates a vector with a given size
#define CREATE_VECTOR_SIZED(T) \
	BOOST_PP_CAT(create_sized_, VECTOR_TAGLESS(T))

// Destroys a vector, deallocating the internal storage
#define DESTROY_VECTOR(T) \
	BOOST_PP_CAT(destroy_, VECTOR_TAGLESS(T))

// Gets an element from a vector
#define VECTOR_GET(T) \
	BOOST_PP_CAT(VECTOR_TAGLESS(T), _get)

// Sets an element in the vector
#define VECTOR_SET(T) \
	BOOST_PP_CAT(VECTOR_TAGLESS(T), _set)

// Appends an element to a vector
#define VECTOR_APPEND(T) \
	BOOST_PP_CAT(VECTOR_TAGLESS(T), _append)

// Resizes the vector
#define VECTOR_RESIZE(T) \
	BOOST_PP_CAT(VECTOR_TAGLESS(T), _resize)

// Reserves space for some elements, ensuring there is space
#define VECTOR_RESERVE(T) \
	BOOST_PP_CAT(VECTOR_TAGLESS(T), _reserve)

// Gets the raw pointer to the data
#define VECTOR_START_CHECKOUT(T) \
	BOOST_PP_CAT(VECTOR_TAGLESS(T), _start_checkout)

// Finishes using the raw data
#define VECTOR_FINISH_CHECKOUT(T) \
	BOOST_PP_CAT(VECTOR_TAGLESS(T), _complete_checkout)

#define VECTOR_LENGTH(T) \
	BOOST_PP_CAT(VECTOR_TAGLESS(T), _length)

#define VECTOR_RESERVED(T) \
	BOOST_PP_CAT(VECTOR_TAGLESS(T), _reserved)

// Internal

#define VECTOR_TAGLESS(T) \
	BOOST_PP_CAT(vector_, T)

#define VECTOR_DEFAULT_RESERVE 10

// Body

#define DEFINE_VECTOR(T) \
	typedef struct packed{ \
		U32 length; \
		U32 reserved; \
		T* data; \
	} VECTOR(T); \
	\
	static inline void CREATE_VECTOR_SIZED(T)(in_out VECTOR(T)* obj, in U32 size){ \
		obj->length = 0; \
		obj->reserved = size; \
		obj->data = allocate_array(T, obj->reserved); \
		memclear(obj->data, size * sizeof(T)); \
	} \
	\
	static inline void CREATE_VECTOR(T)(in_out VECTOR(T)* obj){ \
		CREATE_VECTOR_SIZED(T)(obj, VECTOR_DEFAULT_RESERVE); \
	} \
	\
	static inline void DESTROY_VECTOR(T)(in_out VECTOR(T)* obj){ \
		deallocate(obj->data); \
	} \
	\
	static inline void VECTOR_RESIZE(T)(in_out VECTOR(T)* obj, in U32 new_size){ \
		T* new_data = allocate_array(T, new_size); \
		memclear(new_data, new_size * sizeof(T)); \
		U32 copy_size = min(new_size, obj->reserved) * sizeof(T); \
		memcpy(new_data, obj->data, copy_size); \
		deallocate(obj->data); \
		obj->data = new_data; \
		obj->reserved = new_size; \
	} \
	\
	static inline T VECTOR_GET(T)(in VECTOR(T)* obj, in U32 index){ \
		assert(index < obj->reserved); \
		return obj->data[index]; \
	} \
	\
	static inline void VECTOR_SET(T)(in_out VECTOR(T)* obj, in U32 index, in T value){ \
		if(index > obj->reserved) VECTOR_RESIZE(T)(obj, index + 1); \
		obj->data[index] = value; \
		obj->length = index + 1; \
	} \
	\
	static inline void VECTOR_APPEND(T)(in_out VECTOR(T)* obj, in T value){ \
		if(++obj->length >= obj->reserved){ \
			VECTOR_RESIZE(T)(obj, 2 * obj->reserved + 1); \
		} \
		obj->data[obj->length - 1] = value; \
	} \
	\
	static inline void VECTOR_RESERVE(T)(in_out VECTOR(T)* obj, in U32 count){ \
		if(obj->length + count >= obj->reserved){ \
			VECTOR_RESIZE(T)(obj, obj->reserved + count); \
		} \
	} \
	\
	static inline T* VECTOR_START_CHECKOUT(T)(in_out VECTOR(T)* obj){ \
		return &(obj->data[obj->length]); \
	} \
	\
	static inline void VECTOR_FINISH_CHECKOUT(T)(in_out VECTOR(T)* obj, in U32 written){ \
		obj->length += written; \
	} \
	\
	static inline U32 VECTOR_LENGTH(T)(in VECTOR(T)* obj){ \
		return obj->length; \
	} \
	\
	static inline U32 VECTOR_RESERVED(T)(in VECTOR(T)* obj){ \
		return obj->reserved; \
	}

// Basic type vectors

DEFINE_VECTOR(U8)
DEFINE_VECTOR(U16)
DEFINE_VECTOR(U32)
DEFINE_VECTOR(U64)

DEFINE_VECTOR(S8)
DEFINE_VECTOR(S16)
DEFINE_VECTOR(S32)
DEFINE_VECTOR(S64)
