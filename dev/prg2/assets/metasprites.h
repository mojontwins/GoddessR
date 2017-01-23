// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// Metasprite definitions

const unsigned char * const spr_pl [] = {
	// 0 = FACING_RIGHT

	sspl_00_a,													// IDLE			0
	sspl_01_a, sspl_02_a, sspl_03_a, sspl_04_a,					// WALK			1
	sspl_05_a, sspl_06_a, sspl_07_a, sspl_06_a, 				// SUPERHERO	5
	sspl_08_a, sspl_09_a, sspl_0A_a,							// TURN AROUND	9
	sspl_0B_a, sspl_0C_a, sspl_0D_a,							// CROUCHS		12
	sspl_0C_a, sspl_0B_a, sspl_0A_a,							// BACK UP		15
	sspl_09_a, sspl_08_a, sspl_0E_a,							// WIN POSE		18
	sspl_0F_a,													// AIRBORNE		21

	// 22 = FACING LEFT

	sspl_00_b,													// IDLE			0
	sspl_01_b, sspl_02_b, sspl_03_b, sspl_04_b,					// WALK			1
	sspl_05_b, sspl_06_b, sspl_07_b, sspl_06_b, 				// SUPERHERO	5
	sspl_08_b, sspl_09_b, sspl_0A_b,							// TURN AROUND	9
	sspl_0B_b, sspl_0C_b, sspl_0D_b,							// CROUCHS		12
	sspl_0C_b, sspl_0B_b, sspl_0A_b,							// BACK UP		15
	sspl_09_b, sspl_08_b, sspl_0E_b,							// WIN POSE		18
	sspl_0F_b,													// AIRBORNE		21

	// 44 = TELEPORT DANCE
	sspld_00, sspld_01, sspld_02, sspld_03,
	sspld_04, sspld_05, sspld_06, sspld_07
};

const unsigned char * const spr_en [] = {
	// First, left/right f1 f2 for linear enemies
	ssena_00_a, ssena_01_a, ssena_02_a, ssena_03_a, 
	ssena_03_b, ssena_02_b, ssena_01_b, ssena_00_b, 			// 0: CYCLOPS
	ssena_04_a, ssena_05_a, ssenx_a   , ssena_06_a,
	ssena_06_b, ssenx_b   , ssena_05_b, ssena_04_b, 			// 1: ELEUTERIO
	ssenb_00, ssenb_01, ssenb_02, ssenb_01,
	ssenb_00, ssenb_01, ssenb_02, ssenb_01,						// 2: GRAY BAT
	ssenc_00, ssenc_01, ssenc_00, ssenc_01,
	ssenc_00, ssenc_01, ssenc_00, ssenc_01, 					// 3: PLATFORM

	// PEZON_BASE = 32
	ssenc_02, ssenc_03, ssenc_04, 0, 							// 4: FISH & OCC

	// FANTY_BASE = 36
	ssenb_03, ssenb_04, ssenb_05, ssenb_04,

	// MISC... 40
	ssenc_05													// NO
};

const unsigned char * const spr_it [] = {
	0,
	ssit_00, ssit_01, ssit_02, ssit_03,
	ssit_04, ssit_05, ssit_06, ssit_07
};

const unsigned char spr_empty [] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0x80
};
