// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "threads.h"

#include <library/error.h>
#include <library/system/time.h>

// Interface

ATOMIC_BIT_VECTOR(MAX_THREAD_COUNT) threads_used = { 1 };

U32 threads_get_prefered_count(){
	return threads_get_prefered_count_platform();
}

void create_thread(in ae_thread_fn fn, in_out void* arg){
	S32 thread_id = ATOMIC_BIT_VECTOR_DEQUEUE_0(MAX_THREAD_COUNT)(&threads_used);
	if(thread_id == -1) goto clean_thread_count;

	ae_thread_arg thread_arg = {
		.fn = fn,
		.arg = arg,
		.started = false,
		.id = thread_id,
	};

	create_thread_platform(&thread_arg);

	// We have to wait for the thread to start before we kill the thread_arg
	thread_wait(pred_identity, &thread_arg.started, THREAD_START_TIMEOUT);

	return;

clean_thread_count:
	error(ERROR_THREAD);
}

void thread_yield(){
	thread_yield_platform();
}

void thread_sleep(in F32 time){
	if(time < 0.f) error(ERROR_SLEEP);
	thread_sleep_platform(time);
}

U32 thread_get_id(){
	return thread_get_id_platform();
}

void thread_wait(in ae_predicate pred, in void* arg, in F32 timeout){
	U64 timeout_ns = (U64)(timeout * 1E9);
	U64 time_start_ns = time_get_ns();

	int delay = 0;
	while(!pred(arg)){
		U64 time_spent_ns = time_get_ns() - time_start_ns;
		if(time_spent_ns > timeout_ns) error(ERROR_TIME_OUT);

		// Exponential backoff
		// NOTE: constants picked more or less at random
		if(delay < 10){
			_mm_pause();
		} else if(delay < 20){
			int i;
			for(i = 0; i < 50; ++i) _mm_pause();
		} else if(delay < 25){
			thread_yield();
		} else if(delay < 30){
			thread_sleep(0.001f);
		} else if(delay < 35){
			thread_sleep(0.01f);
		} else if(delay < 40){
			thread_sleep(0.1f);
		} else{
			thread_sleep(1.0f);
		}
	}
}

// Helpers

bool pred_identity(in void* arg){
	atomic_thread_fence(memory_order_acquire);
	return *(bool*)arg;
}
