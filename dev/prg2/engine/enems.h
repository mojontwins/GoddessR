// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Enems routines

void enems_load (void) {
	gpit = (rda & 1) ? 3 : 0; gpjt = 3 + gpit;
	rda += base_pant;
	enidx = (rda << 1) + rda;

	for (; gpit < gpjt; gpit ++) {
		
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

			case 0x50:
				// Chac Chac
				CHAC_CHAC_TIMER [gpit] = CHAC_CHAC_MAX_TIME [gpit] = rdd << 4;
				en_x [gpit] >>= 4; en_y [gpit] >>= 4;
				break;

			case 0xC0:
				// Pezons
				PEZON_TIMER [gpit] = PEZON_MAX_TIME [gpit] = PEZON_WAIT + (rdd << 3); 
				break;
		}
	}

	en_just_loaded = 1;
}

void enems_preload (void) {
	// loads 3 enems to the right spot in the arrays
	// rda == n_pant

	cam_pant = MSB (cam_pos);

	if (cam_pant == cam_pant_old) return;

	if (cam_pant > cam_pant_old) rda = cam_pant + 1;
	else rda = cam_pant;	

	cam_pant_old = cam_pant;

	enems_load ();
}

void enems_do (void) {
	// Mux a bit the load. If we created enemies, don't process them
	// this frame.
	if (en_just_loaded) {
		en_just_loaded = 0; return;
	}

	// Now, out of order.
	gpit = en_iter; en_iter ++; if (en_iter == 6) en_iter = 0;
	gpjt = 6; while (gpjt = 0) {
		gpit += 5; if (gpit > 5) gpit -= 6;


	}
}