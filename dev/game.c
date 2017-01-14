// Cheril the Goddess R

// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

#include "neslib-unrom.h"

#include "definitions.h"

// ----------------------------------------------------------------------------

#pragma bss-name (push,"ZEROPAGE")
#pragma data-name(push,"ZEROPAGE")

#include "ram/globals_zp.h"

// ----------------------------------------------------------------------------

#pragma bss-name (push,"BSS")
#pragma data-name(push,"BSS")

#include "ram/globals_bss.h"

// ----------------------------------------------------------------------------

#pragma rodata-name	("CODE")
#pragma code-name	("CODE")

const unsigned char bitmasks [] = {0xfc, 0xf3, 0xcf, 0x3f};

// ----------------------------------------------------------------------------

#pragma rodata-name	("ROM0")
#pragma code-name	("ROM0")

// ############################################################################
// ROM0, maps & tilemaps
// ############################################################################

#include "prg0/map.h"
#include "prg0/main_ts.h"
#include "prg0/attr_precalcs.h"

// ----------------------------------------------------------------------------

#pragma rodata-name	("ROM1")
#pragma code-name	("ROM1")

// ############################################################################
// ROM1, patterns, music, etc
// ############################################################################

#include "prg1/main_ts_patterns_c.h"
#include "prg1/main_ss_patterns_c.h"
#include "prg1/palettes.h"

// ----------------------------------------------------------------------------

#pragma rodata-name	("ROM2")
#pragma code-name	("ROM2")

// ############################################################################
// ROM2, game functions here. When the game is running, ROM2 is paged in
// ############################################################################

#include "prg2/assets/behs.h"
#include "prg2/assets/spritedata.h"
#include "prg2/assets/precalcs.h"

// ----------------------------------------------------------------------------

#pragma rodata-name	("CODE")
#pragma code-name	("CODE")

// ############################################################################
// CODE segment = PRG3, the fixed segment. Global functions need be here.
// ############################################################################

#include "prg3/engine/general.h"
#include "prg3/engine/scroller.h"

// Main section

extern const unsigned char music_ROM1 [];	// A pointer to the music data @ ROM1.

void main (void) {
	// Initialization
	ticks = ppu_system () ? 60 : 50;
	halfticks = ticks >> 1;
	
	famitone_init (1, music_ROM1);

	// And do it...
	bank_bg (0);
	bank_spr (1);
	oam_size (0);
	pal_bright (0);

	map_ptr = map_0;

	cam_pos = (n_pant << 8) | prx;

	// Remove 
	test_scroller ();
}
