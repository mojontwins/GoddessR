// MT NES MK1 ChamanH v0.1
// Copyleft 2016 by The Mojon Twins

// Handy aliases
// Those were used this way in the original GNROM version of Lala to describe
// the game state between rom changes. This of course is not needed anymore.
// I could have changed this for this version but I couldn't be arsed.

// I had to turn these into plain variables so stuff doesn't get hasty.
// Look for them in globals_bss.h

#define COMM_REG 				COMM_POOL [0]
#define COMM_LEVEL 				COMM_POOL [1]
#define COMM_LIVES 				COMM_POOL [2]
#define COMM_INITS 				COMM_POOL [3]
#define COMM_GS 				COMM_POOL [0x0f]
#define COMM_CHECKSUM 			COMM_POOL [0x0e]
#define COMM_DIAMOND_A 			COMM_POOL [0x0a]
#define COMM_DIAMOND_B 			COMM_POOL [0x0b]
#define COMM_DIAMOND_C 			COMM_POOL [0x0c]

// Handy macros

#define UPDATE_LIST_SIZE		32
#define UPDATE 					*gp_ul ++
#define MSB(x)					((x)>>8)
#define LSB(x)					((x)&0xff)
#define SPRITE_ORIGIN			32
#define TILE_ORIGIN 			2
#define SPRITE_ADJUST			-1
#define TOP_ADJUST				4
#define FIX_BITS				4
#define FADE_DELAY 				1

#define SGNI(n)					((n)<0?-1:1)
#define SGNC(a,b,c)				((a)<(b)?-(c):(c))
#define SATURATE_Z(n)			((n)<0?0:(n))
#define SATURATE(v,max)			((v)>=0?((v)>(max)?(max):(v)):((v)<-(max)?-(max):(v)))
#define ABS(n)					((n)<0?-(n):(n))
#define DELTA(a,b)				((a)<(b)?(b)-(a):(a)-(b))
#define CL(x1,y1,x2,y2)			((x1)+4>=(x2)&&(x1)<=(x2)+12&&(y1)+12>=(y2)&&(y1)<=(y2)+12)
#define SUBSTR_SAT(a,b)			((a)>(b)?(a)-(b):0)
#define DISABLE_SFX_NEXT_FRAME	*((unsigned char*)0x01bf)=1;

// Change this if you change where digits are stored in the pattern table

#define DIGIT(n) 				(16+(n))

// Game States

#define GS_GAME_OVER 			0
#define GS_NEXT_LEVEL			1
#define GS_REPEAT_LEVEL			2
#define GS_RESET				3

// Cutscenes

#define NEW_LINE 				1
#define NEW_PAGE				2

// Define it so it has the MAX # of bolts in a level
#define MAX_BOLTS			15

// Player cells

#define PCELL_WALK_BASE			1
#define PCELL_STANDING			0
#define PCELL_ASCENDING			5
#define PCELL_DESCENDING		6
#define PCELL_MAGIC				7
#define PCELL_OFFS				16

#define PFACING_LEFT			8
#define PFACING_RIGHT			0

// Sound channels

#define SC_PLAYER				0
#define SC_ENEMS				1
#define SC_LEVEL				1

// SFX

#define SFX_START				0
#define SFX_JUMP				1			
#define SFX_REFILL				2
#define SFX_ENEMY_HIT			3
#define SFX_EXTRA_1				4
#define SFX_SHOOT				5
#define SFX_FART				6
#define SFX_CHOF				7
#define SFX_BUTT_FALL			8
#define SFX_BUTT_HIT			9
#define SFX_BLOCO				10
#define SFX_PALACE_DISAPPEARS	11
#define SFX_NINTENDONT 			12
#define SFX_GEMS 				13
#define SFX_KEYS				14
#define SFX_GET_ITEM			15
#define SFX_COINS				16
#define SFX_UNLOCKER 			17
#define SFX_SPIKE				18
#define SFX_KILLALL 			19
#define SFX_WAND				20

// Music

#define MUSIC_TITLE				0
#define MUSIC_CUTSCENES_BASE	1
#define MUSIC_CUTSCENE_3B		5
#define MUSIC_GAME_OVER			6
#define MUSIC_ENDING			7

// SFX

#define MUSIC_LEVEL_BASE 		8
#define MUSIC_LEVEL_REPEAT		12
#define MUSIC_FANFARE 			13
#define MUSIC_SILENCE			14

// States

#define EST_NORMAL				0
#define EST_PARP				1

// Screen times in seconds

#define ENDING_SCREEN_TIME		255
#define GAME_OVER_SCREEN_TIME	10
#define LEVEL_SCREEN_TIME		10

// Game States

#define GS_NEXT_LEVEL			1
#define GS_REPEAT_LEVEL			2
#define GS_GAME_OVER 			0

// Handy aliases
