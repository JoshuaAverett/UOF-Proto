// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "packet-circuit-created.h"

DEFINE_EVENT(packet_circuit_created)

void create_packet_circuit_created(in_out ae_packet* obj){
	create_packet(obj, PACKET_CIRCUIT_CREATED);
}

void packet_circuit_created_decode(in ae_ipaddr_port* source, in_out ae_packet* packet){
	ae_packet_circuit_created ret;
	ret.source = *source;

	HANDLE_EVENT(packet_circuit_created, &ret);
}
