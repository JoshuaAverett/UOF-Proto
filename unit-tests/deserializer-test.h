// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <library/deserializer.h>

void deserializer_test(){
	ae_deserializer uut;

	U8 testin[] = {
		0x12,
		0x12, 0x34,
		0x12, 0x34, 0x56, 0x78,
		0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
		0xD2, 0x09,
	};

	test_start("Create deserializer")
		create_deserializer(&uut, testin);
	test_end()

	test_start("Deserialize U8")
		U8 testout;
		deserialize(&uut, U8, &testout);
		assert(testout == 18);
	test_end()

	test_start("Deserialize U16")
		U16 testout;
		deserialize(&uut, U16, &testout);
		assert(testout == 13330);
	test_end()

	test_start("Deserialize U32")
		U32 testout;
		deserialize(&uut, U32, &testout);
		assert(testout == 2018915346);
	test_end()

	test_start("Deserializer U64")
		U64 testout;
		deserialize(&uut, U64, &testout);
		assert(testout == 17279655951921914625ULL);
	test_end()

	test_start("Deserialize varint")
		U32 testout;
		deserialize(&uut, varint, &testout);
		assert(testout == 1234);
	test_end()

	test_passed();
}
