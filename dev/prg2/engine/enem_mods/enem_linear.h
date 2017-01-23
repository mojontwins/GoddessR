// Linear enemies version all tomorow's parties
// Copyleft 2017 by The Mojon Twins

	if (!en_state [gpit] || half_life) {

		// Can be stopped by a wall
		// as they are always aligned, 
		// calculations are fairly easy.

		// Horizontal

		rdy = (en_y [gpit] < 32 ? 0 : en_y [gpit] - 32) & 0xf0; // (y >> 4) << 4
		rdx = en_x [gpit] >> 4;

		if (en_mx [gpit]) {
			en_cx = en_x [gpit];
			en_x [gpit] += en_mx [gpit];

			if (en_x [gpit] == en_x1 [gpit] ||
				en_x [gpit] == en_x2 [gpit]
			) {
				en_mx [gpit] = -en_mx [gpit];
			} else if (
				(en_x [gpit] & 0xf) == 0 && 
				8 == *(en_scr_buffer_ptr + rdy + rdx + (en_mx [gpit] > 0))
			) {
				en_mx [gpit] = -en_mx [gpit];
				en_x [gpit] = en_cx;
			} 
		}

		if (en_my [gpit]) {
			rdx = en_x [gpit] >> 4;
			en_cy = en_y [gpit];
			en_y [gpit] += en_my [gpit];

			if (en_y [gpit] == en_y1 [gpit] ||
				en_y [gpit] == en_y2 [gpit]
			) {
				en_my [gpit] = -en_my [gpit];
			} else if (
				(en_y [gpit] & 0xf) == 0 && 
				8 == *(en_scr_buffer_ptr + rdy + rdx + (en_my [gpit] > 0 ? 16 : 0))
			) {
				en_my [gpit] = -en_my [gpit];
				en_y [gpit] = en_cy;
			}
		}
	}

	sprx = en_x [gpit]; spry = en_y [gpit];
	sprid = en_s [gpit] + (en_mx [gpit] == 0 ?
		((en_my [gpit] < 0 ? 4 : 0) + ((en_y [gpit] >> 2) & 3)) :
		((en_mx [gpit] < 0 ? 4 : 0) + ((en_x [gpit] >> 2) & 3)));
	