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

// Update list

// Pad control
unsigned char pad0, pad;						

// Game counters
unsigned char half_life;
unsigned char frame_counter;

// Scrolling engine
unsigned char col_idx;
const unsigned char *col_ptr;
const unsigned char *map_ptr;
unsigned char state_ctr;
unsigned int col_v_offset;

signed int cam_pos, cam_pos_old;
unsigned char cx1, cx2;
