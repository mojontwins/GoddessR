// Precalculated fanty
// Copyleft 2017 by The Mojon Twins

// Needs FANTY_INCS_MAX and fanty_incs
// Needs fanty_retreat_incs

	// States are:
	// FANTY_ST_IDLE 0 - stays idle. 
	// FANTY_ST_PURSUING 1 - pursues player.
	// FANTY_ST_RETREATING 2 - retreats to original position.

	// IDLE -> PURSUING if player_in_range
	// PURSUING -> RETREATING if !player_in_range
	// RETREATING -> IDLE if x = x1 && y = y1

	rdd = (prx < en_x [gpit]) ? en_x [gpit] - prx : prx - en_x [gpit];
	rdb = (
		(en_p [gpit] == n_pant) && 
		rdd < FANTY_SIGHT_DISTANCE
	);
	
	switch (en_state [gpit]) {
		case FANTY_ST_IDLE:
			if (rdb) {
				en_state [gpit] = FANTY_ST_PURSUING;
				en_mx [gpit] = 0;
				en_my [gpit] = 0;
			}
			break;

		case FANTY_ST_PURSUING:
			if (!rdb) {
				en_state [gpit] = FANTY_ST_RETREATING;
				en_mx [gpit] = 0;
				en_my [gpit] = 0;
			} else {
				// Accelerate / decelerate:
				if (prx > en_x [gpit]) {
					en_mx [gpit] ++; 
					if (en_mx [gpit] >= FANTY_INCS_MAX - 1) en_mx [gpit] = FANTY_INCS_MAX - 1;
				} else if (prx < en_x [gpit]) {
					en_mx [gpit] --;
					if (en_mx [gpit] <= -(FANTY_INCS_MAX - 1)) en_mx [gpit] = - (FANTY_INCS_MAX - 1);
				}

				if (rand8 () & 0xf) en_x [gpit] += ADD_SIGN (
					en_mx [gpit],
					fanty_incs [ABS (en_mx [gpit])]
				);
				//if (en_x [gpit] < 8 || en_x [gpit] > 232) en_mx [gpit] = -en_mx [gpit];
				if ((en_x [gpit] < 8 && en_mx [gpit] < 0) ||
					(en_x [gpit] > 232 && en_mx [gpit] > 0)) en_mx [gpit] = -en_mx [gpit]; 

				if (pry > en_y [gpit]) {
					en_my [gpit] ++; 
					if (en_my [gpit] >= FANTY_INCS_MAX - 1) en_my [gpit] = FANTY_INCS_MAX - 1;
				} else if (pry < en_y [gpit]) {
					en_my [gpit] --;
					if (en_my [gpit] <= -(FANTY_INCS_MAX - 1)) en_my [gpit] = - (FANTY_INCS_MAX - 1);
				}

				if (rand8 () & 0xf) en_y [gpit] += ADD_SIGN (
					en_my [gpit],
					fanty_incs [ABS (en_my [gpit])]
				);
				//if (en_y [gpit] < 8 || en_y [gpit] > 204) en_my [gpit] = -en_my [gpit];
				if ((en_y [gpit] < 8 && en_my [gpit] < 0) ||
					(en_y [gpit] > 232 && en_my [gpit] > 0)) en_my [gpit] = -en_my [gpit];
			}
			break;

		case FANTY_ST_RETREATING:
			if (rdb) {
				en_state [gpit] = FANTY_ST_PURSUING;
				en_mx [gpit] = 0;
				en_my [gpit] = 0;
			} else {
				en_mx [gpit] = (en_mx [gpit] + 1) & 3;
				rds = fanty_retreat_incs [en_mx [gpit]];
				if (en_x [gpit] != en_x1 [gpit]) en_x [gpit] += (en_x [gpit] > en_x1 [gpit] ? -rds : rds);
				if (en_y [gpit] != en_y1 [gpit]) en_y [gpit] += (en_y [gpit] > en_y1 [gpit] ? -rds : rds);
				if (en_x [gpit] == en_x1 [gpit] && en_y [gpit] == en_y1 [gpit])
					en_state [gpit] = FANTY_ST_IDLE;
			}
			break;
	}

	sprx = en_x [gpit];
	spry = en_y [gpit];
	sprid = FANTY_BASE_SPRID + (
		en_state [gpit] ?
		((en_x [gpit] >> 2) & 3) :
		((frame_counter >> 3) & 3)
	);
