// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Printing routines

void split_and_wait (void) {
	split (cam_pos & 0x1ff, SCROLL_Y); ppu_wait_nmi ();
}

void fade_out_split (void) {
	for (fader = 4; fader > -1; fader --) {
		pal_bright (fader);
		split_and_wait ();
	}	
}

void fade_in_split (void) {
	for (fader = 0; fader < 5; fader ++) {
		pal_bright (fader);
		split_and_wait ();
	}	
}

void delay_split (unsigned char n) {
	gpit = n; while (gpit --) split_and_wait ();
}

void fade_out (void) { fader = 5; while (fader --) { pal_bright (fader); ppu_wait_nmi (); } }	

void fade_in (void) { fader = 5; while (fader --) { pal_bright (4 - fader); ppu_wait_nmi (); } }
	
void cls (void) { vram_adr (NAMETABLE_A); vram_fill (0, 0x800); }

void p_t2 (unsigned char x, unsigned char y, unsigned char n) {
	gp_addr = NAMETABLE_A + (y << 5) + x;
	UPDATE = MSB (gp_addr) | NT_UPD_HORZ;
	UPDATE = LSB (gp_addr);
	UPDATE = 2;	
	UPDATE = DIGIT ((n / 10));
	UPDATE = DIGIT ((n % 10));
}

void p_s (unsigned char x, unsigned char y, unsigned char *s) {
	vram_adr (NAMETABLE_A + (y << 5) + x);
	while (rda = *s ++) {
		if (rda == '%') {
			y ++; vram_adr (NAMETABLE_A + (y << 5) + x);
		} else vram_put (rda - 32);
	}
}

void fx_flash (const unsigned char *pal) {
	c_pal_back = pal; ct_flash = 4;		
}