// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Player routines

void player_reset_movement (void) {
	pvx = pvy = 0;
}

void player_init (void) {
	prx = (4 << 4); px = prx << FIX_BITS;
	pry = (6 << 4); py = pry << FIX_BITS;
	pfacing = pfr = 0;
}

void player_move (void) {
	pad = pad0;		// Add ifs.

	// Vertical

	// Gravity
	if (!pgotten) {
		if (pvy < PLAYER_VY_FALLING_MAX) pvy += PLAYER_G; else pvy = PLAYER_VY_FALLING_MAX;
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
		cy1 = pry >> 4;
		cm_two_points_horizontal ();
		if ((at1 & 8) || (at2 & 8)) {
			pgotten = pvy = 0;
			pry = (cy1 + 1) << 4;
			py = pry << FIX_BITS;
		} else if ((at1 & 2) || (at2 & 2)) {
			if (pctj > 2) pj = 0;
		}
	} else if (pvy + pgtmy > 0) {
		cy1 = (pry + 15) >> 4;
		cm_two_points_horizontal ();
		if (((pry - 1) & 15) < 4 && ((at1 & 12) || (at2 & 12))) {
			pgotten = pvy = 0;
			pry = (cy1 - 1) << 4;
			py = pry << FIX_BITS;
		} else if ((at1 & 2) || (at2 & 2)) {
			pvy = PLAYER_VY_SINK;
		}
	}
	cy1 = (pry + 16) >> 4;
	cm_two_points_horizontal ();
	ppossee = ((at1 & 14) || (at2 & 14));
	pslip = (ppossee && ((at1 & 16) || (at2 & 16)));

	// Jump
	if (pad & PAD_A) {
		if (!pjb) {
			pjb = 1;
			if (!pj) {
				if (pgotten || ppossee || phit) {
					pj = 1; pctj = 0; 
					pvy = -PLAYER_VY_JUMP_INITIAL;
					//sfx_play (SFX_JUMP, SC_PLAYER);
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
		pjb = 0;
		pj = 0;
	}

	// Horizontal

	if (pad & PAD_LEFT) {
		pfacing = PFACING_LEFT;
		ppressingh = 1;
		if (pvx > -PLAYER_VX_MAX) pvx -= (pslip ? PLAYER_AX_SLIP : PLAYER_AX);
	} else if (pad & PAD_RIGHT) {
		pfacing = PFACING_RIGHT;
		ppressingh = 1;
		if (pvx < PLAYER_VX_MAX) pvx += (pslip ? PLAYER_AX_SLIP : PLAYER_AX);
	} else {
		ppressingh = 0;
		if (pvx > 0) {
			pvx -= (pslip ? PLAYER_RX_SLIP : PLAYER_RX); if (pvx < 0) pvx = 0;
		} else if (pvx < 0) {
			pvx += (pslip ? PLAYER_RX_SLIP : PLAYER_RX); if (pvx > 0) pvx = 0;
		}
	}

	// Move
	px += pvx;

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
	cy1 = pry >> 4;
	cy2 = (pry + 15) >> 4;
	if (pvx < 0) {
		cx1 = prx >> 4;
		cm_two_points_vertical ();
		if ((at1 & 8) || (at2 & 8)) {
			pvx = 0;
			prx = (cx1 + 1) << 4;
			px = prx << FIX_BITS;
		}
	} else if (pvx > 0) {
		cx1 = (prx + 7) >> 4;
		cm_two_points_vertical ();
		if ((at1 & 8) || (at2 & 8)) {
			pvx = 0;
			prx = ((cx1 - 1) << 4) + 8;
			px = prx << FIX_BITS;
		}
	}

	// Calc cell
	if (ppossee || pgotten) {
		if (ABS (pvx) > PLAYER_VX_MIN && (!pslip || ppressingh)) {
			pfr = PCELL_WALK_BASE + ((prx >> 4) & 3);
		} else pfr = PCELL_STANDING;
	} else {
		pfr = PCELL_AIRBORNE;
	}

	px_world = (n_pant << 8) | prx;
}

void player_render (void) {
	if (half_life || !pflickers) oam_index = oam_meta_spr (
		px_world - cam_pos,
		SPRITE_ADJUST + pry,
		oam_index,
		spr_pl [pfacing + pfr]
	);
}
