// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Fixed screens routines

void enter_screen (const unsigned char *pal, void (*func) (void)) {
	scroll (0, 0);
	
	bankswitch_prg_b (PRG_BANK_B_MAIN);
	cls ();
	(*func) ();
	
	bankswitch_prg_a (PRG_BANK_A_MAIN_DATA);
	pal_bg (pal);
	ppu_on_all ();
	fade_in ();
}

void exit_cleanly (void) {
	//set_vram_update (0);
	oam_hide_rest (0);
	music_stop ();
	bankswitch_prg_b (PRG_BANK_B_MAIN);
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
	bankswitch_prg_a (PRG_BANK_A_RLE_SCREENS);
	bankswitch_prg_b (PRG_BANK_B_MAIN);
	vram_adr (NAMETABLE_A);
	vram_unrle (title_rle);

	tkrom_bankswitch (BG_BANK_0, CHR_BANK_FONT);
	tkrom_bankswitch (BG_BANK_1, CHR_BANK_TITLE);
	tkrom_bankswitch (BG_BANK_2, CHR_BANK_TITLE + 1);
	
	bankswitch_prg_b (PRG_BANK_B_MAIN);
	if (first_time) {
		p_s (10, 17, "PRESS START!");
	} else {
		p_s (8, 16, "START  TO BEGIN%%SELECT TO CONTINUE");
	}
	p_s (5, 25, "@ 2017 THE MOJON TWINS");
}

void screen_game_over (void) {
	tkrom_bankswitch (BG_BANK_0, CHR_BANK_FONT);
	bankswitch_prg_b (PRG_BANK_B_MAIN);
	p_s (11, 14, "GAME OVER!");
}


