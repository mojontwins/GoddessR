// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Zero page globals

// General
unsigned char rda, rdb, rdc, rdd, rdct, rdt;
unsigned char rdx, rdy, rdpant, ccit;
signed char rds;

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
unsigned int col_idx_latest;
const unsigned char *col_ptr;
const unsigned char *map_ptr;
unsigned char state_ctr;
unsigned int col_v_offset;

signed int cam_pos;
unsigned char cam_pos_mod, cam_pos_pant;

// Collision detection
unsigned char cx1, cx2, cy1, cy2;
unsigned char cxaux, cyaux;
unsigned char at1, at2;
unsigned char *scr_buffer_ptr;
unsigned char *en_scr_buffer_ptr;
unsigned char scr_v_offset;

// Dum
unsigned char n_pant;

// Player 
unsigned char prx, pry;
signed int px, py;
signed int pvx, pvy;
unsigned char pgotten, pfacing, psprid;
unsigned char ppossee, pslip, psignal;
unsigned char pj, pjb, pctj;
unsigned char ppressingh, pfr, pflickers, ppodewwwr;
signed char pgtmx, pgtmy;

signed int px_world;

// Enems
unsigned char cam_pant, cam_pant_old;
const unsigned char *c_enems_t;
const unsigned char *c_enems_yx1;
const unsigned char *c_enems_yx2;
const unsigned char *c_enems_mn;
unsigned char enidx, en_just_loaded;
unsigned char en_iter;
unsigned char en_t [6], en_x1 [6], en_y1 [6], en_x2 [6], en_y2 [6];
unsigned char en_x [6], en_y [6], en_state [6], en_s [6], en_p [6];
signed char en_mx [6], en_my [6];
unsigned char sprx, spry, sprid;
unsigned char en_cx, en_cy;

// Hotspots
const unsigned char *c_hotspots_yx;
const unsigned char *c_hotspots_t;

