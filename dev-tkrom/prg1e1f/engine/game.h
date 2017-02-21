// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Game loop routines

void game_init (void) {
	// Setup CHR
	tkrom_bankswitch (BG_BANK_0, CHR_BANK_TS_GAME);
	tkrom_bankswitch (BG_BANK_1, CHR_BANK_TS_GAME + 1);
	tkrom_bankswitch (BG_BANK_2, CHR_BANK_TS_GAME + 2);
	tkrom_bankswitch (BG_BANK_3, CHR_BANK_TS_GAME + 3);

	tkrom_bankswitch (FG_BANK_01, CHR_BANK_SPRITESET);
	tkrom_bankswitch (FG_BANK_23, CHR_BANK_SPRITESET + 2);

	// Setup PRG
	bankswitch_prg_a (PRG_BANK_A_MAIN_DATA);
	bankswitch_prg_b (PRG_BANK_B_MAIN);

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
		// Must return the carried object to its place
		if (pinv != 0xff) hotspots_restore_carried_object ();
	} else {
		stage = 0;
		level = LEVEL_INI; n_pant = SCR_INI;	
		gpit = 4; while (gpit --) gs_flags [gpit] = 0;	
		hotspots_init ();
	}

	player_init ();	// Remember pinv is reset here.

	// Debug shyte:
	//level = 0;n_pant=0;pinv=4;pcharges=3;
	//level = 3; n_pant = 17; pcharges = 3;
	//gpit = 4; while (gpit --) gs_flags [gpit] = 2;	
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

	bankswitch_prg_b (PRG_BANK_B_ENEMS);
	enems_load ();
	bankswitch_prg_b (PRG_BANK_B_MAIN);
	hotspots_load ();
}

