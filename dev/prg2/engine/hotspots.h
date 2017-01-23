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
		// Render
		rda = hrt [hrp [gpit]];
		if (rda == 0) continue;

		rdb = hrx [gpit]; rdc = hry [gpit];

		if (rda < 8) {
			sprid = rda;
		} else if (rda & 0x10) {
			sprid = rda & 0x7;
		} else sprid = 3;

		if (cam_pos_pant == gpit) {
			if (rdb >= cam_pos_mod) rdx = rdb - cam_pos_mod; else return;
		} else {
			if (rdb + 16 < cam_pos_mod) rdx = 256 - cam_pos_mod + rdb; else return;
		}
		
		oam_index = oam_meta_spr (
			rdx, rdc + SPRITE_ADJUST,
			oam_index,
			spr_it [sprid]
		);

		// Collision
		if (CL (prx, pry, rdb, rdc)) {
			// Plain ones, react on touch if < 8
			if (rda < 8) {
				switch (rda) {
					case 0x01: 
						// life
						break;
					case 0x04:
					case 0x05:
					case 0x06:
					case 0x07:
						// Get object
						break;
				}
			} else if ((pad0 & PAD_B) && !(guay_ct || tt_ct || use_ct || no_ct)) {
				rdb = 0;
				switch (rda) {
					case 0x0C:
					case 0x0D:
					case 0x0E:
					case 0x0F:
						// Use object
						break;
					case 0x20:
						// Teleport
						if (pcharges) {
							pcharges --;
							music_pause (1);
							// sfx_play (SFX_TELEPORT, SC_LEVEL);
							fx_flash (mypal_reds);
							tt_ct = 1; fr_ct = 0;
							rdb = 1;
						}
						break;
					case 0x21:
						// Recharge
						if (pcharges < 3) {
							pcharges = 3;
							// sfx_play (SFX_RECHARGE, SC_LEVEL);
							fx_flash (c_pal_bg);
							guay_ct = ticks;
							rdb = 1;
						}
						break;
					case 0x22:
						// Ending
						break;
				}
				if (!rdb) no_ct = ticks;
			}
		}
	}
}
