// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include "test.h"

#include <library/event.h>
#include <library/network/circuit.h>
#include <library/network/packets/packet-list.h>

void test_print(void* arg){
	const ae_packet_test* packet = arg;

	printf("%s\n", packet->message);
}

void handle_create_circuit(void* arg){
	const ae_packet_create_circuit* packet = arg;

	printf("Got circuit create\n");

	ae_circuit* new_circuit = allocate(ae_circuit);
	create_circuit(new_circuit, &packet->source);

	ae_packet created;
	create_packet(&created, PACKET_CIRCUIT_CREATED);

	circuit_send_packet_immediate(new_circuit, 0, &created);
	new_circuit->state = CIRCUIT_OPEN;

	destroy_packet(&created);
}

void handle_circuit_created(void* arg){
	const ae_packet_circuit_created* packet = arg;

	printf("Got circuit created\n");

	ae_circuit* circ = circuit_find(&packet->source);
	circ->state = CIRCUIT_OPEN;
}

void circuit_test(){
	ae_circuit receiver, sender;

	REGISTER_EVENT(packet_create_circuit, handle_create_circuit);
	REGISTER_EVENT(packet_circuit_created, handle_circuit_created);
	REGISTER_EVENT(packet_test, test_print);

	ae_ip_port port = { CIRCUIT_LISTEN_PORT };
	socket_init(&port);

	test_start("Creating a receiver")
		create_circuit_listener(&receiver);
	test_end()

	test_start("Creating a circuit")
		ae_ipaddr_port localhost_port = {
			.address = localhost,
			.port = CIRCUIT_LISTEN_PORT,
		};

		create_circuit(&sender, &localhost_port);
		circuit_connect(&sender);

		circuit_receive(); // Get the circuit_create
		circuit_receive(); // Get the circuit_created
	test_end()

	test_start("Send packet with circuit")
		ae_packet test;
		create_packet_test(&test, "Test packet works!");
		circuit_send_packet_immediate(&sender, 0, &test);
		destroy_packet(&test);
	test_end()

	test_start("Receive packet")
		circuit_receive();
	test_end()

	test_passed();
}
