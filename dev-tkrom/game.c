// Cheril the Goddess R

// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Ported to TKROM just for the hell of it (and learn a bit)

// My TKROM setup is 256+128K, 8K WRAM.
// 8K+8K+16K fixed is enforced.

// For this game, I've chosen to deal with PRG 0 and PRG 1 together. 
// BOTH need to be paged in at the same time!

// For this setup I've chosen that pages 2, 3, 4, 5 (32K) are for data,
// And pages 6, 7, 8, 9 (32K) are for code. Very convenient. When I design
// a game for TKROM from scratch I'll have to plan how to set up stuff in
// advance, but this is a port with plenty of room to spare. And waste.

#include "neslib-tkrom.h"
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

// #include here you need everywhere and right from the
// beginning and you need it in the fixed banks.
#include "prg1e1f/assets/behs.h"
#include "prg1e1f/engine/general.h"

// ----------------------------------------------------------------------------

#pragma rodata-name	("ROM0001")
#pragma code-name	("ROM0001")

// ############################################################################
// ROM01, maps & tilemaps
// ############################################################################

#include "prg0001/map.h"
#include "prg0001/main_ts.h"
#include "prg0001/attr_precalcs.h"

// ----------------------------------------------------------------------------

#pragma rodata-name ("ROM02")
#pragma code-name   ("ROM02")

// ############################################################################
// ROM02, music. Loaded externally
// ############################################################################

extern const unsigned char music_ROM02 [];	// A pointer to the music data @ ROM02.

// ----------------------------------------------------------------------------

#pragma rodata-name ("ROM03")
#pragma code-name   ("ROM03")

// ############################################################################
// ROM03, assets storage #1
// ############################################################################

// RLE'd stuff
#include "prg03/title_rle.h"
#include "prg03/plate1_rle.h"
#include "prg03/plate2_rle.h"
#include "prg03/hud_rle.h"
#include "prg03/map_rle.h"
#include "prg03/ending_rle.h"

// ----------------------------------------------------------------------------

#pragma rodata-name ("ROM04")
#pragma code-name   ("ROM04")

// ############################################################################
// ROM04, assets storage #2
// ############################################################################

// Ingame stuff
#include "prg04/enems0.h"
#include "prg04/spritedata.h"
#include "prg04/metasprites.h"
#include "prg04/palettes.h"
#include "prg04/precalcs.h"
#include "prg04/texts.h"

// ----------------------------------------------------------------------------

#pragma rodata-name ("ROM05")
#pragma code-name   ("ROM05")

// ############################################################################
// ROM05, assets storage #3
// ############################################################################

// ...

// ----------------------------------------------------------------------------

#pragma rodata-name ("ROM06")
#pragma code-name   ("ROM06")

// ############################################################################
// ROM06, pageable program data #1
// ############################################################################

#include "prg06/printer.h"
#include "prg06/bg_object.h"
#include "prg06/camera.h"
#include "prg06/hotspots.h"
#include "prg06/hud.h"
#include "prg06/palette_fx.h"
#include "prg06/player.h"

// ----------------------------------------------------------------------------

#pragma rodata-name ("ROM07")
#pragma code-name   ("ROM07")

// ############################################################################
// ROM07, pageable program data #2
// ############################################################################

#include "prg07/enems.h"

// ----------------------------------------------------------------------------

#pragma rodata-name ("ROM08")
#pragma code-name   ("ROM08")

// ############################################################################
// ROM08, pageable program data #3
// ############################################################################

// ...

// ----------------------------------------------------------------------------

#pragma rodata-name ("ROM09")
#pragma code-name   ("ROM09")

// ############################################################################
// ROM09, pageable program data #4
// ############################################################################

// ...

// ----------------------------------------------------------------------------

// Won't be using these but don't want teh compiler to complain...
#include "wontuse.h"


// ----------------------------------------------------------------------------

#pragma rodata-name	("CODE")
#pragma code-name	("CODE")

// ############################################################################
// CODE segment = PRG1E1F, the fixed segment. Global functions need be here.
// ############################################################################

#include "prg1e1f/engine/ul_helpers.h"
#include "prg1e1f/engine/scroller.h"
#include "prg1e1f/engine/screens.h"
#include "prg1e1f/engine/cutscene.h"
#include "prg1e1f/engine/game.h"
#include "prg1e1f/engine/minimap.h"

// #includes...

// Main

void main (void) {
	ntsc = ppu_system ();
	ticks = ntsc ? 60 : 50;
	halfticks = ticks >> 1;
	first_time = 1;
	
	famitone_init (2, music_ROM02);

	// And do it...
	bank_bg (0);
	bank_spr (1);
	oam_size (0);
	pal_bright (0);

// Rehash
	soft_reenter = pcontinues = 0;

	while (1) {
		game_title ();
		if (pcontinues == 0) game_intro ();
		game_init ();
		if (pcontinues) {
			bankswitch_prg_b (PRG_BANK_B_MAIN);
			player_register_safe_spot ();
			n_pant = 19; level = 0; cutscene = 2;
		}

		music_on = 0;
		keep_playing = 1;

		while (keep_playing) { 	
			game_loop ();
			switch (game_res) {
				case PLAYER_EXIT_TOP:
					level --;
					py = 3328 /*3072*/; pvy = -PLAYER_VY_JUMP_FLICK; pvx = 0;
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
					bankswitch_prg_b (PRG_BANK_B_MAIN);
					player_restore_safe_spot ();
					player_reset_movement ();
					pflickers = ticks + ticks + ticks;
					// One life less logics go here
					if (plife) plife --; else {
						game_over ();
						keep_playing = 0;
					}
					break;
				case PLAYER_TELEPORT:
					level = HUB_LEVEL; n_pant = HUB_SCR;
					prx = HUB_X << 4; px = prx << FIX_BITS;
					pry = HUB_Y << 4; py = pry << FIX_BITS;
					guay_ct = ticks;
					break;
				case PLAYER_CUTSCENE:
					bankswitch_prg_b (PRG_BANK_B_MAIN);
					player_register_safe_spot ();
					n_pant = 19; level = 0; cutscene = 1;
					break;
				case PLAYER_RESTORE:
					bankswitch_prg_b (PRG_BANK_B_MAIN);
					player_restore_safe_spot ();
					cutscene = 0;
					break;
				case PLAYER_WINS:
					game_ending ();
					keep_playing = 0;
					break;
				case PLAYER_GAME_OVER:
					game_over ();
					keep_playing = 0;
					break;
				case PLAYER_MAP:
					minimap_do ();
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
}
