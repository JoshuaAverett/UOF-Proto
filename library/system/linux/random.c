// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include <library/system/random.h>

#if defined(AE_PLATFORM_LINUX)

#include <library/error.h>
#include <stdio.h>

void random_stir_platform(){
}

void random_add_entropy_platform(in U8* data, in U32 length){
}

void random_get_bytes_platform(out U8* dest, in U32 length){
	FILE* random = fopen("/dev/urandom", "r");
	if(!random) goto clean_file;

	if(fread(dest, sizeof(U8), length, random) != length) goto clean_read;
	fclose(random);
	return;

clean_read:
	fclose(random);

clean_file:
	error(ERROR_RANDOM);
}

U32 random_get_uniform_platform(in U32 upper_bound){
	// The range is of size 0 or 1, so return the only element
	if(upper_bound < 2) return 0;

	// Generatee the min of the range we want
	U32 min = (1ULL << 32) % upper_bound;

	// Since we filter out numbers in the range [0, min),
	// r must be in the range [min, 2^32), which maps back to [0, upper_bound)
	// after we modulo it
	U32 r;
	while(1){
		random_get_bytes((U8*)&r, sizeof(r));
		if(r >= min) break;
	}

	return r % upper_bound;
}

#endif
