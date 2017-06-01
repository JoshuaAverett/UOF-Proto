// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>

#include <library/collections/vector.h>

// Data types

#define HASH_TABLE(K, V) \
	BOOST_PP_CAT(ae_, HASH_TABLE_TAGLESS(K, V))

// Methods

#define CREATE_HASH_TABLE(K, V) \
	BOOST_PP_CAT(create_, HASH_TABLE_TAGLESS(K, V))

#define DESTROY_HASH_TABLE(K, V) \
	BOOST_PP_CAT(destroy_, HASH_TABLE_TAGLESS(K, V))

#define HASH_TABLE_SET(K, V) \
	BOOST_PP_CAT(HASH_TABLE_TAGLESS(K, V), _set)

#define HASH_TABLE_GET(K, V) \
	BOOST_PP_CAT(HASH_TABLE_TAGLESS(K, V), _get)

#define HASH_TABLE_DELETE(K, V) \
	BOOST_PP_CAT(HASH_TABLE_TAGLESS(K, V), _delete)

// Internal

#define HASH_TABLE_TAGLESS(K, V) \
	BOOST_PP_CAT(hash_table_, BOOST_PP_CAT(K, BOOST_PP_CAT(_, V)))

#define KEY_VALUE_PAIR(K, V) \
	BOOST_PP_CAT(key_value_pair_, BOOST_PP_CAT(K, BOOST_PP_CAT(_, V)))

// Body

static U32 hash_table_hash(in void* data, in U32 size){
	U32 fuck = *(U32*)data;
	if(!fuck) return 1234;
	return fuck;
}

#define DEFINE_HASH_TABLE(K, V) \
	typedef struct{ \
		K key; \
		V value; \
	} KEY_VALUE_PAIR(K, V); \
	\
	DECLARE_TYPE(KEY_VALUE_PAIR(K, V)) \
	DEFINE_TYPE(KEY_VALUE_PAIR(K, V)) \
	DEFINE_VECTOR(KEY_VALUE_PAIR(K, V)) \
	\
	typedef struct{ \
		VECTOR(U32) hashes; \
		VECTOR(KEY_VALUE_PAIR(K, V)) values; \
	} HASH_TABLE(K, V); \
	DEFINE_TYPE(HASH_TABLE(K, V)) \
	\
	static void CREATE_HASH_TABLE(K, V)(in_out HASH_TABLE(K, V)* obj){ \
		CREATE_VECTOR(U32)(&obj->hashes); \
		CREATE_VECTOR(KEY_VALUE_PAIR(K, V))(&obj->values); \
		memclear(obj->hashes.data, sizeof(U32) * VECTOR_RESERVED(U32)(&obj->hashes)); \
	} \
	\
	static void DESTROY_HASH_TABLE(K, V)(in_out HASH_TABLE(K, V)* obj){ \
		DESTROY_VECTOR(U32)(&obj->hashes); \
		DESTROY_VECTOR(KEY_VALUE_PAIR(K, V))(&obj->values); \
	} \
	\
	static void HASH_TABLE_SET(K, V)(in_out HASH_TABLE(K, V)* obj, in K key, in V value){ \
		U32 length = VECTOR_RESERVED(U32)(&obj->hashes); \
		U32 hash = hash_table_hash(&key, sizeof(key)); \
		S32 index = -1; \
		\
		for(U32 i = 0; i < 64; ++i){ \
			U32 test_hash = VECTOR_GET(U32)(&obj->hashes, (hash + i) % length); \
			if(!test_hash || test_hash == hash){ \
				index = (hash + i) % length; \
				break; \
			} \
		} \
		\
		if(index == -1){ \
		} \
		\
		VECTOR_SET(U32)(&obj->hashes, index, hash); \
		KEY_VALUE_PAIR(K, V) key_value = { key, value }; \
		VECTOR_SET(KEY_VALUE_PAIR(K, V))(&obj->values, index, key_value); \
	} \
	\
	static bool HASH_TABLE_GET(K, V)(in_out HASH_TABLE(K, V)* obj, in K key, out V* value){ \
		U32 length = VECTOR_RESERVED(U32)(&obj->hashes); \
		U32 hash = hash_table_hash(&key, sizeof(key)); \
		S32 index = -1; \
		\
		for(U32 i = 0; i < 64; ++i){ \
			U32 test_hash = VECTOR_GET(U32)(&obj->hashes, (hash + i) % length); \
			if(!test_hash) return false; \
			else if(test_hash == hash){ \
				index = (hash + i) % length; \
				break; \
			} \
		} \
		\
		if(index == -1) return false; \
		*value = VECTOR_GET(KEY_VALUE_PAIR(K, V))(&obj->values, index).value; \
		return true; \
	} \
	\
	static void HASH_TABLE_DELETE(K, V)(in_out HASH_TABLE(K, V)* obj, in K key){ \
		U32 length = VECTOR_RESERVED(U32)(&obj->hashes); \
		U32 hash = hash_table_hash(&key, sizeof(key)); \
		S32 index = -1; \
		\
		for(U32 i = 0; i < 64; ++i){ \
			U32 test_hash = VECTOR_GET(U32)(&obj->hashes, (hash + i) % length); \
			if(test_hash == hash){ \
				return; \
			} \
		} \
	}
