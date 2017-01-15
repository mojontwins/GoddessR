
void palfx_do (void) {
	if ((frame_counter & 15) == 0) {
		gpit = pal_cycle [0]; 
		pal_cycle [0] = pal_cycle [1]; pal_col (13, pal_cycle [0]);
		pal_cycle [1] = pal_cycle [2]; pal_col (14, pal_cycle [1]);
		pal_cycle [2] = gpit; pal_col (15, pal_cycle [2]);
	}
}

void palfx_init (void) {
	pal_cycle [0] = c_pal_bg [13];
	pal_cycle [1] = c_pal_bg [14];
	pal_cycle [2] = c_pal_bg [15];
}
