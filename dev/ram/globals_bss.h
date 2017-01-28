// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// BSS globals

// 50 or 60 depending on TV system
unsigned char ticks, halfticks;				
unsigned char ntsc;

// Update list for VBlank updates
static unsigned char update_list [1 + UPDATE_LIST_SIZE * 3];

// Collision buffer
unsigned char scr_buffer [384];

// Stuff
signed char fader;

// Palette fx
unsigned char pal_cycle [3];

// Current palettes
const unsigned char *c_pal_bg;
const unsigned char *c_pal_fg;

// Scroll state
unsigned char scroll_state;
signed int section_x0;
signed int section_x1;
signed int cam_pos_old;

// Chac chacs
unsigned char bgo_on [BG_OBJS_MAX];
unsigned char bgo_x [BG_OBJS_MAX], bgo_y [BG_OBJS_MAX];
unsigned char bgo_pant [BG_OBJS_MAX], bgo_s [BG_OBJS_MAX];
unsigned char bgo_ctr [BG_OBJS_MAX];
unsigned int bgo_col_idx [BG_OBJS_MAX];
unsigned char bgo_total;
unsigned char bgo_type [BG_OBJS_MAX];

// Level info
unsigned char stage; 	// Decides palette & music
unsigned char level;
unsigned char base_pant;
const signed int *section;
unsigned char game_res;
unsigned char fskip_ctr;

// Hotspots
unsigned char hrt [MAX_PANTS];
unsigned char hrx [2], hry [2], hrp [2];
unsigned char h_modify_this;

// Safe respawn
unsigned char safe_prx, safe_pry, safe_n_pant, safe_level;

// Hud & stats
unsigned char plife, pcharges, pinv;
unsigned char oplife, opcharges;
unsigned char pcontinues;

// Music
unsigned char music_on;

// Counters
unsigned char no_ct, tt_ct, use_ct, guay_ct;
unsigned char fr_ct;

// Flash fx
const unsigned char *c_pal_back;
unsigned char ct_flash;

// Game state flags
unsigned char gs_flags [4];
unsigned char gs_this_flag;

// Cutscene
unsigned char cutscene;
