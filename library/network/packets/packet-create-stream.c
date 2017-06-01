// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "packet-create-stream.h"

DEFINE_EVENT(packet_create_stream)

void create_packet_create_stream(in_out ae_packet* obj, in ae_packet_stream* data){
	create_packet(obj, PACKET_CREATE_STREAM);
}

void packet_create_stream_decode(in ae_ipaddr_port* source, in_out ae_packet* packet){
	ae_packet_create_stream ret;

	HANDLE_EVENT(packet_create_stream, &ret);
}
