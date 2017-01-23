// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Chac Chac routines

void update_buffered_tile (void); // Sorry

void chac_chac_init (void) {
	ccit = CHAC_CHAC_MAX; while (ccit --) cc_col_idx [ccit] = 0;
	cc_total = 0;
}

void chac_chac_do (void) {
	// prevent
	if (scroll_state == SCROLL_STATE_NONE || 0 == cc_total) return;

	ccit = CHAC_CHAC_MAX; while (ccit --) {
		if (cc_col_idx [ccit]) {
			// First, delete?
			gpint = cam_pos >> 5;
			if (cc_col_idx [ccit] + 1 < gpint ||
				cc_col_idx [ccit] > gpint + 9) {
				cc_col_idx [ccit] = 0;
				cc_total --;
			} else if (cc_ctr [ccit]) cc_ctr [ccit] --; else {
				rdd = cc_s [ccit];
				rdct = cc_pant [ccit]; rdx = cc_x [ccit];
				rdy = cc_y [ccit]; rdt = chac_chac_tiles_0 [rdd];
				update_buffered_tile ();
				rdy ++; rdt = chac_chac_tiles_1 [rdd];
				update_buffered_tile ();
				rdy ++; rdt = chac_chac_tiles_2 [rdd];
				update_buffered_tile ();
				
				cc_ctr [ccit] = chac_chac_times [rdd];

				cc_s [ccit] ++; if (cc_s [ccit] == 6) cc_s [ccit] = 0;
			}
		}
	}
}
