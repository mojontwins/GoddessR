// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Update list helpers

void update_buffered_tile (void) {
	// paints tile rdt at rdx<<1, rdy<<1 in the update list
	// and writes it to the screen buffer at nametable rdct

	// Beware! In this game metatile definitions are in prg0.
	// This function gets called from prg2 so I MUST PAGE IT BACK IN!
	// This makes this code not über portable, but 8 bits are... 8 bits.

	*(scr_buffer + (rdct ? 192 : 0) + rdx + (rdy << 4)) = behs [rdt];

	// Paint
	gp_addr = (rdct ? NAMETABLE_B : NAMETABLE_A) + (rdx << 1) + nt_tile_offsets_y [rdy];
	//bankswitch (0);
	bankswitch_prg_a (PRG_BANK_A_SCROLL);
	bankswitch_prg_b (PRG_BANK_B_SCROLL);

	UPDATE = MSB (gp_addr) | NT_UPD_HORZ;
	UPDATE = LSB (gp_addr);
	UPDATE = 2;
	UPDATE = main_ts_tmaps_0 [rdt];
	UPDATE = main_ts_tmaps_1 [rdt];

	gp_addr += 32;
	UPDATE = MSB (gp_addr) | NT_UPD_HORZ;
	UPDATE = LSB (gp_addr);
	UPDATE = 2;
	UPDATE = main_ts_tmaps_2 [rdt];
	UPDATE = main_ts_tmaps_3 [rdt];

	// Don't forget!
	bankswitch_prg_a (PRG_BANK_A_MAIN_DATA);
	bankswitch_prg_b (PRG_BANK_B_MAIN);
}
