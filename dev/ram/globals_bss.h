// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// BSS globals

// 50 or 60 depending on TV system
unsigned char ticks, halfticks;				

// Update list for VBlank updates
static unsigned char update_list [1 + UPDATE_LIST_SIZE * 3];

// Collision buffer
unsigned char scr_buffer [384];

// Stuff
signed char fader;
