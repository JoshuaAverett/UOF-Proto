// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <library/master.h>
#include <library/serializer.h>
#include <library/deserializer.h>
#include <library/system/random.h>

#define TEST_ITER 100
#define SERIAL_MIN_ITER 2
#define SERIAL_MAX_ITER 128

typedef enum{
	DATATYPE_U8,
	DATATYPE_U16,
	DATATYPE_U32,
	DATATYPE_U64,
	DATATYPE_VARINTU32,
	DATATYPE_VARINTU64,
	DATATYPE_VARINTS32,
	DATATYPE_VARINTS64,
	DATATYPE_BLANK,
	DATATYPE_STRING,
	DATATYPE_BLOCK,
} datatype_t;

void get_interesting_data(out U8* dest, in U32 length, bool is_signed){
	switch(random_get_uniform(3)){
	case 0: // Lower data bound
		memclear(dest, length);
		break;
	case 1: // Random data
		random_get_bytes(dest, length);
		break;
	case 2: // Upper data bound
		memset(dest, 0xFF, length);
		break;
	}
}

void serializer_test(){
	for(U32 i = 0; i < TEST_ITER; ++i){
		// Step 1: generate random data
		U8 testdata[sizeof(U64)*SERIAL_MAX_ITER];
		datatype_t testdata_types[SERIAL_MAX_ITER];
		int writehead = 0;
		for(U32 j = 0; j < SERIAL_MAX_ITER; ++j){
			switch(random_get_uniform(8)){
			case DATATYPE_U8:
				random_get_bytes(testdata+writehead, sizeof(U8));
				writehead += sizeof(U8);
				break;

			case DATATYPE_U16:
				random_get_bytes(testdata+writehead, sizeof(U16));
				writehead += sizeof(U16);
				break;

			case DATATYPE_U32:
				random_get_bytes(testdata+writehead, sizeof(U32));
				writehead += sizeof(U32);
				break;

			case DATATYPE_U64:
				random_get_bytes(testdata+writehead, sizeof(U64));
				writehead += sizeof(U64);
				break;

			case DATATYPE_VARINTU32:
				break;
			}
		}

		ae_serializer serializer;
		create_serializer(&serializer);
	}
}
