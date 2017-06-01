// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#include <library/master.h>
#include <library/serializer.h>

void compress(in_out ae_serializer* dest, in U8* source, in U32 length);
void decompress(in_out ae_serializer* dest, in U8* source, in U32 length);
