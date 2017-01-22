// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Game loop routines

void game_init (void) {
	// Decompress patterns from tileset #1
	bankswitch (1);
	tokumaru_lzss (main_ts_patterns_c,      0);
	tokumaru_lzss (hex_digit_ts_patterns_c, 3840);	// 240*16
	tokumaru_lzss (main_ss_patterns_c,      4096);	// 256*16

	level = LEVEL_INI; n_pant = SCR_INI;

	bankswitch (2);
	player_init ();

	c_pal_bg = mypal_game_bg0;
	c_pal_fg = mypal_game_fg0;

	c_enems_t = enems_t_0;
	c_enems_yx1 = enems_yx1_0;
	c_enems_yx2 = enems_yx2_0;
	c_enems_mn = enems_mn_0;

	c_hotspots_yx = hotspots_yx_0;
	c_hotspots_t = hotspots_t_0;

	hotspots_init ();
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

void game_stuff_preload (void) {
	// loads 3 enems & 1 hotspot to the right spot in the arrays
	// rda == n_pant

	cam_pant = MSB (cam_pos);

	if (cam_pant == cam_pant_old) return;

	if (cam_pant > cam_pant_old) rdpant = cam_pant + 1;
	else rdpant = cam_pant;	

	cam_pant_old = cam_pant;

	enems_load ();
	hotspots_load ();
}

void game_loop (void) {
	// Add palette selection logic - later
	bankswitch (1);
	pal_bg (c_pal_bg);
	pal_spr (c_pal_fg);
	palfx_init ();
	
	// Inits
	bankswitch (2);
	chac_chac_init ();
	game_strip_setup ();

	// Screen
	ppu_on_all ();
	scroll (cam_pos & 0x1ff, 448);
	set_vram_update (update_list);
	bankswitch (0);
	scroll_draw_screen ();

	// Preload enems
	bankswitch (2);
	rdpant = n_pant; 
	enems_load (); hotspots_load ();
	rdpant = n_pant < 19 ? n_pant + 1 : n_pant - 1; 
	enems_load (); hotspots_load ();
	cam_pant_old = MSB (cam_pos);
	
	SCR_BUFFER_PTR_UPD;
	fade_in ();

	half_life = phit = 0;

	// Do
	game_res = 0;
	while (!game_res) {
		*((unsigned char*)0x2001) = 0x1f;

		half_life = 1 - half_life;
		frame_counter ++;
		gp_ul = update_list;
		
		bankswitch (2);
		game_stuff_preload ();

		if (!ntsc || fskip_ctr < 5) {
			pad0 = pad_poll (0);

			oam_index = 28;
			bankswitch (2);
			player_move ();
			camera_do ();
			chac_chac_do ();
			enems_do ();
			player_render ();
			hotspots_do ();

			if (px_world < section_x0 + 4) game_res = PLAYER_EXIT_LEFT;
			else if (px_world > section_x1 + 244) game_res = PLAYER_EXIT_RIGHT;

			bankswitch (2);
			oam_hide_rest (oam_index);
		}
		fskip_ctr ++; if (fskip_ctr == 6) fskip_ctr = 0;

		bankswitch (0);
		scroll_to ();

		bankswitch (1);
		palfx_do ();
		
		*gp_ul = NT_UPD_EOF;
		
		*((unsigned char*)0x2001) = 0x1e;
		scroll (cam_pos & 0x1ff, 448);
		ppu_wait_nmi ();

		if (phit) {
			// sfx_play (SFX_ENEMY_HIT, SC_PLAYER);
			music_stop ();
			delay (ticks);
			game_res = PLAYER_KILLED;
		}
	}

	bankswitch (2);
	fade_out ();
	oam_hide_rest (0);
	set_vram_update (0);
	ppu_off ();
}
