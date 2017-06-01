// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <library/master.h>
#include <library/task.h>

void task_fn(void* arg){
	*(U32*)arg = 1234;
}

void task_test(){
	ae_task t0;
	ae_task_manager uut;
	U32 test_value = 0;

	test_start("Create task")
		create_task(&t0, 0, task_fn, &test_value);
	test_end()

	test_start("Create task manager")
		create_task_manager(&uut);
	test_end()

	test_start("Enqueue task")
		task_manager_add_task(&uut, &t0);
	test_end()

	test_start("Run task")
		task_manager_run_task(&uut);
		assert(test_value == 1234);
	test_end()

	test_passed();
}
