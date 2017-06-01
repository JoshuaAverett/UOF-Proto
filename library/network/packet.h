// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>
#include <library/serializer.h>
#include <library/stream.h>
#include <library/network/ip-address.h>

typedef enum{
	PACKET_CREATE_CIRCUIT,
	PACKET_CIRCUIT_CREATED,

	PACKET_CREATE_STREAM,
	PACKET_STREAM_CREATED,

	PACKET_TEST = (1 << 14) - 1,
	MAX_PACKET_TYPE
} ae_packet_type;

DEFINE_CONSTANT(PACKET_HEADER_MAX_SIZE, sizeof(varint))

typedef ae_stream ae_packet;

typedef void(*ae_packet_handler_fn)(in ae_ipaddr_port* source, in_out ae_packet* packet);

global ae_packet_handler_fn packet_handlers[MAX_PACKET_TYPE];

void create_packet(in_out ae_packet* obj, in ae_packet_type type);
void destroy_packet(in_out ae_packet* obj);

void packet_dispatch(in ae_ipaddr_port* source, in U8* data, in U32 size);

#define packet_read stream_read
#define packet_write stream_write

void* packet_data(in ae_packet* obj);
U32 packet_index(in ae_packet* obj);
U32 packet_length(in ae_packet* obj);
