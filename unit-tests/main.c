// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#define TESTS \
	(compiler) \
	(allocator) \
	(threads) \
	(sockets) \
	(vector) \
	(hash_table) \
	(serializer) \
	(deserializer) \
	(stream) \
	(symmetric) \
	(circuit) \
	(speed) \
	(task)

#include "main.h"

int main(){
	printf("Starting tests\n\n");

	DO_TESTS()

	printf("Tests complete\n");

	return 0;
}
