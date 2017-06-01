// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>
#include <library/network/ip-address.h>

// A dummy type for platforms to have their own version of this object
DEFINE_CONSTANT(SOCKET_PLATFORM_SIZE, 8);
typedef U8 ae_socket[SOCKET_PLATFORM_SIZE];
DECLARE_TYPE(ae_socket)

// Interface

// Initializes a sending port
void socket_init(in ae_ip_port* listen_port);

// Sends data to a given destination using a given socket
void socket_send(in ae_ipaddr_port* dest, in void* data, in U32 length);

// Dispatches the receiver on all recieved data since the last call
typedef void(*ae_receiver_fn)(in ae_ipaddr_port* source, in U8* data, in U32 size);
void socket_receive(ae_receiver_fn fn);

// Platform
void socket_platform(in_out ae_socket* s);
void socket_noblock_platform(in ae_socket* s);
void socket_reuseaddr_platform(in ae_socket* s);
void socket_bind_platform(in ae_socket* s, in ae_ip_port* listen_port);
void socket_send_platform(in ae_socket* s, in ae_ipaddr_port* dest, in void* data, in U32 length);
void socket_receive_platform(in ae_socket* s, ae_receiver_fn fn);
