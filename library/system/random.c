// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "random.h"

void random_stir(){
	random_stir_platform();
}

void random_add_entropy(in U8* data, in U32 length){
	random_add_entropy_platform(data, length);
}

void random_get_bytes(out U8* dest, in U32 length){
	random_get_bytes_platform(dest, length);
}

U32 random_get_uniform(in U32 upper_bound){
	// apple has a special version of this
	return random_get_uniform_platform(upper_bound);
}
