// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>
#include <library/collections/vector.h>

#include <boost/preprocessor/library.hpp>

typedef void(*ae_event_handler)(void* event_data);
DECLARE_TYPE(ae_event_handler)

DEFINE_VECTOR(ae_event_handler)

#define HANDLER_LIST(name) \
	BOOST_PP_CAT(event_list_, name)

#define DECLARE_EVENT(name) \
	global VECTOR(ae_event_handler) HANDLER_LIST(name);

#define DEFINE_EVENT(name) \
	VECTOR(ae_event_handler) HANDLER_LIST(name) = { .reserved = 0 };

#define REGISTER_EVENT(event, fn) \
	VECTOR_APPEND(ae_event_handler)(&HANDLER_LIST(event), fn)

#define HANDLE_EVENT(event, arg) \
	do{ \
		for(S32 i = 0; i < VECTOR_LENGTH(ae_event_handler)(&HANDLER_LIST(event)); ++i){ \
			(VECTOR_GET(ae_event_handler)(&HANDLER_LIST(event), i))(arg); \
		} \
	} while(0)