void game_loop (void) {
	bankswitch_prg_a (PRG_BANK_A_MAIN_DATA);
	bankswitch_prg_b (PRG_BANK_B_MAIN);

	if (!soft_reenter) {
		// Add palette selection logic - later
		c_pal_bg = c_pal_bgs [stage];
		
		pal_bg (c_pal_bg);
		pal_spr (c_pal_fg);
		palfx_init ();
		
		// Inits
		bg_object_init ();
		game_strip_setup ();
	} 
	hud_and_split_setup ();

	// Screen
	bankswitch_prg_a (PRG_BANK_A_SCROLL);
	bankswitch_prg_b (PRG_BANK_B_SCROLL);
	scroll_draw_screen ();
	ppu_on_all ();

	set_vram_update (update_list);

	// Preload enems, bg objects, hotspots
	bankswitch_prg_a (PRG_BANK_A_MAIN_DATA);
	bankswitch_prg_b (PRG_BANK_B_MAIN);

	scroll_state = SCROLL_STATE_FREE;
	for (frame_counter = 0; frame_counter < 3; frame_counter ++) {
		gp_ul = update_list;
		bg_object_do ();
		*gp_ul = NT_UPD_EOF;
		ppu_wait_nmi ();
	}
	
	if (!soft_reenter) {
		cam_pant = MSB (cam_pos);
		rdpant = cam_pant; 
		bankswitch_prg_b (PRG_BANK_B_ENEMS);
		enems_load (); 
		bankswitch_prg_b (PRG_BANK_B_MAIN);
		hotspots_load ();
		rdpant = cam_pant + 1; 
		bankswitch_prg_b (PRG_BANK_B_ENEMS);
		enems_load (); 
		bankswitch_prg_b (PRG_BANK_B_MAIN);
		hotspots_load ();
		cam_pant_old = MSB (cam_pos);
	}

	SCR_BUFFER_PTR_UPD;
	fade_in_split ();

	if (!cutscene) {
		if (!music_on) {
			music_play (MUSIC_INGAME_BASE + stage);
			music_on = 1;
		} else music_pause (0);
	}

	// Zero stuff
	
	soft_reenter = game_res = frame_counter = 0;
	paused = no_ct = tt_ct = half_life = psignal = 0;

	// And do

	while (!game_res) {
		if (!paused) {
			half_life = 1 - half_life;
			frame_counter ++;
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
			if (paused) { 
				pal_bright (4); 
				music_pause (0);
			} else { 
				pal_bright (3);
				music_pause (1);
			}
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
					bankswitch_prg_b (PRG_BANK_B_ENEMS);
					enems_do ();
					bankswitch_prg_b (PRG_BANK_B_MAIN);
					player_render ();
					hotspots_do ();
				}
				hud_do ();
				oam_hide_rest (oam_index);
			}
			fskip_ctr ++; if (fskip_ctr == 6) fskip_ctr = 0;

			bankswitch_prg_a (PRG_BANK_A_SCROLL);
			bankswitch_prg_b (PRG_BANK_B_SCROLL);
			scroll_to ();
			bankswitch_prg_a (PRG_BANK_A_MAIN_DATA);
			bankswitch_prg_b (PRG_BANK_B_MAIN);
		}
		
		*gp_ul = NT_UPD_EOF;
		
		//*((unsigned char*)0x2001) = 0x1e;
		ppu_wait_nmi ();
		//*((unsigned char*)0x2001) = 0x1f;

		// Exit conditions

		if (psignal) {
			if (psignal == PLAYER_KILLED) {
				music_pause (1);
				delay_split (ticks);
			} else if (psignal == PLAYER_WINS) {
				music_stop  ();
				delay_split (8);
				music_play (MUSIC_CLEAR);
				ticker = ticks; game_time = 7;
				while (game_time) {
					if (ticker) ticker --; else {
						ticker = ticks; game_time --;
					}
					split_and_wait ();
				}
				music_stop ();
			}
			game_res = psignal;
		}

		if (px_world < section_x0 + 4) game_res = PLAYER_EXIT_LEFT;
		else if (px_world > section_x1 + 244) game_res = PLAYER_EXIT_RIGHT;	

		if (pad0 & PAD_SELECT) {
			sfx_play (SFX_SHOW_MAP, SC_PLAYER);
			game_res = PLAYER_MAP;
			soft_reenter = 1;
		}

		if ((cutscene == 1 && frame_counter == 0) || (cutscene == 2 && frame_counter == 90)) game_res = PLAYER_RESTORE;
	}

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
	bankswitch_prg_b (PRG_BANK_B_MAIN);

	// Setup CHR
	tkrom_bankswitch (BG_BANK_0, CHR_BANK_FONT);
	tkrom_bankswitch (BG_BANK_1, CHR_BANK_ENDING + 1);
	tkrom_bankswitch (BG_BANK_2, CHR_BANK_ENDING + 2);

	// Setup PRG
	bankswitch_prg_a (PRG_BANK_A_MAIN_DATA);
	pal_bg (mypal_ending);

	bankswitch_prg_a (PRG_BANK_A_RLE_SCREENS);
	vram_adr (NAMETABLE_A);
	vram_unrle (ending_rle);

	music_play (MUSIC_TITLE);

	cutscene_show (3);
	music_stop ();
	delay (ticks);
}

void game_intro (void) {
	// General
	bankswitch_prg_b (PRG_BANK_B_MAIN);
	tkrom_bankswitch (BG_BANK_0, CHR_BANK_FONT);
	
	// Play music
	music_play (MUSIC_CUTSCENE);

	// Show plate 1
	tkrom_bankswitch (BG_BANK_1, CHR_BANK_CUTS1 + 0);
	tkrom_bankswitch (BG_BANK_2, CHR_BANK_CUTS1 + 1);
	
	bankswitch_prg_a (PRG_BANK_A_RLE_SCREENS);
	vram_adr (NAMETABLE_A);
	vram_unrle (plate1_rle);

	bankswitch_prg_a (PRG_BANK_A_MAIN_DATA);
	cutscene_show (0);

	if (!panic_exit) {
		// Show plate 2

		tkrom_bankswitch (BG_BANK_1, CHR_BANK_CUTS2 + 0);
		tkrom_bankswitch (BG_BANK_2, CHR_BANK_CUTS2 + 1);

		bankswitch_prg_a (PRG_BANK_A_RLE_SCREENS);
		vram_adr (NAMETABLE_A);
		vram_unrle (plate2_rle);
		
		bankswitch_prg_a (PRG_BANK_A_MAIN_DATA);
		cutscene_show (1);
	}
	
	if (!panic_exit) {
		cls ();
		cutscene_show (2);
	}	

	music_stop ();
}
