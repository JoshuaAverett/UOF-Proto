// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include <library/master.h>

#if defined(AE_PLATFORM_LINUX)

#include <library/error.h>

#include <library/system/time.h>

#include <time.h>

U64 time_get_ns_platform(){
	int res;
	struct timespec time;

	res = clock_gettime(CLOCK_MONOTONIC, &time);
	if(res) goto clock_clean;

	return time.tv_sec * 1000000000ULL + time.tv_nsec;

clock_clean:
	error(ERROR_TIME);
}

#endif
