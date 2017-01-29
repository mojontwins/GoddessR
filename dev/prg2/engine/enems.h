// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Enems routines

void enems_load (void) {
	gpit = (rdpant & 1) ? 3 : 0; gpjt = 3 + gpit;
	rda = rdpant + base_pant;
	enidx = (rda << 1) + rda;

	for (; gpit < gpjt; gpit ++) {
		en_p [gpit] = rdpant;
		
		// cc65 could do better, so:
		
		/*
		rda = c_enems_t [enidx];
		rdb = c_enems_yx1 [enidx];
		rdc = c_enems_yx2 [enidx];
		rdd = c_enems_mn [enidx];
		*/

		__asm__ ("ldy %v", enidx);
		__asm__ ("lda (%v), y", c_enems_t);
		__asm__ ("sta %v", rda);
		__asm__ ("lda (%v), y", c_enems_yx1);
		__asm__ ("sta %v", rdb);
		__asm__ ("lda (%v), y", c_enems_yx2);
		__asm__ ("sta %v", rdc);
		__asm__ ("lda (%v), y", c_enems_mn);
		__asm__ ("sta %v", rdd);

		enidx ++; 
	
		en_t [gpit] = rda; rdt = rda & 0xf0;
		en_s [gpit] = (rda & 0xf) << 3;
		
		en_x [gpit] = en_x1 [gpit] = rdb << 4;
		en_y [gpit] = en_y1 [gpit] = rdb & 0xf0;

		en_x2 [gpit] = rdc << 4;
		en_y2 [gpit] = rdc & 0xf0;

		en_state [gpit] = 0;

		switch (rdt) {
			case 0x10:
			case 0x20:
				// Linear
				if (rdd == 1) en_state [gpit] = 1; else rdd >>= 1;
				en_mx [gpit] = ADD_SIGN2 (en_x2 [gpit], en_x1 [gpit], rdd);
				en_my [gpit] = ADD_SIGN2 (en_y2 [gpit], en_y1 [gpit], rdd);
				break;

			case 0x30:
				// Homing fanties
				en_mx [gpit] = en_my [gpit] = 0;
				break;

			case 0xC0:
				// Pezons
				PEZON_TIMER [gpit] = PEZON_MAX_TIME [gpit] = PEZON_WAIT + (rdd << 3); 
				break;
		}
	}

	en_just_loaded = 1;
}

void enems_do (void) {
	// Out of order.
	gpit = en_iter; en_iter ++; if (en_iter == 6) en_iter = 0;
	gpjt = 6; while (gpjt --) {
		gpit += 5; if (gpit > 5) gpit -= 6;

		rdt = en_t [gpit] & 0xf0;
		if (!rdt) continue;

		en_scr_buffer_ptr = scr_buffer + (gpit < 3 ? 0 : 192);
		sprid = 0xff; // this may be removed later

		switch (rdt) {
			case 0x10:
			case 0x20:
				// Linear
				#include "prg2/engine/enem_mods/enem_linear.h"
				break;

			case 0x30:
				// Fanty
				#include "prg2/engine/enem_mods/enem_fanty_precalc.h"
				break;

			case 0xC0:
				// Pezon
				#include "prg2/engine/enem_mods/enem_pezon_precalc.h"
				break;
		}

		// Render

		if (sprid == 0xff) continue;
		
		if ((cam_pos_pant && gpit >= 3) || (!cam_pos_pant && gpit < 3)) {
			if (sprx >= cam_pos_mod) rdx = sprx - cam_pos_mod; 
			else continue; 
		} else {
			if (sprx + 16 < cam_pos_mod) rdx = 256 - cam_pos_mod + sprx;
			else continue; 
		}

		// Occlude pezons
		if (rdt == 0xC0) {
			// Occluding sprite
			oam_index = oam_meta_spr (
				rdx, en_y1 [gpit] + SPRITE_ADJUST + 1,
				oam_index,
				spr_en [PEZONS_BASE_SPRID + 2]
			);
		}

		oam_index = oam_meta_spr (
			rdx, spry + SPRITE_ADJUST,
			oam_index,
			spr_en [sprid]
		);

		// Collision

		if (n_pant != en_p [gpit]) continue;
		if (ppodewwwr) continue;

		// With platforms
		if (rdt == 0x20) {
			if (prx + 9 >= sprx && prx <= sprx + 17 && !(pj && pvy <= 0)) {
				// Horizontal
				if (en_mx [gpit]) {
					if (pry + 18 >= spry && pry + 12 <= spry) {
						pgotten = 1;
						pgtmx = endx << FIX_BITS;
						prx += endx; px = prx << FIX_BITS;
						pry = spry - 16; py = pry << FIX_BITS;
						pvy = 0;
					}
				}

				// Vertical
				if (
					(en_my [gpit] < 0 && pry + 17 >= spry && pry + 12 <= spry) ||
					(en_my [gpit] > 0 && pry + 16 + en_my [gpit] >= spry && pry + 12 <= spry)
				) {
					pgotten = 1;
					pgtmy = en_my [gpit] << (FIX_BITS - en_state [gpit]);
					pry = spry - 16; py = pry << FIX_BITS;
					pvy = 0;
				}
			}
			continue;
		}

		if (pflickers) continue;

		// With plain enemies
		if (CL (prx, pry, sprx, spry)) {
			psignal = PLAYER_KILLED;
			sfx_play (SFX_KILL, SC_PLAYER);
		}
	}
}