void minimap_do (void) {
	// Switch patterns
	tkrom_bankswitch (BG_BANK_3, CHR_BANK_MAP);

	// Draw bg
	bankswitch_prg_a (PRG_BANK_A_RLE_SCREENS);
	scroll (0,0);
	vram_adr (NAMETABLE_A);
	vram_unrle (map_rle);

	// Fill map dinamically
	bankswitch_prg_a (PRG_BANK_A_MAIN_DATA);
	rdx = 6; rdy = 12;
	for (gpit = 0; gpit < 80; gpit ++) {
		rda = 0;
		if (hrt [gpit] > 1 && hrt [gpit] < 0x20) {
			if (hrt [gpit] < 16) {
				rda = 224 + hrt [gpit];
			} else rda = 254;
		}
		if (rda) {
			vram_adr (NAMETABLE_A + (rdy << 5) + rdx);
			vram_put (rda);
		}
		rdx ++; 
		if (rdx == 26) { rdy ++; rdx = 6; }
	}

	// Draw cheril
	vram_adr (NAMETABLE_A + ((12 + level) << 5) + 6 + n_pant);
	vram_put (224);

	// Show & wait
	pal_bg (mypal_game_bg0);
	ppu_on_all ();
	fade_in ();
	while (1) {
		// Thanks for this, Nicole & nesdev!
		// https://forums.nesdev.com/viewtopic.php?p=179315#p179315
		rda = pad0;
		pad0 = pad_poll (0);
		rda = (rda ^ pad0) & pad0;
		if (rda) break;
	}
	fade_out ();
	ppu_off ();
	pal_bg (c_pal_bg);

	// Switch back main patterns
	tkrom_bankswitch (BG_BANK_3, CHR_BANK_TS_GAME + 3);
}
