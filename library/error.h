// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>

typedef enum{
	ERROR_THREAD = 1,
	ERROR_SLEEP,
	ERROR_TIME_OUT,
	ERROR_TIME,
	ERROR_SOCKET,
	ERROR_RANDOM,
} ae_error;

noreturn void error(in ae_error err);
