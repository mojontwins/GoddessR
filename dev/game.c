// Lala the Magical v1.2 [UNROM version]
// MT NES MK1 ChamanH v0.2
// Copyleft 2016 by The Mojon Twins

#include "neslib-unrom.h"

#include "definitions.h"
#include "config.h"

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

// ----------------------------------------------------------------------------

#pragma rodata-name	("ROM2")
#pragma code-name	("ROM2")

// ############################################################################
// ROM2, game functions here. When the game is running, ROM2 is paged in
// ############################################################################



// ----------------------------------------------------------------------------

#pragma rodata-name	("CODE")
#pragma code-name	("CODE")

// ############################################################################
// CODE segment = PRG3, the fixed segment. Global functions need be here.
// ############################################################################

void main (void) {
}
