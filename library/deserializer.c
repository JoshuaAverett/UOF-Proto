// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "deserializer.h"

#include <library/master.h>

void create_deserializer(in_out ae_deserializer* obj, in U8* data){
	obj->data = data;
	obj->index = 0;
}

U32 deserializer_index(in ae_deserializer* obj){
	return obj->index;
}

inline U32 deserialize_U8(out U8* dest, in U8* source){
	*dest = source[0];
	return 1;
}

inline U32 deserialize_U16(out U16* dest, in U8* source){
	*dest = source[0] | (source[1] << 8);
	return 2;
}

inline U32 deserialize_U32(out U32* dest, in U8* source){
	*dest = source[0] | (source[1] << 8) | (source[2] << 16) | (source[3] << 24);
	return 4;
}

inline U32 deserialize_U64(out U64* dest, in U8* source){
	*dest = source[0] | (source[1] << 8) | (source[2] << 16) | (source[3] << 24) |
		((U64)source[4] << 32) | ((U64)source[5] << 40) | ((U64)source[6] << 48) | ((U64)source[7] << 56);
	return 8;
}

inline U32 deserialize_varintU32(out U32* dest, in U8* source){
	*dest = 0;
	U32 index = 0;
	do{
		*dest |= (source[index] & 0x7F) << (7 * index);
	} while(source[index++] & 0x80);

	return index;
}

inline U32 deserialize_varintU64(out U64* dest, in U8* source){
	*dest = 0;
	U32 index = 0;
	do{
		*dest |= (source[index] & 0x7F) << (7 * index);
	} while(source[index++] & 0x80);

	return index;
}

inline U32 deserialize_varintS32(out S32* dest, in U8* source){
	*dest = 0;
	U32 index = 0;
	U32 val = 0;
	do{
		*dest |= (source[index] & 0x7F) << (7 * index);
	} while(source[index++] & 0x80);

	*dest = (val >> 1) ^ (-(val & 1));

	return index;
}

inline U32 deserialize_varintS64(out S64* dest, in U8* source){
	*dest = 0;
	U32 index = 0;
	U64 val = 0;
	do{
		*dest |= (source[index] & 0x7F) << (7 * index);
	} while(source[index++] & 0x80);

	*dest = (val >> 1) ^ (-(val & 1));

	return index;
}

inline U32 deserialize_block(out U8** dest, in U32 length, in U8* source){
	*dest = (U8*)source;
	return length;
}

inline U32 deserialize_string(out char** dest, in U8* source){
	U32 length = strlen((char*)source) + 1;
	*dest = (char*)source;
	return length;
}
