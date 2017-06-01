// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "error.h"

#include <stdlib.h>
#include <errno.h>

void error(in ae_error err){
	int sys_errno = errno;
	fprintf(stderr, "Error %d, system error code %d\n", err, sys_errno);
	assert(false);
	exit(err);
}
