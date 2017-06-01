// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "packet-header.h"

typedef struct{
	ae_ipaddr_port source;
} ae_packet_create_circuit;

DECLARE_EVENT(packet_create_circuit)
void create_packet_create_circuit(in_out ae_packet* obj);
void packet_create_circuit_decode(in ae_ipaddr_port* source, in_out ae_packet* packet);
