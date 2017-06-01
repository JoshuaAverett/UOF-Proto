// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>

DEFINE_CONSTANT(MAX_TASK_PRIORITY, 4)

typedef void(*ae_task_fn)(void*);

typedef struct{
	U32 priority;
	ae_task_fn fn;
	void* arg;
} ae_task;

DECLARE_TYPE(ae_task)

typedef struct ae_task_node{
	ae_task task;
	struct ae_task_node* next;
} ae_task_node;

DECLARE_TYPE(ae_task_node)

typedef struct{
	atomic_bool lock;
	ae_task_node* front, *back;
} ae_task_queue;

typedef struct{
	atomic_U32 running_tasks;
	ae_task_queue priorities[MAX_TASK_PRIORITY];
} ae_task_manager;

void create_task(in_out ae_task* obj, in U32 priority, in ae_task_fn fn, in_out void* arg);
void destroy_task(in_out ae_task* obj);

void create_task_manager(in_out ae_task_manager* obj);
void destroy_task_manager(in_out ae_task_manager* obj);

void task_manager_add_task(in_out ae_task_manager* obj, in ae_task* task);
bool task_manager_run_task(in_out ae_task_manager* obj);
bool task_manager_has_task(in_out ae_task_manager* obj);

void task_manager_thread_fn(void* arg);
