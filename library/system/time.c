// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "time.h"

#include <library/master.h>

U64 time_get_ns(){
	return time_get_ns_platform();
}
