// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Hud & scroll split setup routines.

void hud_and_split_setup (void) {
	scroll (0, SCROLL_Y);
	vram_adr (NAMETABLE_A);
	vram_unrle (hud_rle);
	oam_spr (254, 27, 0, 3, 0);	// Sprite 0
}

void hud_do (void) {
	oam_index = oam_meta_spr (
		136, 15,
		oam_index,
		spr_it [ (pinv > 3 && pinv < 7) ? pinv : 3 ]
	); 
}
