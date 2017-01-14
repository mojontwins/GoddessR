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
const int sections_3 [] = { 0, 256, 2304, 2816, 4096, 5120 };
const int * const sections [] = { sections_0, sections_1, sections_2, sections_3 };
