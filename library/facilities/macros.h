// Copyright (C) 76 Enterprises LLC - All Rights Reserved
// See the file "license.txt" for the full copyright notice

#pragma once

#define noreturn _Noreturn

#define min(a, b) ({ \
	typeof(a) a_val = a; \
	typeof(b) b_val = b; \
	a < b ? a : b; \
})

#define max(a, b) ({ \
	typeof(a) a_val = a; \
	typeof(b) b_val = b; \
	a > b ? a : b; \
})

#define DEFINE_CONSTANT(name, value) \
	enum { name = value };
