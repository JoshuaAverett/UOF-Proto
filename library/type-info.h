// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>

#include <boost/preprocessor/library.hpp>

typedef struct{
	U32 size;
	cstring name;
} ae_type_info;

#define TYPE_INFO(type) \
	BOOST_PP_CAT(type_info_, type)

#define DECLARE_TYPE(type) \
	extern const ae_type_info TYPE_INFO(type);

#define DEFINE_TYPE(type) \
	const ae_type_info TYPE_INFO(type) = { \
		.size = sizeof(type), \
		.name = BOOST_PP_STRINGIZE(type), \
	};
