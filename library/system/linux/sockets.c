// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include <library/master.h>

#if defined(AE_PLATFORM_LINUX)

#include <library/error.h>
#include <library/system/sockets.h>

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

void socket_platform(in_out ae_socket* obj){
	*(int*)obj = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(*(int*)obj <= 0) goto clean_socket;

	return;

clean_socket:
	error(ERROR_SOCKET);
}

void socket_noblock_platform(in ae_socket* s){
	if(fcntl(*(int*)s, F_SETFL, O_NONBLOCK) == -1) goto clean_set_options;

	return;

clean_set_options:
	close(*(int*)s);
	error(ERROR_SOCKET);
}

void socket_reuseaddr_platform(in ae_socket* s){
	int true_val = true;
	if(setsockopt(*(int*)s, SOL_SOCKET, SO_REUSEADDR, &true_val, sizeof(true_val))) goto clean_set_options;

#if defined(SO_REUSEPORT)
	if(setsockopt(*(int*)s, SOL_SOCKET, SO_REUSEPORT, &true_val, sizeof(true_val))) goto clean_set_options;
#endif

	return;

clean_set_options:
	close(*(int*)s);
	error(ERROR_SOCKET);
}

void socket_bind_platform(in ae_socket* s, in ae_ip_port* listen_port){
	struct sockaddr_in us = {
		.sin_family = AF_INET,
		.sin_port = htons(listen_port->value),
		.sin_addr.s_addr = INADDR_ANY,
	};

	if(bind(*(int*)s, (struct sockaddr*)&us, sizeof(us))) goto clean_bind;

	return;

clean_bind:
	close(*(int*)s);
	error(ERROR_SOCKET);
}

void socket_send_platform(in ae_socket* s, in ae_ipaddr_port* dest, in void* data, in U32 length){
	struct sockaddr_in dest_conv = {
		.sin_family = AF_INET,
		.sin_port = htons(dest->port.value),
		.sin_addr.s_addr = *(long*)&dest->address.value,
	};

	if(sendto(*(int*)s, data, length, 0, (struct sockaddr*)&dest_conv, sizeof(dest_conv)) < 0) goto clean_sendto;

	return;

clean_sendto:
	error(ERROR_SOCKET);
}

void socket_receive_platform(in ae_socket* s, ae_receiver_fn fn){
	U8 buffer[65536];
	struct sockaddr_in source;

	U32 source_len = sizeof(source);
	S32 received = recvfrom(*(int*)s, buffer, sizeof(buffer), 0, (struct sockaddr*)&source, &source_len);
	if(received > 0){
		ae_ipaddr_port ip_port;
		memcpy(&ip_port.address.value, &source.sin_addr.s_addr, sizeof(ip_port.address));
		ip_port.port.value = ntohs(source.sin_port);

		fn(&ip_port, buffer, received);
	}
}

#endif
