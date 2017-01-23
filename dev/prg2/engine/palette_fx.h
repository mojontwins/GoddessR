
void palfx_do (void) {
	if (ct_flash) {
		if (ct_flash == 4) {
			pal_bg (mypal_light_bg);
			pal_spr (mypal_light_fg);
		}
		ct_flash --;
		if (ct_flash == 0) {
			pal_bg (c_pal_back);
			pal_spr (c_pal_fg);
		}
	} else if ((frame_counter & 15) == 0) {
		gpit = pal_cycle [2]; 
		pal_cycle [2] = pal_cycle [1]; 
		pal_cycle [1] = pal_cycle [0]; 
		pal_cycle [0] = gpit; 
		pal_col (13, pal_cycle [0]);
		pal_col (14, pal_cycle [1]);
		pal_col (15, pal_cycle [2]);
	}
}

void palfx_init (void) {
	pal_cycle [0] = c_pal_bg [13];
	pal_cycle [1] = c_pal_bg [14];
	pal_cycle [2] = c_pal_bg [15];
}
