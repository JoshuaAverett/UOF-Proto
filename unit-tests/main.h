// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <boost/preprocessor/library.hpp>

#define DO_TESTS() \
	BOOST_PP_SEQ_FOR_EACH(DO_TEST, BOOST_PP_EMPTY, TESTS)

#define DO_TEST(r, data, elem) \
	printf("Testing module \"%s\"\n", BOOST_PP_STRINGIZE(elem)); \
	BOOST_PP_CAT(elem, _test)(); \
	printf("\n\n");

#define INCLUDE_TEST(i) \
	BOOST_PP_STRINGIZE(BOOST_PP_SEQ_ELEM(i, TESTS)-test.h)

#if BOOST_PP_SEQ_SIZE(TESTS) >= 1
#  include INCLUDE_TEST(0)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 2
#  include INCLUDE_TEST(1)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 3
#  include INCLUDE_TEST(2)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 4
#  include INCLUDE_TEST(3)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 5
#  include INCLUDE_TEST(4)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 6
#  include INCLUDE_TEST(5)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 7
#  include INCLUDE_TEST(6)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 8
#  include INCLUDE_TEST(7)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 9
#  include INCLUDE_TEST(8)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 10
#  include INCLUDE_TEST(9)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 11
#  include INCLUDE_TEST(10)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 12
#  include INCLUDE_TEST(11)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 13
#  include INCLUDE_TEST(12)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 14
#  include INCLUDE_TEST(13)
#endif

#if BOOST_PP_SEQ_SIZE(TESTS) >= 15
#  error too many tests
#endif
