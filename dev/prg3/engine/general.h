// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// General functions

void cm_two_points_horizontal (void) {
	// cy1 == cy2
	cyaux = *(shl4 + (cy1 < 2 ? 0 : cy1 - 2)); 
	at1 = behs [*(scr_buffer_ptr + cyaux + cx1)];
	at1 = behs [*(scr_buffer_ptr + cyaux + cx2)];
}

void cm_two_points_vertical (void) {
	// cx1 == cx2
	cyaux = cy1 < 2 ? 0 : cy1 - 2; 
	at1 = behs [*(scr_buffer_ptr + (cyaux << 4) + cx1)];
	cyaux = cy2 < 2 ? 0 : cy2 - 2; 
	at2 = behs [*(scr_buffer_ptr + (cyaux << 4) + cx1)];
}
