// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "packet-create-circuit.h"

DEFINE_EVENT(packet_create_circuit)

void create_packet_create_circuit(in_out ae_packet* obj){
	create_packet(obj, PACKET_CREATE_CIRCUIT);
}

void packet_create_circuit_decode(in ae_ipaddr_port* source, in_out ae_packet* packet){
	ae_packet_create_circuit ret;
	ret.source = *source;

	HANDLE_EVENT(packet_create_circuit, &ret);
}
