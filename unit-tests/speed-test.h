#pragma once

#include "test.h"

#include <library/master.h>

#include <library/system/random.h>
#include <library/system/time.h>

#include <boost/preprocessor/library.hpp>

#define TEST_OBJECT(size) \
	BOOST_PP_CAT(test_, size)

#define CREATE_TEST_OBJECT_PTR(size) \
	BOOST_PP_CAT(BOOST_PP_CAT(create_test_, size), _ptr)

#define CREATE_TEST_OBJECT_RET(size) \
	BOOST_PP_CAT(BOOST_PP_CAT(create_test_, size), _ret)

#define MODIFY_TEST_OBJECT_PTR(size) \
	BOOST_PP_CAT(BOOST_PP_CAT(modify_test_, size), _ptr)

#define MODIFY_TEST_OBJECT_RET(size) \
	BOOST_PP_CAT(BOOST_PP_CAT(modify_test_, size), _ret)

#define MAKE_OBJECT(size) \
	typedef struct{ \
		U8 data[size]; \
	} TEST_OBJECT(size); \
	\
	void CREATE_TEST_OBJECT_PTR(size)(in_out volatile TEST_OBJECT(size)* obj, in U8 q){ \
		for(S32 i = 0; i < size; ++i) obj->data[i] = q * i; \
	} \
	\
	TEST_OBJECT(size) CREATE_TEST_OBJECT_RET(size)(in U8 q){ \
		TEST_OBJECT(size) obj; \
		for(S32 i = 0; i < size; ++i) obj.data[i] = q * i; \
		return obj; \
	} \
	\
	void MODIFY_TEST_OBJECT_PTR(size)(out volatile TEST_OBJECT(size)* dest, in volatile TEST_OBJECT(size)* src){ \
		for(S32 i = 0; i < size; ++i) dest->data[i] = i * src->data[i]; \
	} \
	\
	TEST_OBJECT(size) MODIFY_TEST_OBJECT_RET(size)(in volatile TEST_OBJECT(size) src){ \
		TEST_OBJECT(size) dest; \
		for(S32 i = 0; i < size; ++i) dest.data[i] = i * src.data[i]; \
		return dest; \
	}

#define SPEED_TEST_SIZE(size) \
	test_start("Create object size " BOOST_PP_STRINGIZE(size) " bytes") \
		U64 t0 = time_get_ns(); \
			volatile TEST_OBJECT(size) obj_1; \
			for(S32 i = 0; i < 1000; ++i) CREATE_TEST_OBJECT_PTR(size)(&obj_1, q); \
		U64 t1 = time_get_ns(); \
			volatile TEST_OBJECT(size) obj_2; \
			for(S32 i = 0; i < 1000; ++i) obj_2 = CREATE_TEST_OBJECT_RET(size)(q); \
		U64 t2 = time_get_ns(); \
		\
		printf("return time / pointer time = %f\n", (F32)(t2 - t1) / (F32)(t1 - t0)); \
	test_end()

#define MODIFY_TEST(size) \
	test_start("Modify object size " BOOST_PP_STRINGIZE(size) " bytes") \
		U64 t0 = time_get_ns(); \
			volatile TEST_OBJECT(size) src_1, dest_1; \
			CREATE_TEST_OBJECT_PTR(size)(&src_1, q); \
			for(S32 i = 0; i < 1000; ++i) MODIFY_TEST_OBJECT_PTR(size)(&dest_1, &src_1); \
		U64 t1 = time_get_ns(); \
			volatile TEST_OBJECT(size) src_2, dest_2; \
			CREATE_TEST_OBJECT_PTR(size)(&src_2, q); \
			for(S32 i = 0; i < 1000; ++i) dest_2 = MODIFY_TEST_OBJECT_RET(size)(src_2); \
		U64 t2 = time_get_ns(); \
		\
		printf("return time / pointer time = %f\n", (F32)(t2 - t1) / (F32)(t1 - t0)); \
	test_end()

MAKE_OBJECT(4)
MAKE_OBJECT(8)
MAKE_OBJECT(12)
MAKE_OBJECT(16)
MAKE_OBJECT(20)
MAKE_OBJECT(24)
MAKE_OBJECT(32)
MAKE_OBJECT(64)
MAKE_OBJECT(128)
MAKE_OBJECT(256)
MAKE_OBJECT(512)
MAKE_OBJECT(1024)

void speed_test(){
	U8 q = (U8)random_get_uniform(256);

	SPEED_TEST_SIZE(4)
	SPEED_TEST_SIZE(8)
	SPEED_TEST_SIZE(12)
	SPEED_TEST_SIZE(16)
	SPEED_TEST_SIZE(20)
	SPEED_TEST_SIZE(24)
	SPEED_TEST_SIZE(32)
	SPEED_TEST_SIZE(64)
	SPEED_TEST_SIZE(128)
	SPEED_TEST_SIZE(256)
	SPEED_TEST_SIZE(512)
	SPEED_TEST_SIZE(1024)

	printf("\n");

	MODIFY_TEST(4)
	MODIFY_TEST(8)
	MODIFY_TEST(12)
	MODIFY_TEST(16)
	MODIFY_TEST(20)
	MODIFY_TEST(24)
	MODIFY_TEST(32)
	MODIFY_TEST(64)
	MODIFY_TEST(128)
	MODIFY_TEST(256)
	MODIFY_TEST(512)
	MODIFY_TEST(1024)


	test_passed();
}
