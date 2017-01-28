// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Player routines

void player_reset_movement (void) {
	pvx = pvy = 0;
}

void player_register_safe_spot (void) {
	safe_prx = prx; safe_pry = pry;
	safe_n_pant = n_pant; safe_level = level;
}

void player_restore_safe_spot (void) {
	prx = safe_prx; px = prx << FIX_BITS;
	pry = safe_pry; py = pry << FIX_BITS;			
	n_pant = safe_n_pant; level = safe_level;
}

void player_init (void) {
	if (pcontinues) {
		prx = (10 << 4); px = prx << FIX_BITS;
		pry = (4 << 4); py = pry << FIX_BITS;
	} else {
		prx = (4 << 4); px = prx << FIX_BITS;
		pry = (6 << 4); py = pry << FIX_BITS;
	}
	pfacing = pfr = 0;
	player_register_safe_spot ();
	player_reset_movement ();

	use_ct = 0;
	pinv = 0;
	pcharges = 0;
	plife = 5;

	pvmax = PLAYER_VX_MAX;
}

void player_collision_vertical (void) {
	cyaux = cy1 < 32 ? 0 : cy1 - 32;
	at1 = *(scr_buffer_ptr + cyaux + cx1);
	if (cx2 > 15) {
		cx2 -= 16;
		gp_aux = scr_buffer + ((n_pant & 1) ? 0 : 192);
	} else {
		gp_aux = scr_buffer_ptr;
	}
	at2 = *(gp_aux + cyaux + cx2);
}

void player_collision_horizontal (void) {
	if (cx1 > 15) {
		cx1 -= 16;
		gp_aux = scr_buffer + ((n_pant & 1) ? 0 : 192);
	} else {
		gp_aux = scr_buffer_ptr;
	}

	cyaux = cy1 < 32 ? 0 : cy1 - 32; 
	at1 = *(gp_aux + cyaux + cx1);
	cyaux = cy2 < 32 ? 0 : cy2 - 32; 
	at2 = *(gp_aux + cyaux + cx1);
}

