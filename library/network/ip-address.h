// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>

// Interface

typedef struct{
	U8 value[4];
} ae_ip_address;

typedef struct{
	U16 value;
} ae_ip_port;

typedef struct{
	ae_ip_address address;
	ae_ip_port port;
} ae_ipaddr_port;

global const ae_ip_address localhost;
global const ae_ip_address any_address;
