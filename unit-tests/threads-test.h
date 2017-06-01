// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <library/master.h>
#include <library/system/threads.h>

void test_fn(void* arg){
	printf("Thread created!\n");
	*(bool*)arg = true;
}

void threads_test(){
	test_start("Create thread")
		bool t0 = false;
		create_thread(test_fn, &t0);
		thread_wait(pred_identity, &t0, 1.f);
	test_end()

	test_passed();
}
