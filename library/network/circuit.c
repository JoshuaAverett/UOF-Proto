// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "circuit.h"

#include <library/master.h>
#include <library/error.h>
#include <library/collections/hash-table.h>
#include <library/network/packet.h>
#include <library/system/sockets.h>
#include <library/network/packets/packet-list.h>

DEFINE_TYPE(ae_circuit)
DEFINE_TYPE(ae_packet_stream)

DEFINE_HASH_TABLE(ae_ipaddr_port, ae_circuit_p)

static HASH_TABLE(ae_ipaddr_port, ae_circuit_p)* circuit_map = nullptr;

inline void circuit_receive(){
	socket_receive(packet_dispatch);
}

void create_circuit(in_out ae_circuit* obj, in ae_ipaddr_port* them){
	obj->state = CIRCUIT_CLOSED;
	obj->their_location = *them;

	if(circuit_map == nullptr){
		circuit_map = allocate(HASH_TABLE(ae_ipaddr_port, ae_circuit_p));
		CREATE_HASH_TABLE(ae_ipaddr_port, ae_circuit_p)(circuit_map);
	}

	HASH_TABLE_SET(ae_ipaddr_port, ae_circuit_p)(circuit_map, *them, obj);
}

void create_circuit_listener(in_out ae_circuit* obj){
	ae_ipaddr_port localhost_port = {
		.address = any_address,
		.port = CIRCUIT_LISTEN_PORT,
	};

	create_circuit(obj, &localhost_port);

	// A listener is always open
	obj->state = CIRCUIT_OPEN;
}

void destroy_circuit(in_out ae_circuit* obj){
	HASH_TABLE_DELETE(ae_ipaddr_port, ae_circuit_p)(circuit_map, obj->their_location);
}

ae_circuit* circuit_find(in ae_ipaddr_port* source){
	ae_circuit* circ;
	if(!HASH_TABLE_GET(ae_ipaddr_port, ae_circuit_p)(circuit_map, *source, &circ)){
		// Request from an unknown source, route to the listener
		ae_ipaddr_port localhost_port = {
			.address = any_address,
			.port = CIRCUIT_LISTEN_PORT,
		};

		if(!HASH_TABLE_GET(ae_ipaddr_port, ae_circuit_p)(circuit_map, localhost_port, &circ)){
			// No listener set up. This shouldn't happen
			assert(false);
		}
	}

	return circ;
}

U32 circuit_create_stream(in_out ae_circuit* obj, in ae_packet_stream* stream){
	// Get the stream ID
	U32 length = VECTOR_LENGTH(ae_packet_stream)(&obj->streams);

	// Put the stream into the vector, setting its state to half open
	ae_packet_stream stream_copy = *stream;
	stream_copy.state = STREAM_HALF_OPEN;
	VECTOR_APPEND(ae_packet_stream)(&obj->streams, stream_copy);

	// Send the creation packet
	ae_packet packet;
	create_packet_create_stream(&packet, stream);
	circuit_send_packet_immediate(obj, length, &packet);
	destroy_packet(&packet);

	return length;
}

void circuit_send_packet(in_out ae_circuit* obj, in U32 stream, in ae_packet* packet){
	// Put this packet in to the FIFO
}

void circuit_send_packet_immediate(in_out ae_circuit* obj, in U32 stream, in ae_packet* packet){
	U32 header_size = 0;
	U32 header_offset = PACKET_HEADER_MAX_SIZE - header_size;

	assert(packet_length(packet) > header_offset);

	socket_send(&obj->their_location, packet_data(packet) + header_offset, packet_length(packet) - header_offset);
}

void circuit_connect(in_out ae_circuit* obj){
	// Construct a circuit creation packet
	ae_packet create_circuit;
	create_packet_create_circuit(&create_circuit);

	// Send the packet
	circuit_send_packet_immediate(obj, 0, &create_circuit);
	destroy_packet(&create_circuit);

	// Set state to partially-open
	obj->state = CIRCUIT_HALF_OPEN;
}

bool pred_circuit_open(in void* arg){
	const ae_circuit* circ = arg;
	return circ->state == CIRCUIT_OPEN;
}
