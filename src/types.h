#pragma once

typedef signed long int64;
typedef unsigned long uint64;
typedef signed int int32;
typedef unsigned int uint32;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed char int8;
typedef unsigned char uint8;

typedef int64 i64;
typedef uint64 u64;
typedef int32 i32;
typedef uint32 u32;
typedef int16 i16;
typedef uint16 u16;
typedef int8 i8;
typedef uint8 u8;

typedef enum keybuttonmask : uint32 {
	shift         = 1<<0,
	caps_lock     = 1<<1,
	control       = 1<<2,
	alt           = 1<<3,
	num_lock      = 1<<4,
	scroll_lock   = 1<<5,
	super         = 1<<6,
	alt_gr        = 1<<7,
	left_button   = 1<<8,
	middle_button = 1<<9,
	right_button  = 1<<10,
	wheel_up      = 1<<11,
	wheel_down    = 1<<12,
} keybuttonmask_t;

typedef enum gravity : uint32 {
	north_west = 1,
	north      = 2,
	north_east = 3,
	west       = 4,
	center     = 5,
	east       = 6,
	south_west = 7,
	south      = 8,
	south_east = 9,
} gravity_t;

typedef enum event : uint32 {
	key_press         = 2,
	key_release       = 3,
	button_press      = 4,
	button_release    = 5,
	motion_notify     = 6,
	enter_notify      = 7,
	leave_notify      = 8,
	focus_in          = 9,
	focus_out         = 10,
	keymap_notify     = 11,
	expose            = 12,
	graphics_expose   = 13,
	no_expose         = 14,
	visibility_notify = 15,
	create_notify     = 16,
	destroy_notify    = 17,
	unmap_notify      = 18,
	map_notify        = 19,
	map_request       = 20,
	reparent_notify   = 21,
	configure_notify  = 22,
	configure_request = 23,
	gravity_notify    = 24,
	resize_request    = 25,
	circulate_notify  = 26,
	circulate_request = 27,
	property_notify   = 28,
	selection_clear   = 29,
	selection_request = 30,
	selection_notify  = 31,
	colormap_notify   = 32,
	client_message    = 33,
	mapping_notify    = 34,
	generic_event     = 35,
	last_event        = 36,
} event_t;

typedef struct point { int16 x, y; } point_t;
typedef struct rectangle { int16 x, y; int16 w, h; } rectangle_t;
typedef struct arc { int16 x, y; int16 w, h; int16 a1, a2; } arc_t;

typedef struct xauth {
	uint16 addr_len;
	char* addr;
	uint16 display_len;
	char* display;
	uint16 name_len;
	char* name;
	uint16 data_len;
	char* data;
} xauth_t;
