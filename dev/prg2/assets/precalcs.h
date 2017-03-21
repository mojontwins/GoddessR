// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// precalcs

/*
const unsigned int shl5 [] = {
	0x0000, 0x0020, 0x0040, 0x0060, 0x0080, 0x00A0, 0x00C0, 0x00E0,
	0x0100, 0x0120, 0x0140, 0x0160
};

const unsigned char shl4 [] = {
	0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70,
	0x80, 0x90, 0xa0, 0xb0
};
*/

const int sections_0 [] = { 0, 256, 4096, 5120 };
const int sections_1 [] = { 0, 2304, 2816, 3328, 4096, 4352, 5120 };
const int sections_2 [] = { 0, 1024, 2304, 3072, 4352, 5120 };
const int sections_3 [] = { 0, 256, 2304, 2816, 3072, 4096, 5120 };
const int * const sections [] = { sections_0, sections_1, sections_2, sections_3 };

#define PEZON_INCS_MAX 48
#define PEZON_INCS_FIRST_FALL 26
const signed char pezon_incs [] = {
	-6, -6, -5, -5, -5, -4, -4, -4,
	-4, -4, -3, -3, -3, -2, -2, -2, 
	-2, -2, -1, -1, -1, 0, 0, 0, 
	0, 0, 1, 1, 1, 2, 2, 2, 
	2, 2, 3, 3, 3, 4, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 4
};

#define FANTY_INCS_MAX 16
const signed char fanty_incs [] = {
	0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1
};

#define FANTY_RETREAT_INCS_MAX 4
const signed char fanty_retreat_incs [] = {
	1, 0, 0, 0
};

const unsigned char chac_chac_tiles_0 [] = { 48, 50, 53, 50, 48, 54 };
const unsigned char chac_chac_tiles_1 [] = { 54, 54, 52, 54, 54, 54 };
const unsigned char chac_chac_tiles_2 [] = { 49, 51, 53, 51, 49, 54 };
const unsigned char bg_object_times [] = { 16, 1, 50, 2, 2, 120 };

const unsigned char column_tiles_0 [] = { 6, 6, 20 };
const unsigned char column_tiles_1 [] = { 6, 20, 0 };
const unsigned char column_tiles_2 [] = { 20, 0, 0 };

const unsigned char main_gate_tiles_0 [] = { 2, 2, 2 };
const unsigned char main_gate_tiles_1 [] = { 29, 0, 0 };
const unsigned char main_gate_tiles_2 [] = { 30, 29, 0 };

const unsigned int nt_tile_offsets_y [] = {
	0, 64, 128, 192,
	256, 320, 384, 448, 
	512, 576, 640, 704
};

// 0xFT, T = 0 -> T = 20;
const unsigned char tt_anim [] = {
	0xff, // dummy to save code.
	0x00, 0x10,
	0x2f, 0x3e, 0x4d, 0x1c,
	0x2b, 0x3a, 0x49, 0x18,
	0x28, 0x38, 0x47, 0x17,
	0x26, 0x36, 0x45, 0x15,
	0x24, 0x34, 0x43, 0x13,
	0x22, 0x32, 0x42, 0x12,
	0x21, 0x31, 0x41, 0x11,
	0x21, 0x31, 0x41, 0x11,
	0x21, 0x31, 0x41,
	0x54, 0x62, 0x72,
	0xff
};

const unsigned char * const c_pal_bgs [] = {
	mypal_game_bg0,
	mypal_game_bg1,
	mypal_game_bg2,
	mypal_game_bg3
};

const unsigned char * const c_pal_fgs [] = {
	mypal_game_fg0,
	mypal_game_fg1
};

const unsigned char bounce_precalc [] = {
	0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7,
	7, 7, 7, 7, 6, 6, 6, 6, 5, 5, 4, 4, 3, 2, 1, 0
};

// empty, tele, cherger, skull, stone, paper, scissors, key, 
// cheril A, B, C, D, scissors temple, rock temple, paper temple, key hole

const unsigned char map_sprite_positions_x [] = {
	0, 16, 128, 136, 16, 128, 16, 128,
	4, 12, 4, 12, 16, 16, 128, 128,
};

const unsigned char map_sprite_positions_y [] = {
	0, 207, 207, 87, 159, 159, 175, 175,
	83, 83, 91, 91, 127, 111, 111, 127
};

const unsigned char map_sprite_attributes [] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 1, 1, 1, 1
};
