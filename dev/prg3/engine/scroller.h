// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Scrolling stuff. Everything you need is in prg0, so page it in.

void scroll_chac_chac_create (void) {
	// I could do something prettier but RAM is tight, time is tight
	// And my ass is NOT tight.

	if (col_idx == cc_col_idx [0] || 
		col_idx == cc_col_idx [1] || 
		col_idx == cc_col_idx [2] || 
		col_idx == cc_col_idx [3] ||
		col_idx == cc_col_idx [4]) return;

	// Discard?
	ccit = CHAC_CHAC_MAX; while (ccit --) {
		if (0 == cc_col_idx [ccit]) {
			cc_x [ccit] = rdc >> 1;
			cc_pant [ccit] = (col_idx >> 3) & 1;
			cc_y [ccit] = rdd + (rdct >> 1);
			cc_s [ccit] = 0;
			cc_ctr [ccit] = chac_chac_times [5] + (rand8 () & 0x1f);
			cc_col_idx [ccit] = col_idx;
			cc_total ++;
			break;
		}
	}
}

void scroll_paint_chunk (void) {
	// Calculate memory address of current column [col_idx * 24]
	gpint = col_idx << 2;
	// 24 = 12 * 2 = (4*3)*2
	col_ptr = map_ptr + ((gpint + gpint + gpint) << 1);

	// VRAM address
	rdc = gpint & 31;
	rdd = (col_idx & 8);

	scroll_state = SCROLL_STATE_NONE;

	if (state_ctr < 6) {
		// State 0..5: draw patterns. 4x4 chunk

		// where to paint
		rdct = (state_ctr << 2);
		gp_addr = (rdd ? NAMETABLE_B : NAMETABLE_A) + rdc + col_v_offset;
		gp_aux = (unsigned char *) (col_ptr + rdct);
		gp_gen = gp_aux;
		
		// Two metatiles
		rda = *gp_gen ++; rdb = *gp_gen ++;

		// Chac chac creation. Note there's an increible
		// shortcut: chac chacks must have X even
		if (rda == CHAC_CHAC_BASE_TILE) {
			rdd = 0; scroll_chac_chac_create ();
			rda = 54;
		}
		
		UPDATE = MSB (gp_addr) | NT_UPD_HORZ;
		UPDATE = LSB (gp_addr);
		UPDATE = 4;
		UPDATE = main_ts_tmaps_0 [rda];
		UPDATE = main_ts_tmaps_1 [rda];
		UPDATE = main_ts_tmaps_0 [rdb];
		UPDATE = main_ts_tmaps_1 [rdb];
		
		gp_addr += 32;

		UPDATE = MSB (gp_addr) | NT_UPD_HORZ;
		UPDATE = LSB (gp_addr);
		UPDATE = 4;
		UPDATE = main_ts_tmaps_2 [rda];
		UPDATE = main_ts_tmaps_3 [rda];
		UPDATE = main_ts_tmaps_2 [rdb];
		UPDATE = main_ts_tmaps_3 [rdb];

		gp_addr += 32;

		// Two metatiles more
		rda = *gp_gen ++; rdb = *gp_gen;

		// Chac chac creation. Note there's an increible
		// shortcut: chac chacks must have X even
		if (rda == CHAC_CHAC_BASE_TILE) {
			rdd = 1; scroll_chac_chac_create ();
			rda = 54;
		}
		
		UPDATE = MSB (gp_addr) | NT_UPD_HORZ;
		UPDATE = LSB (gp_addr);
		UPDATE = 4;
		UPDATE = main_ts_tmaps_0 [rda];
		UPDATE = main_ts_tmaps_1 [rda];
		UPDATE = main_ts_tmaps_0 [rdb];
		UPDATE = main_ts_tmaps_1 [rdb];
		
		gp_addr += 32;

		UPDATE = MSB (gp_addr) | NT_UPD_HORZ;
		UPDATE = LSB (gp_addr);
		UPDATE = 4;
		UPDATE = main_ts_tmaps_2 [rda];
		UPDATE = main_ts_tmaps_3 [rda];
		UPDATE = main_ts_tmaps_2 [rdb];
		UPDATE = main_ts_tmaps_3 [rdb];

		// Next chunk at
		col_v_offset += 128;

		// Write a bit in the collision buffer
		gp_gen = gp_aux;
		gp_aux = scr_buffer + (rdd ? 192 : 0) + ((col_idx & 0x7) << 1) + scr_v_offset;
		*gp_aux ++ = behs [*gp_gen ++]; *gp_aux = behs [*gp_gen ++]; gp_aux += 15;
		*gp_aux ++ = behs [*gp_gen ++]; *gp_aux = behs [*gp_gen];
		scr_v_offset += 32;
	} else if (state_ctr < 7) {
		// State 6: fetch & paint attrs.
	
		// which nametable?
		gp_addr = (rdd ? NAMETABLE_B : NAMETABLE_A) + 0x03c0 + (col_idx & 0x7);
		gp_gen = (unsigned char *) col_ptr;

		gpit = 6; do {
			rda = *gp_gen ++;
			rdt = attr_lookup_0_0 [rda];
			rda = *gp_gen ++;
			rdt += attr_lookup_0_1 [rda];
			rda = *gp_gen ++;
			rdt += attr_lookup_0_2 [rda];
			rda = *gp_gen ++;
			rdt += attr_lookup_0_3 [rda];
			UPDATE = MSB (gp_addr);
			UPDATE = LSB (gp_addr);
			UPDATE= rdt;
			gp_addr += 8;
		} while (-- gpit);

		col_v_offset = scr_v_offset = 0;
	} else {
		// State 7: Free state. We just signal this to the engine
		// so it can perform other tasks.

		scroll_state = SCROLL_STATE_FREE;
	}

	state_ctr = (state_ctr + 1) & 7;
}

void scroll_draw_one_chunk_completely (void) {
	state_ctr = col_v_offset = scr_v_offset = 0;
	gp_ul = update_list;
	scroll_paint_chunk ();
	scroll_paint_chunk ();
	scroll_paint_chunk ();
	*gp_ul = NT_UPD_EOF;
	ppu_wait_nmi ();
	gp_ul = update_list;
	scroll_paint_chunk ();
	scroll_paint_chunk ();
	scroll_paint_chunk ();
	*gp_ul = NT_UPD_EOF;
	ppu_wait_nmi ();
	gp_ul = update_list;
	scroll_paint_chunk ();
	scroll_paint_chunk ();
	*gp_ul = NT_UPD_EOF;
	ppu_wait_nmi ();
}

void scroll_to (void) {
	// Updates nametables upon direction
	if (cam_pos > cam_pos_old) {
		col_idx = (cam_pos >> 5) + 9;
		scroll_paint_chunk ();
	} else if (cam_pos < cam_pos_old) {
		col_idx = (cam_pos >> 5) - 1;
		scroll_paint_chunk ();
	} else scroll_state = SCROLL_STATE_FREE;

	cam_pos_old = cam_pos;
}

void scroll_draw_screen (void) {
	// Redraw
	cx1 = (cam_pos >> 5); if (cx1) cx1 --;
	cx2 = cx1 + 10;
	for (col_idx = cx1; col_idx <= cx2; col_idx ++) {
		scroll_draw_one_chunk_completely ();
	}
}
