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

#include "prg2/assets/behs.h"
#include "prg3/engine/general.h"

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
#include "prg1/chars_ts_patterns_c.h"

// ----------------------------------------------------------------------------

#pragma rodata-name	("ROM2")
#pragma code-name	("ROM2")

// ############################################################################
// ROM2, game functions here. When the game is running, ROM2 is paged in
// ############################################################################

#include "prg2/assets/spritedata.h"
#include "prg2/assets/metasprites.h"
#include "prg2/assets/precalcs.h"
#include "prg2/assets/enems0.h"
#include "prg2/assets/hud_rle.h"
#include "prg2/assets/palettes.h"

#include "prg2/engine/palette_fx.h"
#include "prg2/engine/printer.h"
#include "prg2/engine/camera.h"
#include "prg2/engine/player.h"
#include "prg2/engine/enems.h"
#include "prg2/engine/hotspots.h"
#include "prg2/engine/bg_object.h"
#include "prg2/engine/hud.h"

// ----------------------------------------------------------------------------

#pragma rodata-name	("CODE")
#pragma code-name	("CODE")

// ############################################################################
// CODE segment = PRG3, the fixed segment. Global functions need be here.
// ############################################################################

#include "prg3/engine/ul_helpers.h"
#include "prg3/engine/scroller.h"
#include "prg3/engine/game.h"

// Main section

extern const unsigned char music_ROM1 [];	// A pointer to the music data @ ROM1.

void main (void) {
	// Initialization
	ntsc = ppu_system ();
	ticks = ntsc ? 60 : 50;
	halfticks = ticks >> 1;
	
	famitone_init (1, music_ROM1);

	// And do it...
	bank_bg (0);
	bank_spr (1);
	oam_size (0);
	pal_bright (0);

	// Rehash
	game_init ();

	music_on = 0;

	while (1) { 	
		game_loop ();
		switch (game_res) {
			case PLAYER_EXIT_TOP:
				level --;
				py = 3072; pvy = -PLAYER_VY_JUMP_MAX; pvx = 0;
				break;
			case PLAYER_EXIT_BOTTOM:
				level ++;
				pvx = pvy = 0;
				py = 0;
				break;
			case PLAYER_EXIT_LEFT:
				px -= (16<<FIX_BITS);
				if (px < 0) {
					px += 256<<FIX_BITS;
					n_pant --;
				}
				prx = px >> FIX_BITS;
				break;
			case PLAYER_EXIT_RIGHT:
				px += (16<<FIX_BITS);
				if (px > 256<<FIX_BITS) {
					px -= 256<<FIX_BITS;
					n_pant ++;
				}
				prx = px >> FIX_BITS;
				break;
			case PLAYER_KILLED:
				player_restore_safe_spot ();
				player_reset_movement ();
				pflickers = ticks + ticks + ticks;
				// One life less logics go here
				break;
			case PLAYER_TELEPORT:
				level = HUB_LEVEL; n_pant = HUB_SCR;
				prx = HUB_X << 4; px = prx << FIX_BITS;
				pry = HUB_Y << 4; py = pry << FIX_BITS;
				guay_ct = ticks;
				break;
			case PLAYER_CUTSCENE:
				player_register_safe_spot ();
				n_pant = 19; level = 0; cutscene = 1;
				break;
			case PLAYER_RESTORE:
				player_restore_safe_spot ();
				cutscene = 0;
				break;

			//

			case PLAYER_DEBUG:
				// Custom here
				level = 0; n_pant = 0;
				prx = 32; px = prx << FIX_BITS;
				pry = 64; py = pry << FIX_BITS;
				break;
		}
	}
}
