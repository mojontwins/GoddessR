// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Zero page globals

// General
unsigned char rda, rdb, rdc, rdd, rdct, rdt;
unsigned char rdx, rdy;

unsigned char gpit, gpjt;
unsigned int gpint;

unsigned char *gp_gen, *gp_aux, *gp_ul;
unsigned int gp_addr;

// Update 
unsigned char oam_index;

// Pad control
unsigned char pad0, pad;						

// Game counters
unsigned char half_life;
unsigned char frame_counter;

// Scrolling engine
unsigned int col_idx;
const unsigned char *col_ptr;
const unsigned char *map_ptr;
unsigned char state_ctr;
unsigned int col_v_offset;

signed int cam_pos, cam_pos_old;
signed int section_x0;
signed int section_x1;

// Collision detection
unsigned char cx1, cx2, cy1, cy2;
unsigned char cxaux, cyaux;
unsigned char at1, at2;
unsigned char *scr_buffer_ptr;
unsigned char scr_v_offset;

// Dum
unsigned char n_pant, base_pant;
unsigned char level;
const signed int *section;
unsigned char game_res;

// Player 
unsigned char prx, pry;
signed int px, py;
signed int pvx, pvy;
unsigned char pgotten, pfacing, psprid;
unsigned char ppossee, pslip, phit;
unsigned char pj, pjb, pctj;
unsigned char ppressingh, pfr, pflickers;
signed char pgtmx, pgtmy;

signed int px_world;
