// Precalculated pezon
// Copyleft 2017 by The Mojon Twins

// Needs PEZON_INCS_MAX and pezon_incs

	// Occluding sprite
	oam_index = oam_meta_spr (
		en_x1 [gpit], en_y1 [gpit],
		oam_index,
		spr_enems [PEZONS_BASE_SPRID + 2]
	);

	if (en_state [gpit]) {
		en_y [gpit] += pezon_incs [PEZON_INCS_IDX [gpit]];
		oam_index = oam_meta_spr (
			en_x1 [gpit], en_y [gpit],
			oam_index,
			spr_enems [PEZONS_BASE_SPRID + (PEZON_INCS_IDX [gpit] > PEZON_INCS_FIRST_FALL)];
		);
		if (PEZON_INCS_IDX [gpit] < PEZON_INCS_MAX) {
			PEZON_INCS_IDX [gpit] ++; 
		} else {
			en_state [gpit] = 0;
			PEZON_TIMER [gpit] = PEZON_MAX_TIME [gpit];
		}
	} else {
		if (PEZON_TIMER [gpit]) PEZON_TIMER [gpit] --; else {
			PEZON_INCS_IDX [gpit] = 0;
			en_state [gpit] = 1;
			en_y [gpit] = en_y1 [gpit];
		}
	}
	