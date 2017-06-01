// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "packet-stream-created.h"

DEFINE_EVENT(packet_stream_created)

void create_packet_stream_created(in_out ae_packet* obj){
	create_packet(obj, PACKET_STREAM_CREATED);
}

void packet_stream_created_decode(in ae_ipaddr_port* source, in_out ae_packet* packet){
	ae_packet_stream_created ret;

	HANDLE_EVENT(packet_stream_created, &ret);
}
