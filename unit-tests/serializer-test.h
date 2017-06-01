// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <library/serializer.h>

void serializer_test(){
	ae_serializer uut;

	test_start("Create serializer")
		create_serializer(&uut);
	test_end()

	test_start("Serialize U8")
		serialize(&uut, U8, 123);
		assert(uut.data[0] == 123);
	test_end()

	test_start("Serialize U16")
		serialize(&uut, U16, 1234);
		assert((uut.data[1] | (uut.data[2] << 8)) == 1234);
	test_end()

	test_start("Serialize U32")
		serialize(&uut, U32, 12345678);
		assert((uut.data[3] | (uut.data[4] << 8) | (uut.data[5] << 16) | (uut.data[6] << 24)) == 12345678);
	test_end()

	test_start("Serializer U64")
		serialize(&uut, U64, 1234567890ULL);
		assert((uut.data[7] | (uut.data[8] << 8) | (uut.data[9] << 16) | (uut.data[10] << 24) |
			((U64)uut.data[11] << 32) | ((U64)uut.data[12] << 40) | ((U64)uut.data[13] << 48) | ((U64)uut.data[14] << 56)) == 1234567890);
	test_end()

	test_start("Serialize varint")
		serialize(&uut, varint, 1234UL);
		assert(((uut.data[15] & 0x7F) | ((uut.data[16] & 0x7F) << 7)) == 1234);
	test_end()

	test_start("Destroy serializer")
		destroy_serializer(&uut);
	test_end()

	test_passed();
}
