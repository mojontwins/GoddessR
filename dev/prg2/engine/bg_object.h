// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Chac Chac routines

void update_buffered_tile (void); // Sorry

void bg_object_init (void) {
	ccit = BG_OBJS_MAX; while (ccit --) bgo_col_idx [ccit] = 0;
	bgo_total = 0;
}

void bg_object_draw_this (void) {
	rdd = bgo_s [ccit];
	rdct = bgo_pant [ccit]; rdx = bgo_x [ccit];
	rdy = bgo_y [ccit];
	if (rda) {
		rdt = column_tiles_0 [rdd];
		update_buffered_tile ();
		rdy ++; rdt = column_tiles_1 [rdd];
		update_buffered_tile ();
		rdy ++; rdt = column_tiles_2 [rdd];
		update_buffered_tile ();
	} else {
		rdt = main_gate_tiles_0 [rdd];
		update_buffered_tile ();
		rdy ++; rdt = main_gate_tiles_1 [rdd];
		update_buffered_tile ();
		rdy ++; rdt = main_gate_tiles_2 [rdd];
		update_buffered_tile ();
	}
}

void bg_object_do (void) {
	// prevent
	if (scroll_state == SCROLL_STATE_NONE || 0 == bgo_total) return;

	ccit = BG_OBJS_MAX; while (ccit --) {
		if (bgo_col_idx [ccit]) {
			// First, delete?
			gpint = cam_pos >> 5;
			if (bgo_col_idx [ccit] + 1 < gpint ||
				bgo_col_idx [ccit] > gpint + 9) {
				bgo_col_idx [ccit] = 0;
				bgo_total --;
			} else {
				rda = 0;
				switch (bgo_type [ccit]) {
					case 48:
						// CHAC CHAC
						if (bgo_ctr [ccit]) bgo_ctr [ccit] --; else {
							rdd = bgo_s [ccit];
							rdct = bgo_pant [ccit]; rdx = bgo_x [ccit];
							rdy = bgo_y [ccit]; rdt = chac_chac_tiles_0 [rdd];
							update_buffered_tile ();
							rdy ++; rdt = chac_chac_tiles_1 [rdd];
							update_buffered_tile ();
							rdy ++; rdt = chac_chac_tiles_2 [rdd];
							update_buffered_tile ();
							
							bgo_ctr [ccit] = bg_object_times [rdd];

							bgo_s [ccit] ++; if (bgo_s [ccit] == 6) bgo_s [ccit] = 0;
						}
						break;
					case 99:
						rda = 1;
					case 96:
					case 97:
					case 98:
						if (bgo_ctr [ccit]) bgo_ctr [ccit] --; else {
							if ((frame_counter & 3) == bgo_type [ccit] - 96) {
								bg_object_draw_this ();

								if (gs_flags [bgo_type [ccit] - 96] && rdd < 2) {
									bgo_ctr [ccit] = 50;
									bgo_s [ccit] ++;
								} else bgo_ctr [ccit] = 0;
							}
						}
						break;
				}
			}
		}
	}
}
