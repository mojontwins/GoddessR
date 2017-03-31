void minimap_do (void) {
	// Load patterns
	// Ucompress full set from PRG 3
	tokumaru_lzss (map_ts_patterns_c, 		0);
	tokumaru_lzss (map_ss_patterns_c,		7808);	// 488*16 (sprite pattern 232 onwards)

	// Draw bg
	bankswitch (2);
	scroll (0,0);
	vram_adr (NAMETABLE_A);
	vram_unrle (map_rle);

	oam_index = 4;

	// Draw icons on map

	// Draw icons off map
	gpit = 16; while (-- gpit) oam_index = oam_spr (
		map_sprite_positions_x [gpit],
		map_sprite_positions_y [gpit],
		232 + gpit,
		map_sprite_attributes [gpit],
		oam_index
	);
	
	// Fill map dinamically
	rdx = 10; rdy = 25;
	for (gpit = 0; gpit < 80; gpit ++) {
		rda = 0;

		if (hrt [gpit] > 1) {
			if (hrt [gpit] < 0x20) {
				// Beat temple:
				if (hrt [gpit] > 15) {
					oam_index = oam_spr (rdx, rdy, 232, 1, oam_index);
					rda = 224 + hrt [gpit];
				} else {
					rda = 232 + hrt [gpit];
				}
			} else rda = 233 + hrt [gpit] - 0x20;
		}

		// Draw Cheril
		if (gpit == n_pant + base_pant) {
			oam_index = oam_meta_spr (rdx, rdy, oam_index, spr_cheril_mini);
			rda = 0;
		}

		if (rda) oam_index = oam_spr (rdx, rdy, rda, 1, oam_index);

		rdx += 12; if (rdx == 250) { rdx = 10; rdy += 12; }
	}
	
	/*
	// Draw cheril
	vram_adr (NAMETABLE_A + ((12 + level) << 5) + 6 + n_pant);
	vram_put (224);
	*/

	oam_hide_rest (oam_index);

	// Show & wait
	pal_bg (mypal_map);
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
	oam_hide_rest (0);
	ppu_off ();
	pal_bg (c_pal_bg);

	// Reload hud patterns
	bankswitch (1);
	tokumaru_lzss (main_ts_patterns_c,		0);
	tokumaru_lzss (chars_ts_patterns_c, 	3584);	// 224*16
	tokumaru_lzss (sps_ss_patterns_c,		7808);
	bankswitch (2);
}
