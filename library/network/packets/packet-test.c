// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#include "packet-test.h"

DEFINE_EVENT(packet_test)

void create_packet_test(in_out ae_packet* obj, in char* message){
	create_packet(obj, PACKET_TEST);
	packet_write(obj, string, message);
}

void packet_test_decode(in ae_ipaddr_port* source, in_out ae_packet* packet){
	ae_packet_test ret;
	ret.source = *source;

	packet_read(packet, string, &ret.message);

	HANDLE_EVENT(packet_test, &ret);
}
