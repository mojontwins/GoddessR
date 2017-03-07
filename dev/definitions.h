// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// General definitions

	#define UPDATE_LIST_SIZE			32
	#define MSB(x)						((x)>>8)
	#define LSB(x)						((x)&0xff)
	#define SPRITE_ADJUST				3
	#define FIX_BITS					4
	#define SCROLL_Y					444

// Handy macros

	#define SGNI(n)						((n)<0?-1:1)
	#define SGNC(a,b,c)					((a)<(b)?-(c):(c))
	#define SATURATE_Z(n)				((n)<0?0:(n))
	#define SATURATE(v,max)				((v)>=0?((v)>(max)?(max):(v)):((v)<-(max)?-(max):(v)))
	#define SATURATE_N(v,min)			(v<min?min:v)
	#define ABS(n)						((n)<0?-(n):(n))
	#define DELTA(a,b)					((a)<(b)?(b)-(a):(a)-(b))
	#define CL(x1,y1,x2,y2)				((x1)+4>=(x2)&&(x1)<=(x2)+12&&(y1)+12>=(y2)&&(y1)<=(y2)+12)
	#define SUBSTR_SAT(a,b)				((a)>(b)?(a)-(b):0)
	#define DISABLE_SFX_NEXT_FRAME		*((unsigned char*)0x01bf)=1;
	#define ADD_SIGN2(a,b,v)			((a)==(b))?(0):(((a)>(b))?(v):(-(v)))
	#define ADD_SIGN(a,v) 				((a)?(((a)>0)?(v):(-(v))):(0))
	#define DIGIT(n) 					(224+(n))
	#define UPDATE						*gp_ul++
	#define SCR_BUFFER_PTR_UPD 			scr_buffer_ptr = scr_buffer + ((n_pant & 1) ? 192 : 0)

// Map properties

	#define MAP_W						20
	#define MAP_H 						4
	#define MAX_PANTS					MAP_W*MAP_H
	#define LEVEL_INI					3
	#define SCR_INI						11
	#define HUB_LEVEL					1
	#define HUB_SCR 					9
	#define HUB_X						0xA
	#define HUB_Y						0x5

// Player movement values

	#define PLAYER_VY_FALLING_MAX		64
	#define PLAYER_G					4
	#define PLAYER_G_JUMPING			1
	#define PLAYER_VY_JUMP_INITIAL		52 
	#define PLAYER_VY_JUMP_RELEASE		24
	#define PLAYER_VY_JUMP_FLICK		64	
	#define PLAYER_VY_JUMP_BUTT			96
	#define PLAYER_VY_JUMP_A_STEPS  	16
	#define PLAYER_VY_SINK				2
	#define PLAYER_AY_JUMP 				8	
	#define PLAYER_VX_MAX				32	
	#define PLAYER_VX_MAX_PODEWWWR		48
	#define PLAYER_AX					3	
	#define PLAYER_RX					4
	#define PLAYER_AX_SLIP				1
	#define PLAYER_RX_SLIP				0
	#define PLAYER_VX_MIN 				(PLAYER_AX << 2)
	#define PLAYER_V_REBOUND			56

// Animation cells

	#define PFACING_RIGHT				0
	#define PFACING_LEFT				27

	#define PCELL_STANDING 				0
	#define PCELL_WALK_BASE				1
	#define PCELL_SUPERHERO				5
	#define PCELL_USE_ANIM_BASE			8  // Minus one
	#define PCELL_WIN_POSE				25
	#define PCELL_AIRBORNE				26
	#define PCELL_TELEPORT				54

	#define ENCELL_NO					40

// Game states

	#define PLAYER_EXIT_TOP				1
	#define PLAYER_EXIT_BOTTOM 			2
	#define PLAYER_EXIT_LEFT			3
	#define PLAYER_EXIT_RIGHT			4
	#define PLAYER_KILLED				5
	#define PLAYER_TELEPORT 			6
	#define PLAYER_CUTSCENE				7
	#define PLAYER_RESTORE				8
	#define PLAYER_WINS					9
	#define PLAYER_GAME_OVER 			10
	#define PLAYER_MAP 					11
	#define PLAYER_DEBUG				0xff

// Scroll states

	#define SCROLL_STATE_NONE			0
	#define SCROLL_STATE_FREE			1
	#define SCROLL_STATE_CHUNK_0		2
	#define SCROLL_STATE_CHUNK_7		4

// Defines for enemies

	#define PEZON_WAIT					50
	#define PEZONS_BASE_SPRID			32

	#define FANTY_BASE_SPRID			36
	#define FANTY_ST_IDLE				0
	#define FANTY_ST_PURSUING			1
	#define FANTY_ST_RETREATING			2
	#define FANTY_SIGHT_DISTANCE		96

// Defines for chac chacs

	#define BG_OBJS_MAX 				5

// Defines for readability

	#define PEZON_TIMER 				en_x2
	#define PEZON_MAX_TIME 				en_y2
	#define PEZON_INCS_IDX				en_my

// Music

	#define MUSIC_TITLE					0
	#define MUSIC_INGAME_BASE 			1
	#define MUSIC_CLEAR					5
	#define MUSIC_GAME_OVER 			6

// SFX

	#define SC_PLAYER					0
	#define SC_LEVEL 					1

	#define SFX_DUMMY					0
	#define SFX_FLASH 					1
	#define SFX_USE 					2
	#define SFX_GET 					3
	
	#define SFX_ON 						5
	#define SFX_OFF 					6
	#define SFX_JUMP 					7
	#define SFX_RECHARGE				8
	#define SFX_SHOW_MAP				9
	#define SFX_KILL 					10
	#define SFX_HEART 					11
	#define SFX_PAUSE 					12
	#define SFX_NO 						13
	#define SFX_LAVA 					14
	#define SFX_FISH 					15
	#define SFX_FLY 					16

// Cutscenes

	#define NEW_LINE 					1
	#define NEW_PAGE					2
