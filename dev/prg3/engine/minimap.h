void minimap_do (void) {
	// Load patterns
	bankswitch (1);
	tokumaru_lzss (map_ts_patterns_c, 3584);	// 224*16

	// Draw bg
	bankswitch (2);
	scroll (0,0);
	vram_adr (NAMETABLE_A);
	vram_unrle (map_rle);

	// Fill map dinamically
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

	// Reload hud patterns
	bankswitch (1);
	tokumaru_lzss (chars_ts_patterns_c, 3584);	// 224*16
	bankswitch (2);
}
