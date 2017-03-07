// Precalculated pezon
// Copyleft 2017 by The Mojon Twins

// Needs PEZON_INCS_MAX, PEZON_INCS_FIRST_FALL and pezon_incs

	if (en_state [gpit]) {
		en_y [gpit] += pezon_incs [PEZON_INCS_IDX [gpit]];

		sprx = en_x1 [gpit];
		spry = en_y [gpit];
		sprid = PEZONS_BASE_SPRID + (PEZON_INCS_IDX [gpit] > PEZON_INCS_FIRST_FALL);
		
		if (PEZON_INCS_IDX [gpit] < PEZON_INCS_MAX) {
			PEZON_INCS_IDX [gpit] ++; 
		} else {
			en_state [gpit] = 0;
			PEZON_TIMER [gpit] = PEZON_MAX_TIME [gpit];
		}
	} else {
		sprid = 0xff;
		if (PEZON_TIMER [gpit]) PEZON_TIMER [gpit] --; else {
			PEZON_INCS_IDX [gpit] = 0;
			en_state [gpit] = 1;
			en_y [gpit] = en_y1 [gpit];
			// A play sound trigger used to be here, but I've moved it
			// until we know if we should be displaying this enemy.
			// If enemy is not showing, then don't play the sound!
			playfish = 1;	
		}
	}
	