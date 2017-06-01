// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "packet-header.h"

typedef struct{
	ae_ipaddr_port source;
} ae_packet_circuit_created;

DECLARE_EVENT(packet_circuit_created)

void create_packet_circuit_created(in_out ae_packet* obj);
void packet_circuit_created_decode(in ae_ipaddr_port* source, in_out ae_packet* packet);
