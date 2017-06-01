// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "packet-header.h"

typedef struct{
	ae_ipaddr_port source;
	char* message;
} ae_packet_test;

DECLARE_EVENT(packet_test)

void create_packet_test(in_out ae_packet* obj, in char* message);
void packet_test_decode(in ae_ipaddr_port* source, in_out ae_packet* packet);
