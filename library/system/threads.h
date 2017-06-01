// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>
#include <library/collections/atomic-bit-vector.h>

// Interface

#define THREAD_START_TIMEOUT (0.1f)
#define MAX_THREAD_COUNT 32

DEFINE_ATOMIC_BIT_VECTOR(MAX_THREAD_COUNT)

global ATOMIC_BIT_VECTOR(MAX_THREAD_COUNT) threads_used;

typedef void(*ae_thread_fn)(in_out void* argument);
typedef bool(*ae_predicate)(in void* argument);

typedef struct{
	ae_thread_fn fn;
	void* arg;
	bool started;
	U32 id;
} ae_thread_arg;

U32 threads_get_prefered_count();

void create_thread(in ae_thread_fn fn, in_out void* arg);

void thread_yield();
void thread_sleep(in F32 time);
U32 thread_get_id();
void thread_wait(in ae_predicate pred, in void* arg, in F32 timeout);

// Platform

U32 threads_get_prefered_count_platform();

void create_thread_platform(ae_thread_arg* arg);
void thread_yield_platform();
void thread_sleep_platform(F32 time);
U32 thread_get_id_platform();

// Helpers

bool pred_identity(in void* arg);
