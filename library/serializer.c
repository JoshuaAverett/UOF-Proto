// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "serializer.h"

#include <library/master.h>

void create_serializer(in_out ae_serializer* obj){
	CREATE_VECTOR(U8)(obj);
}

void destroy_serializer(in_out ae_serializer* obj){
	DESTROY_VECTOR(U8)(obj);
}

inline void serializer_reserve(in_out ae_serializer* obj, in U32 length){
	VECTOR_RESERVE(U8)(obj, length);
}

inline U32 serializer_length(in ae_serializer* obj){
	return obj->length;
}

inline U8* serializer_data(in ae_serializer* obj){
	return obj->data;
}

inline U32 serialize_U8(out U8* dest, in U8 value){
	dest[0] = value;

	return 1;
}

inline U32 serialize_U16(out U8* dest, in U16 value){
	dest[0] = value & 0xFF;
	dest[1] = (value >> 8) & 0xFF;

	return 2;
}

inline U32 serialize_U32(out U8* dest, in U32 value){
	dest[0] = value & 0xFF;
	dest[1] = (value >> 8) & 0xFF;
	dest[2] = (value >> 16) & 0xFF;
	dest[3] = (value >> 24) & 0xFF;

	return 4;
}

inline U32 serialize_U64(out U8* dest, in U64 value){
	dest[0] = value & 0xFF;
	dest[1] = (value >> 8) & 0xFF;
	dest[2] = (value >> 16) & 0xFF;
	dest[3] = (value >> 24) & 0xFF;
	dest[4] = (value >> 32) & 0xFF;
	dest[5] = (value >> 40) & 0xFF;
	dest[6] = (value >> 48) & 0xFF;
	dest[7] = (value >> 56) & 0xFF;

	return 8;
}

inline U32 serialize_varint(out U8* dest, in U64 value){
	U32 length = 1;

	dest[0] = value & 0x7F; \
	if(value >= (1ULL <<  7)){ dest[0] |= 0x80; dest[1] = ((value) >>  7) & 0x7F; ++length; }
	if(value >= (1ULL << 14)){ dest[1] |= 0x80; dest[2] = ((value) >> 14) & 0x7F; ++length; }
	if(value >= (1ULL << 21)){ dest[2] |= 0x80; dest[3] = ((value) >> 21) & 0x7F; ++length; }
	if(value >= (1ULL << 28)){ dest[3] |= 0x80; dest[4] = ((value) >> 28) & 0x7F; ++length; }
	if(value >= (1ULL << 35)){ dest[4] |= 0x80; dest[5] = ((value) >> 35) & 0x7F; ++length; }
	if(value >= (1ULL << 42)){ dest[5] |= 0x80; dest[6] = ((value) >> 42) & 0x7F; ++length; }
	if(value >= (1ULL << 49)){ dest[6] |= 0x80; dest[7] = ((value) >> 49) & 0x7F; ++length; }
	if(value >= (1ULL << 56)){ dest[7] |= 0x80; dest[8] = ((value) >> 56) & 0x7F; ++length; }

	return length;
}

inline U32 serialize_varint_signed(out U8* dest, in S64 value_signed){
	U64 value = (value_signed << 1) ^ (value_signed >> 63);

	return serialize_varint(dest, value);
}

inline U32 serialize_blank(out U8* dest, in U32 length){
	memclear(dest, length);
	return length;
}

inline U32 serialize_string(out U8* dest, in cstring value){
	U32 length = strlen(value) + 1;
	memcpy(dest, value, length);
	return length;
}

inline U32 serialize_block(out U8* dest, in U8* data, in U32 len){
	memcpy(dest, data, len);
	return len;
}
