// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "symmetric.h"

#include <library/deserializer.h>
#include <library/serializer.h>

void symetric_context_create(in_out ae_symetric_context* obj, in ae_shared_key* shared_key, in U64 nonce){
	// Constant
	obj->schedule[0] = 1634760805; // "expa"
	obj->schedule[1] = 857760878; // "nd 3"
	obj->schedule[2] = 2036477234; // "2-by"
	obj->schedule[3] = 1797285236; // "te k"

	// Key
	const U8* key = shared_key->value;
	deserialize_U32(&obj->schedule[4], key);
	deserialize_U32(&obj->schedule[5], key + 4);
	deserialize_U32(&obj->schedule[6], key + 8);
	deserialize_U32(&obj->schedule[7], key + 12);
	deserialize_U32(&obj->schedule[8], key + 16);
	deserialize_U32(&obj->schedule[9], key + 20);
	deserialize_U32(&obj->schedule[10], key + 24);
	deserialize_U32(&obj->schedule[11], key + 28);

	// Counter
	obj->schedule[12] = 0;
	obj->schedule[13] = 0;

	// Nonce
	obj->schedule[14] = nonce & 0xFFFFFFFF;
	obj->schedule[15] = nonce >> 32;

	obj->available = 0;
}

void symetric_context_set_counter(in_out ae_symetric_context* obj, in U64 counter){
	obj->schedule[12] = counter & 0xFFFFFFFF;
	obj->schedule[12] = counter >> 32;
	obj->available = 0;
}

static inline void symetric_xor(in U8* key, in U8* source, out U8* dest, U32 length){
	const U8* key_end = key + length;
	do{
		*dest++ = *source++ ^ *key++;
	} while(key < key_end);
}

#define ROTL32(v, n) ((v) << (n)) | ((v) >> (32 - (n)))

#define QUARTERROUND(x, a, b, c, d) \
    x[a] += x[b]; x[d] = ROTL32(x[d] ^ x[a], 16); \
    x[c] += x[d]; x[b] = ROTL32(x[b] ^ x[c], 12); \
    x[a] += x[b]; x[d] = ROTL32(x[d] ^ x[a], 8); \
    x[c] += x[d]; x[b] = ROTL32(x[b] ^ x[c], 7);

void symetric_encrypt(out U8* dest, in_out ae_symetric_context* obj, in U8* data, U32 length){
	if(!length) return;

	U8* key_stream = (U8*)obj->keystream;

	if(obj->available){
		U32 amount = min(length, obj->available);
		symetric_xor(key_stream + (sizeof(obj->keystream) - obj->available), data, dest, amount);
		obj->available -= amount;
		length -= amount;
	}

	while(length){
		U32* output = obj->keystream;
		memcpy(output, obj->schedule, sizeof(obj->schedule));

		S32 i = 10;
		while(i--){
			QUARTERROUND(output, 0, 4, 8, 12)
			QUARTERROUND(output, 1, 5, 9, 13)
			QUARTERROUND(output, 2, 6, 10, 14)
			QUARTERROUND(output, 3, 7, 11, 15)
			QUARTERROUND(output, 0, 5, 10, 15)
			QUARTERROUND(output, 1, 6, 11, 12)
			QUARTERROUND(output, 2, 7, 8, 13)
			QUARTERROUND(output, 3, 4, 9, 14)
		}

		for(i = 0; i < 16; ++i){
			U32 result = output[i] + obj->schedule[i];
			serialize_U32((U8*)&output[i], result);
		}

		U32* nonce = &obj->schedule[12];
		if(!++nonce[0] && !++nonce[1] && !++nonce[2]) ++nonce[3];

		U32 amount = min(length, sizeof(obj->keystream));
		symetric_xor(key_stream, data, dest, amount);
		length -= amount;
		obj->available = sizeof(obj->keystream) - amount;
	}
}

void symetric_decrypt(out U8* dest, in_out ae_symetric_context* obj, in U8* data, in U32 length){
	symetric_encrypt(dest, obj, data, length);
}
