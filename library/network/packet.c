// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "packet.h"

#include <library/master.h>
#include <library/collections/hash-table.h>
#include <library/network/packets/packet-list.h>

ae_packet_handler_fn packet_handlers[] = {
	[PACKET_CREATE_CIRCUIT] = packet_create_circuit_decode,
	[PACKET_CIRCUIT_CREATED] = packet_circuit_created_decode,

	[PACKET_CREATE_STREAM] = packet_create_stream_decode,
	[PACKET_STREAM_CREATED] = packet_stream_created_decode,

	[PACKET_TEST] = packet_test_decode
};

void create_packet(in_out ae_packet* obj, in ae_packet_type type){
	create_stream(obj);
	stream_write(obj, blank, PACKET_HEADER_MAX_SIZE);

	// Set the type before the body
	stream_write(obj, varint, (U32)type);
}

void destroy_packet(in_out ae_packet* obj){
	destroy_stream(obj);
}

void packet_dispatch(in ae_ipaddr_port* dest, in U8* data, in U32 size){
	ae_packet packet;
	create_stream_init(&packet, data, size);

	while(packet_index(&packet) < packet_length(&packet)){
		U32 packet_type = 0;
		packet_read(&packet, varint, &packet_type);

		ae_packet_handler_fn fn = packet_handlers[packet_type];
		fn(dest, &packet);
	}
}

void* packet_data(in ae_packet* obj){
	// Insert the full packet header
	U32 header_size = 0;

	return &obj->data[header_size];
}

U32 packet_index(in ae_packet* obj){
	return stream_index(obj);
}

U32 packet_length(in ae_packet* obj){
	return stream_length(obj);
}
