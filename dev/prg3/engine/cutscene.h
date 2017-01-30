// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Shows a cutscene

#define TOP 17

void flush_buffer (void) {
	*gp_ul = NT_UPD_EOF;
	ppu_wait_nmi ();
	gp_ul = update_list;
}

void cutscene_show (unsigned char n) {
	ppu_on_all ();
	scroll (0, 472);
	fade_in ();

	gp_gen = (unsigned char *) str_cuts0_index [n];

	reset = 1; clear = 0; cutscene_do = 1; 
	panic_exit = 0;
	set_vram_update (update_list);
	while (cutscene_do) {
		if (reset) {
			if (clear) {
				gp_addr = NAMETABLE_A + 2 + (TOP << 5);
				for (gpit = 0; gpit < 6; gpit ++) {
					gp_ul = update_list;
					UPDATE = MSB (gp_addr) | NT_UPD_HORZ;
					UPDATE = LSB (gp_addr);
					UPDATE = 32;
					gpjt = 32; while (gpjt --) UPDATE = 0xff;
					*gp_ul = NT_UPD_EOF;
					delay (4);
					gp_addr += 64;
				}
			} else clear = 1;

			rdy = TOP; rdx = 3;
			reset = 0;
			flush = 0;
		}

		rda = *gp_gen ++;

		if (!rda) {
			cutscene_do = 0;
		} else if (rda == NEW_LINE) {
			rdx = 3; rdy += 2;
			if (flush) flush_buffer ();
		} else if (rda == NEW_PAGE) {
			while (pad_poll (0));
			if (flush) flush_buffer ();
			while (!pad_poll (0) & (PAD_A || PAD_B)); 
			reset = 1;
		} else {
			if (!flush) gp_ul = update_list;
			gp_addr = NAMETABLE_A + rdx + (rdy << 5); rdx ++;
			UPDATE = MSB (gp_addr);
			UPDATE = LSB (gp_addr);
			UPDATE = rda;
				if (!flush) {
				*gp_ul = NT_UPD_EOF;
				gpit = 4; while (gpit --) {
					ppu_wait_nmi ();
					rdb = pad_poll (0);
					if (rdb & PAD_START) {
						cutscene_do = 0;
						panic_exit = 1;
						break;
					} else if (rdb) {
						flush = 1;
						gp_ul = update_list;
						while (pad_poll (0));
						break;
					}
				}
			}
		}
	}

	while (pad_poll (0));

	set_vram_update (0);
	
	fade_out ();
	scroll (0,0);
	ppu_off ();
}
