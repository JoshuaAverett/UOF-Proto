// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "task.h"

#include <library/allocator.h>

DEFINE_TYPE(ae_task)
DEFINE_TYPE(ae_task_node)

static void task_queue_get_lock(in_out ae_task_queue* obj){
	bool ret;
	do{
		bool false_val = false;
		ret = atomic_compare_exchange_weak(&obj->lock, &false_val, true);
	} while(!ret);
}

static void task_queue_clear_lock(in_out ae_task_queue* obj){
	atomic_store(&obj->lock, false);
}

void create_task(in_out ae_task* obj, in U32 priority, in ae_task_fn fn, in_out void* arg){
	obj->priority = priority;
	obj->fn = fn;
	obj->arg = arg;
}

void destroy_task(in_out ae_task* obj){
}

void create_task_manager(in_out ae_task_manager* obj){
	atomic_store(&obj->running_tasks, 0);
	for(U32 i = 0; i < MAX_TASK_PRIORITY; ++i){
		task_queue_clear_lock(&obj->priorities[i]);
		obj->priorities[i].front = nullptr;
		obj->priorities[i].back = nullptr;
	}
}

void destroy_task_manager(in_out ae_task_manager* obj){
	for(U32 i = 0; i < MAX_TASK_PRIORITY; ++i){
		task_queue_get_lock(&obj->priorities[i]);
		while(obj->priorities[i].front){
			ae_task_node* node = obj->priorities[i].front;
			obj->priorities[i].front = node->next;
			deallocate(node);
		}
	}
}

void task_manager_add_task(in_out ae_task_manager* obj, in ae_task* task){
	U32 priority = task->priority;
	task_queue_get_lock(&obj->priorities[priority]);

	ae_task_node* node = allocate(ae_task_node);

	node->task = *task;
	node->next = nullptr;

	if(!obj->priorities[priority].front) obj->priorities[priority].front = node;
	if(obj->priorities[priority].back) obj->priorities[priority].back->next = node;
	obj->priorities[priority].back = node;

	task_queue_clear_lock(&obj->priorities[priority]);
}

bool task_manager_run_task(in_out ae_task_manager* obj){
	ae_task_node* node;
	U32 i;

	for(i = 0; i < MAX_TASK_PRIORITY; ++i){
		task_queue_get_lock(&obj->priorities[i]);
		node = obj->priorities[i].front;
		if(node) break;
		task_queue_clear_lock(&obj->priorities[i]);
	}

	// Make sure we got a valid node
	if(!node) return false;

	// If so, advance the queue, and unlock
	obj->priorities[i].front = node->next;
	task_queue_clear_lock(&obj->priorities[i]);

	atomic_fetch_add(&obj->running_tasks, 1);
	node->task.fn(node->task.arg);
	atomic_fetch_sub(&obj->running_tasks, 1);

	deallocate(node);

	return true;
}

bool task_manager_has_task(in_out ae_task_manager* obj){
	if(atomic_load(&obj->running_tasks) > 0) return true;

	for(U32 i = 0; i < MAX_TASK_PRIORITY; ++i){
		if(obj->priorities[i].front) return true;
	}

	return false;
}

void task_manager_thread_fn(void* arg){
	ae_task_manager* task_manager = arg;

	while(task_manager_has_task(task_manager)){
		task_manager_run_task(task_manager);
	}
}
