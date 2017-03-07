// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Hotspots routines

void hotspots_init (void) {
	// Contents of each hotspot is copied to RAM
	// X and Y coordinates are stored in ROM.
	gpit = MAX_PANTS; while (gpit --) hrt [gpit] = c_hotspots_t [gpit];
}

void hotspots_restore_carried_object (void) {
	// Object in pinv returns to hrt
	gpit = MAX_PANTS; while (gpit --) if (c_hotspots_t [gpit] == pinv) hrt [gpit] = pinv;
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

		if (rda == 0xff) {
			sprid = 3;
		} else if (rda < 8) {
			sprid = rda;
		} else if (rda & 0x10) {
			sprid = rda & 0x7;
		} else if (rda == 0x22) {
			sprid = 2;
		} else sprid = 3;

		if (cam_pos_pant == gpit) {
			if (rdb >= cam_pos_mod) rdx = rdb - cam_pos_mod; else continue;
		} else {
			if (rdb + 16 < cam_pos_mod) rdx = 256 - cam_pos_mod + rdb; else continue;
		}
		
		if ((rda >= 8 && rda < 16) ||
			(rda == 0x21 && pcharges < 3) ||
			(rda == 0x20 && pcharges)) oam_index = oam_meta_spr (
			rdx, rdc + SPRITE_ADJUST - 16 + bounce_precalc [frame_counter & 0x1f],
			oam_index,
			spr_push_b_00
		);

		oam_index = oam_meta_spr (
			rdx, rdc + SPRITE_ADJUST,
			oam_index,
			spr_it [sprid]
		);

		if (rda == 0x22 && half_life) oam_index = oam_meta_spr (
			rdx, rdc + SPRITE_ADJUST,
			oam_index,
			spr_it [8]
		);

		// Collision
		if (CL (prx, pry, rdb, rdc)) {
			// Plain ones, react on touch if < 8
			if (rda < 8 || rda == 0x22) {
				switch (rda) {
					case 0x01: 
						// life
						plife ++;
						hrt [hrp [gpit]] = 0;
						sfx_play (SFX_HEART, SC_LEVEL);
						break;
					case 0x04:
					case 0x05:
					case 0x06:
					case 0x07:
						// Get object
						if (guay_ct == 0) {
							if (pinv == 0xff) {
								hrt [hrp [gpit]] = 0xff;
								pinv = rda;
								sfx_play (SFX_GET, SC_LEVEL);
								guay_ct = ticks;
							}
						} 
						break;
					case 0x22:
						// Ending
						psignal = PLAYER_WINS;
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
						if (pinv == (rda & 7)) {
							music_on = 0;
							if (rda < 0x0f) music_stop ();
							use_ct = 1; fr_ct = 0;
							rdb = 1;
							h_modify_this = hrp [gpit];
							gs_this_flag = rda - 0x0C;
							sfx_play (SFX_USE, SC_LEVEL);
						}
						break;
					case 0x20:
						// Teleport
						if (pcharges) {
							pcharges --;
							music_pause (1);
							sfx_play (SFX_USE, SC_LEVEL);
							fx_flash (mypal_reds);
							tt_ct = 1; fr_ct = 0;
							rdb = 1;
						}
						break;
					case 0x21:
						// Recharge
						if (pcharges < 3) {
							pcharges = 3;
							sfx_play (SFX_RECHARGE, SC_LEVEL);
							fx_flash (c_pal_bg);
							guay_ct = ticks;
							rdb = 1;
						}
						break;
				}
				if (!rdb) {
					no_ct = ticks;
					sfx_play (SFX_NO, SC_PLAYER);
				}
			}
		}
	}
}
