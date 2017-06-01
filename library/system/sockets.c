// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include <library/master.h>

#include <library/allocator.h>
#include <library/error.h>
#include <library/system/sockets.h>

DEFINE_TYPE(ae_socket)

static ae_socket* socket_id = nullptr;

void socket_init(in ae_ip_port* listen_port){
	// If we already have a socket, return
	if(socket_id) return;

	// Create a socket
	socket_id = allocate(ae_socket);
	socket_platform(socket_id);

	// Set socket options
	socket_noblock_platform(socket_id);
	socket_reuseaddr_platform(socket_id);

	// Bind socket to given listening port
	socket_bind_platform(socket_id, listen_port);
}

void socket_send(in ae_ipaddr_port* dest, in void* data, in U32 length){
	assert(data);
	assert(length > 0);
	socket_send_platform(socket_id, dest, data, length);
}

void socket_receive(ae_receiver_fn fn){
	socket_receive_platform(socket_id, fn);
}
