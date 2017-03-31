// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Fixed screens routines

void enter_screen (const unsigned char *pal, void (*func) (void)) {
	scroll (0, 0);
	
	bankswitch (2);
	cls ();
	(*func) ();
	
	bankswitch (2);
	pal_bg (pal);
	ppu_on_all ();
	fade_in ();
}

void exit_cleanly (void) {
	//set_vram_update (0);
	oam_hide_rest (0);
	music_stop ();
	bankswitch (2);
	fade_out ();
	ppu_off ();	
}

void wait_time_or_input (void) {
	rda = (pad_poll (0) != 0);
	while (game_time) {
		ticker ++; if (ticker == ticks) {
			ticker = 0;
			game_time --;
		}

		if (pad_poll (0)) {
			if (!rda) break;
		} else {
			rda = 0;
		}

		ppu_wait_nmi ();
	}
}

void do_screen (unsigned char seconds) {
	game_time = seconds; ticker = 0;
	wait_time_or_input ();
	exit_cleanly ();
}

void screen_title (void) {
	bankswitch (2);
	vram_adr (NAMETABLE_A);
	vram_unrle (title_rle);

	bankswitch (1);
	tokumaru_lzss (font_ts_patterns_c, 	0);
	tokumaru_lzss (title_ts_patterns_c,	1024);
	
	bankswitch (2);
	if (first_time) {
		p_s (10, 17, "PRESS START!");
	} else {
		p_s (8, 16, "START  TO BEGIN%%SELECT TO CONTINUE");
	}
	p_s (5, 25, "@ 2017 THE MOJON TWINS");
	p_s (4, 27, "NESDEV COMPO EDITION 1.3");
}

void screen_game_over (void) {
	bankswitch (1);
	tokumaru_lzss (font_ts_patterns_c, 	0);

	bankswitch (2);	
	p_s (11, 14, "GAME OVER!");
}


