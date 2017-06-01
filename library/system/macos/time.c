// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include <library/master.h>

#if defined(AE_PLATFORM_APPLE)

#include <library/error.h>

#include <library/system/time.h>

#include <time.h>

#include <mach/clock.h>
#include <mach/mach.h>

U64 time_get_ns_platform(){
	kern_return_t kr;
	clock_serv_t cs;
	mach_timespec_t mts;

	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cs);
	kr = clock_get_time(cs, &mts);
	mach_port_deallocate(mach_task_self(), cs);
	if(kr != KERN_SUCCESS) goto clock_clean;

	return mts.tv_sec * 1000000000ULL + mts.tv_nsec;

clock_clean:
	error(ERROR_TIME);
}

#endif
