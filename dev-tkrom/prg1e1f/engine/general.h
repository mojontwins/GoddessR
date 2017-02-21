// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// General functions

/*
void cm_two_points_horizontal (void) {
	// cy1 == cy2
	cyaux = (cy1 < 2 ? 0 : cy1 - 2) << 4; 
	at1 = behs [*(scr_buffer_ptr + cyaux + cx1)];
	at2 = behs [*(scr_buffer_ptr + cyaux + cx2)];
}

void cm_two_points_vertical (void) {
	// cx1 == cx2
	cyaux = cy1 < 2 ? 0 : cy1 - 2; 
	at1 = behs [*(scr_buffer_ptr + (cyaux << 4) + cx1)];
	cyaux = cy2 < 2 ? 0 : cy2 - 2; 
	at2 = behs [*(scr_buffer_ptr + (cyaux << 4) + cx1)];
}
*/

void bankswitch_prg_a (unsigned char page) {
	tkrom_bankswitch (0x86, page);
}

void bankswitch_prg_b (unsigned char page) {
	tkrom_bankswitch (0x87, page);
}

void hitit (void) {
	pal_bright (4);
	pal_col (0, 0);
	ppu_on_all ();
	while (1) ppu_wait_nmi ();
}