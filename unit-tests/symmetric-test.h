// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <library/master.h>
#include <library/crypto/asymmetric.h>
#include <library/crypto/symmetric.h>

void symmetric_test(){
	ae_shared_key key;
	memclear(key);

	ae_symetric_context ctx;

	U8 source[64];
	U8 encrypted[64];
	U8 check[64];
	U8 decrypted[64];

	for(U32 i = 0; i < 64; ++i) source[i] = 0;

	char* check_str = "76b8e0ada0f13d90405d6ae55386bd28bdd219b8a08ded1aa836efcc8b770dc7da41597c5157488d7724e03fb8d84a376a43b8f41518a11cc387b669b2ee6586";
	for(U32 i = 0; i < 64; ++i){
		sscanf(&check_str[i * 2], "%2hhx", &check[i]);
	}

	test_start("Create context")
		symetric_context_create(&ctx, &key, 0);
	test_end()

	test_start("Encrypt")
		symetric_encrypt(encrypted, &ctx, source, 64);
		for(U32 i = 0; i < 64; ++i) assert(check[i] == encrypted[i]);
	test_end()

	test_start("Decrypt")
		ae_symetric_context dec_ctx;
		symetric_context_create(&dec_ctx, &key, 0);
		symetric_encrypt(decrypted, &dec_ctx, encrypted, 64);
		for(U32 i = 0; i < 64; ++i) assert(decrypted[i] == source[i]);
	test_end()

	test_passed();
}
