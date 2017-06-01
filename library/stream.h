// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/serializer.h>
#include <library/deserializer.h>

typedef struct packed{
	U32 length;
	U32 reserved;
	U8* data;
	U32 index;
} ae_stream;

void create_stream(in_out ae_stream* obj);
void create_stream_init(in_out ae_stream* obj, in U8* data, in U32 length);
void destroy_stream(in_out ae_stream* obj);

ae_serializer* stream_serializer(in ae_stream* obj);
ae_deserializer* stream_deserializer(in ae_stream* obj);

void stream_reserve(in_out ae_stream* obj, in U32 size);

U32 stream_length(in ae_stream* obj);
U32 stream_index(in ae_stream* obj);

#define stream_write(obj, type, ...) \
	serialize(stream_serializer(obj), type, __VA_ARGS__)

#define stream_read(obj, type, ...) \
	deserialize(stream_deserializer(obj), type, __VA_ARGS__)
