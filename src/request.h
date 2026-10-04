#pragma once

#include <types.h>

typedef struct setup_req {
	enum : uint8 { l = 'l', b = 'b', } byteorder;
	struct { uint16 major, minor; } version;
	struct { uint16 name_len, data_len; } auth;
	uint8 _[2];
} setup_req_t;
