// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>
#include <library/collections/vector.h>
#include <library/crypto/asymmetric.h>
#include <library/network/ip-address.h>
#include <library/network/packet.h>

// A circuit represents an outstanding connection between two clients

DEFINE_CONSTANT(CIRCUIT_LISTEN_PORT, 1234)

typedef enum{
	STREAM_CLOSED,
	STREAM_HALF_OPEN,
	STREAM_OPEN,
} ae_stream_state;

enum{
	// A packet sent on a reliable channel will either arrive, or the circuit will time out
	STREAM_FLAG_RELIABLE = 1 << 0,

	// if(reliable) the stream will hold packets to make sure they all arrive in order, with none dropped
	// else the stream will drop all packets with IDs lower than the current packet's ID
	STREAM_FLAG_ORDERED = 1 << 1,

	// The stream is encrypted with the circuit shared secret
	STREAM_FLAG_ENCRYPTED = 1 << 2,

	// The stream has compression run on it, all packets are compressed
	// WARNING: when combined with encryption, could lead to a CRIME attack
	//   be careful combining these options
	STREAM_FLAG_COMPRESSED = 1 << 3,
};

typedef struct{
	U8 flags;
	ae_stream_state state;
} ae_packet_stream;

DECLARE_TYPE(ae_packet_stream)
DEFINE_VECTOR(ae_packet_stream)

typedef enum{
	CIRCUIT_CLOSED,
	CIRCUIT_HALF_OPEN,
	CIRCUIT_OPEN,
} ae_circuit_state;

typedef struct{
	ae_circuit_state state;
	ae_ipaddr_port their_location;
	VECTOR(ae_packet_stream) streams;
} ae_circuit, *ae_circuit_p;

DECLARE_TYPE(ae_circuit)

// Creates a circuit to a given destination
void create_circuit(in_out ae_circuit* obj, in ae_ipaddr_port* them);
// Creates a listener to accept new circuits
void create_circuit_listener(in_out ae_circuit* obj);
// Destroys a circuit
void destroy_circuit(in_out ae_circuit* obj);

// Gets the circuit from the ip
ae_circuit* circuit_find(in ae_ipaddr_port* port);

// Adds a stream to the circuit, returns stream ID
U32 circuit_create_stream(in_out ae_circuit* obj, in ae_packet_stream* stream);

// Sends a packet across a circuit
void circuit_send_packet(in_out ae_circuit* obj, in U32 stream, in ae_packet* packet);
// Sends a packet without waiting for MTU bundling to happen
void circuit_send_packet_immediate(in_out ae_circuit* obj, in U32 stream, in ae_packet* packet);

// Checks for any received packets
void circuit_receive();

// Sends the set of packets needed to connect a circuit, or errors
void circuit_connect(in_out ae_circuit* obj);

// Checks if a circuit is open
bool pred_circuit_open(in void* arg);
