// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "main.h"

#include <library/task.h>
#include <library/system/threads.h>

void task_init_fn(void* arg){
	
}

void client_main(){
	// Create the task manager
	ae_task_manager task_manager;
	create_task_manager(&task_manager);

	// Fire up an init task
	ae_task init_task;
	create_task(&init_task, 0, task_init_fn, nullptr);
	task_manager_add_task(&task_manager, &init_task);

	// Fire up the threads
	U32 thread_count = threads_get_prefered_count() - 1;
	for(U32 i = 0; i < thread_count; ++i){
		create_thread(task_manager_thread_fn, &task_manager);
	}

	task_manager_thread_fn(&task_manager);
}
