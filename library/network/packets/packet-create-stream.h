// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "packet-header.h"

typedef struct{
	U8 flags;
} ae_packet_create_stream;

DECLARE_EVENT(packet_create_stream)
void create_packet_create_stream(in_out ae_packet* obj, in ae_packet_stream* stream_data);
void packet_create_stream_decode(in ae_ipaddr_port* source, in_out ae_packet* packet);
