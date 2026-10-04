#pragma once

#include <types.h>

typedef struct setup_resp {
	enum : uint8 {
		fail = 0,
		success = 1,
	} status;
	uint8 reason_len;
	struct { uint16 major, minor; } version;
	uint16 len;
	uint32 release;
	struct { uint32 base, mask; } res;
	uint32 motion_buffer_size;
	uint16 vendor_len;
	uint16 max_req_len;
	uint8 roots_len;
	uint8 pixmaps_len;
	uint8 image_byte_order;
	struct {
		uint8 bit_order;
		struct { uint8 unit, pad; } scanline;
	} bitmap;
	struct { uint8 min, max; } keycodes;
	uint8 _[4];
} setup_resp_t;
