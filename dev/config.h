// NES MK1 v0.7
// Copyleft Mojon Twins 2013, 2015, 2016

#define MAP_W 					6
#define MAP_H					5

#define PLAYER_LIFE				5
#define PLAYER_REFILL			1

#define HOTSPOTS_WONT_CHANGE
#define HOTSPOT_TYPE_OBJECT		1
#define HOTSPOT_TYPE_KEYS		2
#define HOTSPOT_TYPE_REFILL		3
#define HOTSPOT_TYPE_UNLOCKER	4
#define HOTSPOT_TYPE_PLATFORMS	5
#define HOTSPOT_TYPE_PLATFORMS_OFF 6
#define HOTSPOT_TYPE_POWERON	7
#define HOTSPOT_TYPE_STAR		8
#define HOTSPOT_TYPE_WAND		9
#define HOTSPOT_TYPE_GEM		10
#define HOTSPOT_TYPE_COIN		11

#define BOUNDING_BOX_8_BOTTOM
#define SMALL_COLLISION

#define SPRITE_BADDIE_DYING 	spr_en_0E_a
#define DIE_AND_RESPAWN
#define PLAYER_FLICKERS

#define ENABLE_FANTY
#define ENEMY_TYPE_FANTY		16
#define FANTY_IDLER				150
#define FANTY_BASE_SPRID		32
#define FANTY_A 				1
#define FANTY_MAXV 				8
#define FANTY_COLLIDES

#define POWER_ON_TIMER			10

#define HOUR_TICKS				75

#define PLAYER_HAS_JUMP
#define NO_HORIZONTAL_EVIL_TILE

#define LIFE_X					6
#define LIFE_Y					2
#define OBJECTS_X				0x1d
#define OBJECTS_Y				2
#define KEYS_X					0x10
#define KEYS_Y					2
#define KILLED_X				16
#define KILLED_Y				2
#define AMMO_X					8
#define AMMO_Y					29

#define LINE_OF_TEXT			3
#define LINE_OF_TEXT_X			1
#define LINE_OF_TEXT_ATTR		71

#define PLAYER_VY_FALLING_MAX	64
#define PLAYER_G				4
#define PLAYER_VY_MIN 			16
#define PLAYER_VY_JUMP_INITIAL	16
#define PLAYER_VY_JUMP_MAX		64	
#define PLAYER_VY_JUMP_BUTT		96
#define PLAYER_VY_JUMP_A_STEPS  16
#define PLAYER_VY_MIN_FLICK		12
#define PLAYER_VY_SINK			2
#define PLAYER_AY_JUMP 			8	
#define PLAYER_VX_MAX			32	
#define PLAYER_AX				4	
#define PLAYER_RX				4
#define PLAYER_AX_SLIP			1
#define PLAYER_RX_SLIP			1
#define PLAYER_VX_MIN (PLAYER_AX << 2)
#define PLAYER_V_REBOUND		56
