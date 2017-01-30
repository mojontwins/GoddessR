// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Game loop routines

void game_init (void) {
	// Decompress patterns from tileset #1
	bankswitch (1);
	tokumaru_lzss (main_ts_patterns_c,  	0);
	tokumaru_lzss (chars_ts_patterns_c, 	3584);	// 224*16
#ifdef THIS_IS_THE_USA
	tokumaru_lzss (main_ss_patterns_usa_c, 	4096);	// 256*16
#else
	tokumaru_lzss (main_ss_patterns_c,  	4096);	// 256*16
#endif
	bankswitch (2);

	c_pal_fg = mypal_game_fg0;

	c_enems_t = enems_t_0;
	c_enems_yx1 = enems_yx1_0;
	c_enems_yx2 = enems_yx2_0;
	c_enems_mn = enems_mn_0;

	c_hotspots_yx = hotspots_yx_0;
	c_hotspots_t = hotspots_t_0;

	guay_ct = 0;

	if (pcontinues) {
		level = 1; n_pant = 9;
	} else {
		stage = 0;
		level = LEVEL_INI; n_pant = SCR_INI;	
		gpit = 4; while (gpit --) gs_flags [gpit] = 0;	
		hotspots_init ();
	}

	player_init ();
	
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

	if (!cutscene) {
		if (!music_on) {
			music_play (MUSIC_INGAME_BASE + stage);
			music_on = 1;
		} else music_pause (0);
	}

	// Zero stuff
	
	game_res = frame_counter = 0;
	paused = no_ct = tt_ct = half_life = psignal = 0;

	// And do

	while (!game_res) {
		if (!paused) {
			half_life = 1 - half_life;
			frame_counter ++;
			bankswitch (2);
			palfx_do ();
		}
		gp_ul = update_list;
		
		// Thanks for this, Nicole & nesdev!
		// https://forums.nesdev.com/viewtopic.php?p=179315#p179315
		pad_this_frame = pad0;
		pad0 = pad_poll (0);
		pad_this_frame = (pad_this_frame ^ pad0) & pad0;
		if (pad_this_frame & PAD_START) {
			sfx_play (SFX_PAUSE, SC_LEVEL);
			if (paused) pal_bright (4); else pal_bright (3);
			paused = !paused;
		}

		//*((unsigned char*)0x2001) = 0x1e;
		split (cam_pos & 0x1ff, SCROLL_Y);
		//*((unsigned char*)0x2001) = 0x1f;

		if (!paused) {
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
		}
		
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
	enter_screen (mypal_game_bg0, screen_title);
	music_play (MUSIC_TITLE);
	while (1) {
		pad0 = pad_poll (0);
		if (pad0 & PAD_START) {
			pcontinues = 0; break;
		}
		if ((pad0 & PAD_SELECT) && !first_time) {
			pcontinues = 1; break;
		}
	}
	music_stop ();
	sfx_play (SFX_PAUSE, SC_LEVEL);
	bankswitch (2);
	fade_out ();
	if (!pcontinues) delay (halfticks);
	ppu_off ();
	first_time = 0;
}

void game_over (void) {
	enter_screen (mypal_game_bg0, screen_game_over);
	music_play (MUSIC_GAME_OVER);
	do_screen (10);
}

void game_ending (void) {

}

void game_intro (void) {
	bankswitch (1);
	tokumaru_lzss (font_ts_patterns_c,		0);
	tokumaru_lzss (cuts_p1_ts_patterns_c,	1024);

	bankswitch (2);
	vram_adr (NAMETABLE_A);
	vram_unrle (plate1_rle);

	cutscene_show (0);
	if (!panic_exit) {
		bankswitch (1);
		tokumaru_lzss (cuts_p2_ts_patterns_c,	1024);

		bankswitch (2);
		vram_adr (NAMETABLE_A);
		vram_unrle (plate2_rle);
		
		cutscene_show (1);
	}
	
	if (!panic_exit) {
		cls ();
		cutscene_show (2);
	}	
}
