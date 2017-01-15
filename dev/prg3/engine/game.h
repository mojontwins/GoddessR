// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Game loop routines

void game_init (void) {
	// Decompress patterns from tileset #1
	bankswitch (1);
	tokumaru_lzss (main_ts_patterns_c, 0);
	tokumaru_lzss (main_ss_patterns_c, 4096);

	level = 3; n_pant = 9;

	bankswitch (2);
	player_init ();

	c_pal_bg = mypal_game_bg0;
	c_pal_fg = mypal_game_fg0;
}

void game_strip_setup (void) {
	base_pant = (level << 4) + (level << 2); // * 20 
	map_ptr = map_0 + (base_pant << 7) + (base_pant << 6); // * 192
	px_world = (n_pant << 8) | prx;

	// Select scroll section
	section_x0 = 0; section_x1 = 4864; // 320*16-256
	section = (signed int *) sections [level]; gpit = 1; while (section [gpit] < 5120) {
		if (px_world < section [gpit]) {
			section_x1 = section [gpit] - 256;
			break;
		} 
		section_x0 = section [gpit];
		gpit ++;
	}

	camera_do ();
}

void game_loop (void) {
	// Add palette selection logic - later
	bankswitch (1);
	pal_bg (c_pal_bg);
	pal_spr (c_pal_fg);
	palfx_init ();
	
	// Inits
	bankswitch (2);
	game_strip_setup ();

	// Screen
	ppu_on_all ();
	scroll (cam_pos & 0x1ff, 448);
	set_vram_update (update_list);
	bankswitch (0);
	scroll_draw_screen ();

	bankswitch (2);
	SCR_BUFFER_PTR_UPD;
	fade_in ();

	half_life = 0;

	// Do
	game_res = 0;
	while (!game_res) {
		half_life = 1 - half_life;
		frame_counter ++;
		gp_ul = update_list;
		oam_index = 4;

		pad0 = pad_poll (0);

		bankswitch (2);
		player_move ();
		camera_do ();
		player_render ();

		if (px_world < section_x0) game_res = PLAYER_EXIT_LEFT;
		else if (px_world > section_x1 + 240) game_res = PLAYER_EXIT_RIGHT;

		bankswitch (0);
		scroll_to ();

		bankswitch (1);
		palfx_do ();
		
		bankswitch (2);
		oam_hide_rest (oam_index);
		*gp_ul = NT_UPD_EOF;
		
		*((unsigned char*)0x2001) = 0x1e;

		scroll (cam_pos & 0x1ff, 448);
		ppu_wait_nmi ();

		*((unsigned char*)0x2001) = 0x1f;
	}

	fade_out ();
	oam_hide_rest (0);
	set_vram_update (0);
	ppu_off ();
}
