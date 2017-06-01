// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include <library/system/random.h>

#if defined(AE_PLATFORM_APPLE)

#include <stdlib.h>

void random_stir_platform(){
	arc4random_stir();
}

void random_add_entropy_platform(in U8* data, in U32 length){
	arc4random_addrandom((U8*)data, length);
}

void random_get_bytes_platform(out U8* dest, in U32 length){
	arc4random_buf(dest, length);
}

U32 random_get_uniform_platform(in U32 upper_bound){
	return arc4random_uniform(upper_bound);
}

#endif
