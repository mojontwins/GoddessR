// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Game loop routines

void game_init (void) {
	// Decompress patterns from tileset #1
	bankswitch (1);
	tokumaru_lzss (main_ts_patterns_c,  0);
	tokumaru_lzss (chars_ts_patterns_c, 3584);	// 224*16
	tokumaru_lzss (main_ss_patterns_c,  4096);	// 256*16

	if (pcontinues) {
		level = 1; n_pant = 9;
	} else {
		stage = 0;
		level = LEVEL_INI; n_pant = SCR_INI;		
	}

	c_pal_fg = mypal_game_fg0;

	c_enems_t = enems_t_0;
	c_enems_yx1 = enems_yx1_0;
	c_enems_yx2 = enems_yx2_0;
	c_enems_mn = enems_mn_0;

	c_hotspots_yx = hotspots_yx_0;
	c_hotspots_t = hotspots_t_0;

	guay_ct = 0;
	gpit = 4; while (gpit --) gs_flags [gpit] = 0;

	bankswitch (2);
	player_init ();
	hotspots_init ();

	// Debug shyte:
	//level = 0;n_pant=0;pinv=4;pcharges=3;
	//level = 1; n_pant = 0x0d; pinv = 4; pcharges = 3;
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
	c_pal_bg = c_pal_bgs [stage];

	bankswitch (2);
	pal_bg (c_pal_bg);
	pal_spr (c_pal_fg);
	palfx_init ();
	
	// Inits
	bg_object_init ();
	game_strip_setup ();
	hud_and_split_setup ();

	// Screen
	bankswitch (0);
	scroll_draw_screen ();
	ppu_on_all ();

	set_vram_update (update_list);

	// Preload enems, bg objects, hotspots
	bankswitch (2);

	scroll_state = SCROLL_STATE_FREE;
	for (frame_counter = 0; frame_counter < 3; frame_counter ++) {
		gp_ul = update_list;
		bg_object_do ();
		*gp_ul = NT_UPD_EOF;
		ppu_wait_nmi ();
	}
	
	cam_pant = MSB (cam_pos);
	rdpant = cam_pant; enems_load (); hotspots_load ();
	rdpant = cam_pant + 1; enems_load (); hotspots_load ();
	cam_pant_old = MSB (cam_pos);
	
	SCR_BUFFER_PTR_UPD;
	fade_in_split ();

	no_ct = tt_ct = half_life = psignal = 0;

	if (!cutscene) {
		if (!music_on) {
			music_play (MUSIC_INGAME_BASE + stage);
			music_on = 1;
		} else music_pause (0);
	}

	// Do
	game_res = 0;
	frame_counter = 0;
	while (!game_res) {
		half_life = 1 - half_life;
		frame_counter ++;
		gp_ul = update_list;

		bankswitch (2);
		palfx_do ();
		
		pad0 = pad_poll (0);

		//*((unsigned char*)0x2001) = 0x1e;
		split (cam_pos & 0x1ff, SCROLL_Y);
		//*((unsigned char*)0x2001) = 0x1f;

		game_stuff_preload ();

		if (!ntsc || fskip_ctr < 5) {
			oam_index = 28;
			if (cutscene) {
				bg_object_do ();
				hotspots_do ();
			} else {
				player_move ();
				camera_do ();
				bg_object_do ();
				enems_do ();
				player_render ();
				hotspots_do ();
			}
			hud_do ();
			oam_hide_rest (oam_index);
		}
		fskip_ctr ++; if (fskip_ctr == 6) fskip_ctr = 0;

		bankswitch (0);
		scroll_to ();
		
		*gp_ul = NT_UPD_EOF;
		
		//*((unsigned char*)0x2001) = 0x1e;
		bankswitch (2);
		ppu_wait_nmi ();
		//*((unsigned char*)0x2001) = 0x1f;

		// Exit conditions

		if (psignal) {
			if (psignal == PLAYER_KILLED) {
				// sfx_play (SFX_ENEMY_HIT, SC_PLAYER);
				music_pause (1);
				delay_split (ticks);
			}
			game_res = psignal;
		}

		if (px_world < section_x0 + 4) game_res = PLAYER_EXIT_LEFT;
		else if (px_world > section_x1 + 244) game_res = PLAYER_EXIT_RIGHT;	

		if (pad0 & PAD_SELECT) {
			sfx_play (SFX_SHOW_MAP, SC_PLAYER);
			game_res = PLAYER_MAP;
		}

		if (cutscene && !frame_counter) game_res = PLAYER_RESTORE;
	}

	bankswitch (2);
	fade_out_split ();
	oam_hide_rest (4);
	set_vram_update (0);
	ppu_off ();
}

void game_title (void) {

}

void game_over (void) {

}

void game_ending (void) {

}

void game_intro (void) {

}
