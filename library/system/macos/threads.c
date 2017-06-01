// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include <library/master.h>

#ifdef AE_PLATFORM_APPLE

#include <library/system/threads.h>
#include <library/error.h>

#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

static thread_local U32 thread_id;

void* platform_thread_fn(void* void_arg){
	ae_thread_arg* arg = void_arg;
	ae_thread_fn fn = arg->fn;
	void* fn_arg = arg->arg;
	thread_id = arg->id;
	arg->started = true;
	atomic_thread_fence(memory_order_release);

	fn(fn_arg);

	ATOMIC_BIT_VECTOR_CLEAR(MAX_THREAD_COUNT)(&threads_used, thread_id);

	return nullptr;
}

U32 threads_get_prefered_count_platform(){
	return sysconf(_SC_NPROCESSORS_ONLN);
}

void create_thread_platform(ae_thread_arg* arg){
	pthread_attr_t attr;
	pthread_t thread;
	int ret;

	ret = pthread_attr_init(&attr);
	if(ret) goto clean_attr;

	ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(ret) goto clean_attr;

	ret = pthread_create(&thread, &attr, platform_thread_fn, arg);
	if(ret) goto clean_thread;

	return;

clean_thread:
clean_attr:
	pthread_attr_destroy(&attr);
	error(ERROR_THREAD);
}

void thread_yield_platform(){
	int ret;

	ret = sched_yield();
	if(ret) goto clean_yield;

	return;

clean_yield:
	error(ERROR_THREAD);
}

void thread_sleep_platform(in F32 time){
	int ret;
	struct timespec request, remainder;

	request.tv_sec = (int)time;
	request.tv_nsec = (long)(time * 1E9);

	ret = nanosleep(&request, &remainder);
	if(ret) goto clean_sleep;

	return;

clean_sleep:
	if(errno == EINTR){
		while(ret == -1 && errno ==  EINTR){
			request = remainder;
			ret = nanosleep(&request, &remainder);
		}

		return;
	} else{
		error(ERROR_SLEEP);
	}
}

U32 thread_get_id_platform(){
	return thread_id;
}

#endif
