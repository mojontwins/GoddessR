// Goddess Engine v0.1
// Copyleft 2017 The Mojon Twins

// General definitions

	#define UPDATE_LIST_SIZE			32
	#define MSB(x)						((x)>>8)
	#define LSB(x)						((x)&0xff)
	#define SPRITE_ADJUST				-1
	#define FIX_BITS					4

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
	#define DIGIT(n) 					(1+(n))
	#define UPDATE						*gp_ul++
	#define SCR_BUFFER_PTR_UPD 			scr_buffer_ptr = scr_buffer + ((n_pant & 1) ? 192 : 0)

// Player movement values

	#define PLAYER_VY_FALLING_MAX		64
	#define PLAYER_G					4
	#define PLAYER_VY_JUMP_INITIAL		16
	#define PLAYER_VY_JUMP_MAX			64	
	#define PLAYER_VY_JUMP_BUTT			96
	#define PLAYER_VY_JUMP_A_STEPS  	16
	#define PLAYER_VY_SINK				2
	#define PLAYER_AY_JUMP 				8	
	#define PLAYER_VX_MAX				32	
	#define PLAYER_AX					4	
	#define PLAYER_RX					4
	#define PLAYER_AX_SLIP				1
	#define PLAYER_RX_SLIP				0
	#define PLAYER_VX_MIN 				(PLAYER_AX << 2)
	#define PLAYER_V_REBOUND			56

// Animation cells

	#define PFACING_RIGHT				0
	#define PFACING_LEFT				22

	#define PCELL_STANDING 				0
	#define PCELL_WALK_BASE				1
	#define PCELL_SUPERHERO				5
	#define PCELL_TURN_AROUND			9
	#define PCELL_CROUCHS				12
	#define PCELL_BACK_UP				15
	#define PCELL_WIN_POSE				18
	#define PCELL_AIRBORNE				21

// Game states

	#define PLAYER_EXIT_TOP				1
	#define PLAYER_EXIT_BOTTOM 			2
	#define PLAYER_EXIT_LEFT			3
	#define PLAYER_EXIT_RIGHT			4
