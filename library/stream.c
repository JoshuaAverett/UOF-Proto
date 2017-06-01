// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "stream.h"

void create_stream(in_out ae_stream* obj){
	create_serializer(stream_serializer(obj));
	obj->index = 0;
}

void create_stream_init(in_out ae_stream* obj, in U8* data, in U32 length){
	obj->length = length;
	obj->reserved = length;
	obj->data = (U8*)data;
	obj->index = 0;
}

void destroy_stream(in_out ae_stream* obj){
	destroy_serializer(stream_serializer(obj));
}

ae_serializer* stream_serializer(in ae_stream* obj){
	// Because the stream and serializer have the same layout, this works fine
	return (ae_serializer*)obj;
}

ae_deserializer* stream_deserializer(in ae_stream* obj){
	// The deserializer start with data, so we convert the pointer from U8** to ae_deserializer*
	return (ae_deserializer*)&obj->data;
}

void stream_reserve(in_out ae_stream* obj, in U32 size){
	serializer_reserve(stream_serializer(obj), size);
}

U32 stream_index(in ae_stream* obj){
	return obj->index;
}

U32 stream_length(in ae_stream* obj){
	return obj->length;
}
