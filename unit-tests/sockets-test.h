// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>
#include <library/system/sockets.h>
#include <library/system/threads.h>

#include <string.h>
#include <unistd.h>

bool waiting = false;

void test_reciever(in ae_ipaddr_port* source, in U8* data, in U32 length){
	printf("Message from %d.%d.%d.%d(%d): %s\n",
		source->address.value[0], source->address.value[1],
		source->address.value[2], source->address.value[3],
		source->port.value, data);
	waiting = true;
}

void sockets_test(){
	ae_ipaddr_port localhost_port = {
		.address = localhost,
		.port.value = 1234,
	};

	test_start("Init socket")
		socket_init(&localhost_port.port);
	test_end()

	test_start("Socket send")
		char* test_data = "Socket works!";
		socket_send(&localhost_port, test_data, strlen(test_data) + 1);
	test_end()

	sleep(1);

	test_start("Socket receive")
		socket_receive(test_reciever);
		thread_wait(pred_identity, &waiting, 1.f);
	test_end()

	test_passed();
}