void player_move (void) {
	// Timers and stuff
	if (pflickers) pflickers --;

	if (guay_ct) {
		guay_ct --;
	} else if (tt_ct) {
		if (fr_ct) fr_ct --; else {
			if (0xff != (rda = tt_anim [tt_ct ++])) {
				if (0 == (fr_ct = rda & 0x0f)) fr_ct = 20;
				pfr = PCELL_TELEPORT + (rda >> 4);
				if ((rand8 () & 3) == 0) {
					sfx_play (SFX_FLASH, SC_LEVEL);
					fx_flash (mypal_reds);
				}
			} else {
				fx_flash (c_pal_bg);
				psignal = PLAYER_TELEPORT;
			}
		}
	} else if (use_ct) {
		pfr = PCELL_USE_ANIM_BASE + use_ct;
		if (fr_ct) fr_ct --; else {
			use_ct ++;
			if (use_ct == 7) {
				sfx_play (SFX_GET, SC_LEVEL);
				hrt [h_modify_this] = pinv | 0x10;
				pinv = 0xff;
				if (gs_this_flag < 3) {
					stage = 1 + gs_this_flag;
					c_pal_bg = c_pal_bgs [stage];
					pal_bg (c_pal_bg);
				}
			}
			if (use_ct == 15) {
				sfx_play (SFX_USE, SC_LEVEL);
				gs_flags [gs_this_flag] = 1;
				if (gs_this_flag < 3) {
					psignal = PLAYER_CUTSCENE;
				}
			}
			if (use_ct == 18) {
				gs_flags [gs_this_flag] = 2;
				use_ct = 0;
			}
			fr_ct = 8;
		}
	} else pad = pad0;

	// Vertical

	if (ppodewwwr) {
		ppodewwwr --;

		if (0 == ppodewwwr) {
			// Deactivate
			sfx_play (SFX_OFF, SC_PLAYER);
			pvmax = PLAYER_VX_MAX;
			c_pal_fg = mypal_game_fg0;
			fx_flash (c_pal_bg);
		}

		if (pad & PAD_UP) {
			if (pvy > -pvmax) pvy -= PLAYER_AX;
		} else if (pad & PAD_DOWN) {
			if (pvy < pvmax) pvy += PLAYER_AX;
		} else {
			if (pvy > 0) {
				pvy -= PLAYER_RX; if (pvy < 0) pvy = 0;
			} else if (pvx < 0) {
				pvy += PLAYER_RX; if (pvy > 0) pvy = 0;
			}
		}
	} else {
		// Gravity
		if (!pgotten) {
			if (pvy < PLAYER_VY_FALLING_MAX) pvy += PLAYER_G; else pvy = PLAYER_VY_FALLING_MAX;
		}
	}

	// Move. 
	py = py + pvy;

	// Limit. Virtual playing area is 14 tiles high, may Y = 13*16 = 208.
	if (py < 0) { if (level) { game_res = PLAYER_EXIT_TOP; return; } else py = 0; }
	if (py > (208 << FIX_BITS)) { game_res = PLAYER_EXIT_BOTTOM; return; }

	pry = py >> FIX_BITS;

	// Collision
	cx1 = prx >> 4;
	cx2 = (prx + 7) >> 4;

	if (pvy + pgtmy < 0) {
		cy1 = pry & 0xf0;
		player_collision_vertical ();
		if ((at1 & 8) || (at2 & 8)) {
			pgotten = pvy = 0;
			pry = cy1 + 16;
			py = pry << FIX_BITS;
		} else if ((at1 & 2) || (at2 & 2)) {
			if (pctj > 2) pj = 0;
		}
	} else if (pvy + pgtmy > 0) {
		cy1 = (pry + 15) & 0xf0;
		player_collision_vertical ();
		if (((pry - 1) & 15) < 4 && ((at1 & 12) || (at2 & 12))) {
			pgotten = pvy = 0;
			pry = cy1 - 16;
			py = pry << FIX_BITS;
		} else if ((at1 & 2) || (at2 & 2)) {
			pvy = PLAYER_VY_SINK;
		}
	}
	cy1 = (pry + 16) & 0xf0;
	player_collision_vertical ();
	ppossee = ((pry & 0xf) == 0) && ((at1 & 14) || (at2 & 14));

	// Jump
	if (0 == ppodewwwr) {
		if (pad & PAD_A) {
			if (!pjb) {
				pjb = 1;
				if (!pj) {
					if (pgotten || ppossee) {
						pj = 1; pctj = 0; 
						pvy = -PLAYER_VY_JUMP_INITIAL;
						sfx_play (SFX_JUMP, SC_PLAYER);
						if (ppossee) player_register_safe_spot ();
					}
				} 
			}
			if (pj) {
				rda = PLAYER_AY_JUMP - (pctj >> 2) - (pctj >> 3);
				pvy -= (rda > 1 ? rda : 1);
				if (pvy < -PLAYER_VY_JUMP_MAX) pvy = -PLAYER_VY_JUMP_MAX;
				pctj ++; if (pctj == PLAYER_VY_JUMP_A_STEPS) pj = 0;
			}
		} else {
			pjb = 0; pj = 0;
		}
	}

	// Horizontal

	if (pad & PAD_LEFT) {
		pfacing = PFACING_LEFT;
		if (pvx > -pvmax) pvx -= PLAYER_AX;
	} else if (pad & PAD_RIGHT) {
		pfacing = PFACING_RIGHT;
		if (pvx < pvmax) pvx += PLAYER_AX;
	} else {
		if (pvx > 0) {
			pvx -= PLAYER_RX; if (pvx < 0) pvx = 0;
		} else if (pvx < 0) {
			pvx += PLAYER_RX; if (pvx > 0) pvx = 0;
		}
	}

	// Move
	px += pvx;
	if (pgotten) px += pgtmx;

	// Detect virtual screen flix and stuff
	if (px < 0) {
		px += (256 << FIX_BITS);
		n_pant --; SCR_BUFFER_PTR_UPD;
	} else if (px >= (256 << FIX_BITS)) {
		px -= (256 << FIX_BITS);
		n_pant ++; SCR_BUFFER_PTR_UPD;
	}

	prx = px >> FIX_BITS;

	// Collision
	cy1 = pry & 0xf0;
	cy2 = (pry + 15) & 0xf0;
	if (pvx + pgtmx < 0) {
		cx1 = prx >> 4;
		player_collision_horizontal ();
		if ((at1 & 8) || (at2 & 8)) {
			pvx = 0;
			prx = (cx1 + 1) << 4;
			px = prx << FIX_BITS;
		}
	} else if (pvx + pgtmx > 0) {
		cx1 = (prx + 7) >> 4;
		player_collision_horizontal ();
		if ((at1 & 8) || (at2 & 8)) {
			pvx = 0;
			prx = ((cx1 - 1) << 4) + 8;
			px = prx << FIX_BITS;
		}
	}

	// Detect evil tile
	if (prx < 252) // Safe. 
		cx1 = (prx + 4) >> 4;
		cy1 = (pry + 8) & 0xf0;
		cyaux = (cy1 < 32 ? 0 : cy1 - 32);
		if (*(scr_buffer_ptr + cyaux + cx1) & 1) {
			psignal = PLAYER_KILLED;
		}

	// Podewwwr
	if (pad & PAD_B) {
		if (pad & PAD_UP) {
			if (pcharges) {
				if (ppodewwwr == 0) {
					ppodewwwr = 250;
					pvmax = PLAYER_VX_MAX_PODEWWWR;
					c_pal_fg = mypal_game_fg1;
					fx_flash (c_pal_bg);
					sfx_play (SFX_ON, SC_PLAYER);
				}
			} else if (no_ct == 0) {
				no_ct = ticks;
				sfx_play (SFX_KILL, SC_PLAYER);
			}
		}
	}

	// Calc cell
	if (tt_ct || use_ct) {
	} else {
		if (ppodewwwr) {
			pfr = PCELL_SUPERHERO + ((frame_counter >> 3) & 3);
		} else if (ppossee || pgotten) {
			if (guay_ct) 
				pfr = PCELL_WIN_POSE;
			else if (ABS (pvx) > PLAYER_VX_MIN) {
				pfr = PCELL_WALK_BASE + ((prx >> 4) & 3);
			} else pfr = PCELL_STANDING;
		} else {
			pfr = PCELL_AIRBORNE;
		}

		pfr += pfacing;
	}

	// Real world pixel coordinate
	px_world = (n_pant << 8) | prx;

	// Important
	pgtmx = pgtmy = pgotten = 0;
}

void player_render (void) {
	rdx = px_world - cam_pos;
	rdy = SPRITE_ADJUST + pry;
	if (half_life || !pflickers) oam_meta_spr (
		rdx, rdy,
		4,
		spr_pl [pfr]); 
	else oam_meta_spr (
		rdx, rdy,
		4,
		spr_empty);

	if (no_ct) {
		no_ct --;
		oam_index = oam_meta_spr (
			rdx + 2, rdy - 24,
			oam_index,
			spr_en [ENCELL_NO] 
		);
	}
}
