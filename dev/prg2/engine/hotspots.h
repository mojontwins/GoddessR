// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Hotspots routines

void hotspots_init (void) {
	// Contents of each hotspot is copied to RAM
	// X and Y coordinates are stored in ROM.
	gpit = MAX_PANTS; while (gpit --) hrt [gpit] = c_hotspots_t [gpit];
}

void hotspots_load (void) {
	rda = rdpant + base_pant;
	gpit = rda & 1;

	rdb = c_hotspots_yx [rda];
	hrx [gpit] = rdb << 4;
	hry [gpit] = rdb & 0xf0;
	hrp [gpit] = rda;
}

void hotspots_do (void) {
	gpit = 2; while (gpit --) {
		if (cam_pos_pant == gpit) {
			if (hrx [gpit] >= cam_pos_mod) rdx = hrx [gpit] - cam_pos_mod; else return;
		} else {
			if (hrx [gpit] + 16 < cam_pos_mod) rdx = 256 - cam_pos_mod + hrx [gpit]; else return;
		}

		// Render
		rda = hrt [hrp [gpit]];

		if (rda == 0) return;

		if (rda < 8) {
			sprid = rda;
		} else if (rda & 0x10) {
			sprid = rda & 0x7;
		} else sprid = 3;

		oam_index = oam_meta_spr (
			rdx, hry [gpit] + SPRITE_ADJUST,
			oam_index,
			spr_it [sprid]
		);
	}
}
