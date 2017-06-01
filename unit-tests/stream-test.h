// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <library/stream.h>

void stream_test(){
	ae_stream uut;

	test_start("Create stream")
		create_stream(&uut);
	test_end()

	test_start("Write U8")
		stream_write(&uut, U8, 123);
	test_end()

	test_start("Read U8")
		U8 test;
		stream_read(&uut, U8, &test);
		assert(test == 123);
	test_end()

	test_start("Write U16")
		stream_write(&uut, U16, 1234);
	test_end()

	test_start("Read U16")
		U16 test;
		stream_read(&uut, U16, &test);
		assert(test == 1234);
	test_end()

	test_start("Write/Read U8 and U16 consecutively")
		stream_write(&uut, U8, 123);
		stream_write(&uut, U16, 4567);

		U8 testU8;
		stream_read(&uut, U8, &testU8);
		assert(testU8 == 123);

		U16 testU16;
		stream_read(&uut, U16, &testU16);
		assert(testU16 == 4567);
	test_end()

	test_start("Varint")
		stream_write(&uut, varint, 1234);
		U32 test;
		stream_read(&uut, varint, &test);
		printf("Test = %d\n", test);
		assert(test == 1234);
	test_end()

	test_start("Destroy stream")
		destroy_stream(&uut);
	test_end()

	test_passed();
}
