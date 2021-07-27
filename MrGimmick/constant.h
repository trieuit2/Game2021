#pragma once

// BLACKBOSS LEVEL 1

#define BLACKBOSS_GRAVITY	0.001f

#define BLACKBOSS_SS_DIE			0
#define BLACKBOSS_SS_IDLE		1
#define BLACKBOSS_SS_SHOOTING	2
#define BLACKBOSS_SS_STUN		3
#define BLACKBOSS_SS_BLINK		4
#define BLACKBOSS_SS_WALK		5

#define BLACKBOSS_BBOX_WIDTH				32
#define BLACKBOSS_BBOX_HEIGHT				31
#define BLACKBOSS_EARS_WIDTH				20
#define BLACKBOSS_EARS_HEIGHT				13
#define BLACKBOSS_SHOOTING_EARS_HEIGHT		16
#define BLACKBOSS_STUN_EARS_HEIGHT			8

#define BLACKBOSS_ANIMATION_IDLE			0
#define BLACKBOSS_EAR_ANI			1
#define BLACKBOSS_ANIMATION_SHOOTING		2
#define BLACKBOSS_ANIMATION_STUN			3
#define BLACKBOSS_ANIMATION_BLINK			4
#define BLACKBOSS_ANIMATION_WALK			5

#define BLACKBOSS_DEFLECT_SPEED					0.09f
#define BLACKBOSS_BLACKENEMY_ACCELERATION		0.0002f
#define BLACKBOSS_WALK_SPEED					0.02f

#define BLACKBOSS_STOP_POSITION_X				1105

#define BLACKBOSS_IDLE_TIME			2000
#define BLACKBOSS_SHOOT_TIME		1500
#define BLACKBOSS_BLINK_TIME		450

#define BLACKBOSS_LIFE_COUNT		3

// BLACK ENEMY

#define BLACKENEMY_SS_DIE	0
#define BLACKENEMY_SS_WALK	1
#define BLACKENEMY_SS_TRANSFORM	2
#define BLACKENEMY_SS_FLY		3
#define BLACKENEMY_SS_BULLET		4

#define BLACKENEMY_WIDTH		16
#define BLACKENEMY_HEIGHT		16

#define BLACKENEMY_ACCELERATION		0.0002f  //0.0002f
#define BLACKENEMY_WALK_SPEED		0.075f	//0.075f
#define BLACKENEMY_GRAVITY			0.0008f //0.001f giam trong luc xuong 1 chut de khi roi khong bi xuyen qua gach
#define BLACKENEMY_JUMP_SPEED		0.23f
#define BLACK_ENEMY_BULLET_SPEED	0.15f
#define BLACKENEMY_DEFLECT_SPEED_X		0.075f	
#define BLACKENEMY_DEFLECT_SPEED_Y		0.12f	

#define BLACKENEMY_FLY_ACCELERATION	0.0004f //0.0004f
#define BLACKENEMY_FLY_SPEED		0.165f  //0.165f
#define BLACKENEMY_FLY_SPEED_Y		0.05f

#define TURN_COUNT_TO_TRANSFORM		5 //5
#define JUMP_COUNT_TO_TRANSFORM		10 // neu can 1 lan nhay thi de = 2, vi nhay 1 lan cong 2

#define PLAYER_MAX_RANGE_WALK			48 // 60 : khoang cach 2 ben so voi gimmick de quay dau 48 la chuan
#define PLAYER_MAX_RANGE_FLY			10 // khoang cach 2 ben so voi gimmick de quay dau

#define BLACKENEMY_TRANSFORM_TIME		1500

#define BLACKENEMY_ANISET_ID				130001

#define BLACKENEMY_ANIMATION_WALK_RIGHT				0
#define BLACKENEMY_ANIMATION_WALK_LEFT				1
#define BLACKENEMY_ANIMATION_FLY_RIGHT				2
#define BLACKENEMY_ANIMATION_FLY_LEFT					3
#define BLACKENEMY_ANIMATION_FLY_ONGROUND_RIGHT		4
#define BLACKENEMY_ANIMATION_FLY_ONGROUND_LEFT		5
#define BLACKENEMY_ANIMATION_DIE_LEFT					6
#define BLACKENEMY_ANIMATION_DIE_RIGHT				7

// BLUE FIRE

#define BLUEFIRE_ANIMATION_BURN		0

#define BLUEFIRE_BBOX_WIDTH		16
#define BLUEFIRE_BBOX_HEIGHT	16

// BOOM 

#define	BOOM_BBOX_WIDTH		14
#define	BOOM_BBOX_HEIGHT	18

#define	BOOM_BBOX_EXPLODE_WIDTH		16
#define	BOOM_BBOX_EXPLODE_HEIGHT	16


#define	BOOM_SS_ALIVE		100
#define	BOOM_SS_DIE			200
#define	BOOM_SS_FALLING		300
#define	BOOM_SS_EXPLODE		400

#define BOOM_ANIMATION_ALIVE		0
#define BOOM_ANIMATION_DEAD		1
#define	BOOM_ANIMATION_EXPLODE	2

#define	BOOM_GRAVITY		0.15f

#define	BOOM_EXPLODE_TIME	300

// CHAIN

#define CHAIN_ANIMATION_TOP_RIGHT	0
#define CHAIN_ANIMATION_BOT_RIGHT	1
#define CHAIN_ANIMATION_BOT_LEFT	2
#define CHAIN_ANIMATION_TOP_LEFT	3
#define CHAIN_ANIMATION_DOWN		4
#define CHAIN_ANIMATION_UP		5

#define CHAIN_BBOX_WIDTH	16
#define CHAIN_BBOX_HEIGHT	16

// COGWHEEL

#define COGWHEEL_ANIMATION_TOP_RIGHT	0
#define COGWHEEL_ANIMATION_BOT_RIGHT	1
#define COGWHEEL_ANIMATION_BOT_LEFT	2
#define COGWHEEL_ANIMATION_TOP_LEFT	3

#define COGWHEEL_BBOX_WIDTH	16
#define COGWHEEL_BBOX_HEIGHT	16

// SMALL COGWHEEL

#define COGWHEELSMALL_ANIMATION_SPIN	0

#define COGWHEELSMALL_BBOX_WIDTH	16
#define COGWHEELSMALL_BBOX_HEIGHT	16

// Conveyor

#define CONVEYOR_ANIMATION_RIGHT		0
#define CONVEYOR_ANIMATION_LEFT		1

#define CONVEYOR_BBOX_WIDTH		16
#define CONVEYOR_BBOX_HEIGHT	16

#define	RIGHT_CONVEYOR			1
#define	LEFT_CONVEYOR			-1

// Door 
#define	DOOR_BBOX_WIDTH		48
#define	DOOR_BBOX_HEIGHT	16

#define DOOR_SS_CLOSE	0
#define	DOOR_SS_OPEN		1
#define	DOOR_SS_STOP		2

#define	DOOR_ANIMATION_CLOSE		0
#define	DOOR_ANIMATION_OPEN		1
#define	DOOR_ANIMATION_STOP		2

#define	DOOR_LIMIT_TIME		100

////////////////////////////////////////////
///////////////////////////////////////////
//////////// GIMMICK //////////////////////
#define GIMMICK_WALKING_SPEED		0.1f
#define GIMMICK_ACCELERATION		0.0002f
#define GIMMICK_WALKING_FRICTION	0.00025f
#define GIMMICK_JUMP_SPEED_Y_MIN	0.15f
#define GIMMICK_JUMP_SPEED_Y_MAX	0.35f	//0.25f
#define GIMMICK_JUMP_ACCELERATION	0.001f	//0.001f
#define GIMMICK_GRAVITY				0.001f
#define GIMMICK_DEFLECT_SPEED_X		0.1f

#define GIMMICK_SS_IDLE			0
#define GIMMICK_SS_WALKING_RIGHT	100
#define GIMMICK_SS_WALKING_LEFT	200
#define GIMMICK_SS_JUMP			300
#define GIMMICK_SS_STUN			400
#define GIMMICK_SS_DIE			500

#define GIMMICK_ANIMATION_IDLE_RIGHT		0
#define GIMMICK_ANIMATION_IDLE_LEFT		1
#define GIMMICK_ANIMATION_WALKING_RIGHT	2
#define GIMMICK_ANIMATION_WALKING_LEFT	3
#define GIMMICK_ANIMATION_JUMP_RIGHT		4
#define GIMMICK_ANIMATION_JUMP_LEFT		5
#define GIMMICK_ANIMATION_STUN_RIGHT		6
#define GIMMICK_ANIMATION_STUN_LEFT		7
#define GIMMICK_ANIMATION_DIE				8

#define GIMMICK_BBOX_WIDTH			16
#define GIMMICK_BBOX_HEIGHT			16

#define GIMMICK_UNTOUCHABLE_TIME	2000
#define GIMMICK_STUNNING_TIME		500

///////////////////////
// 
// 
//////////////////////////
///////////////////////////

// GIMMICK EFFECT : 

#define GIMMICKDIEEFFECT_ANIMATION_SET		140001

#define GIMMICKDIEEFFECT_SPEED			0.075f
#define GIMMICKDIEEFFECT_SPEED_225		0.924f
#define GIMMICKDIEEFFECT_SPEED_450		0.707f
#define GIMMICKDIEEFFECT_SPEED_675		0.383f

#define GIMMICKDIEEFFECT_ANIMATION_ACTIVE		0

#define GIMMICKDIEEFFECT_BBOX_WIDTH		16
#define GIMMICKDIEEFFECT_BBOX_HEIGHT	16

//////////////////////////

// HUD ///
#define HUD_HEIGHT	32
#define HUD_WIDTH	256
#define HUD_ZONE_HEIGHT	32
 // TIME TO CHANGE POINT
#define HUB_TIME_DP	5000

//// MEDICINE 

#define	MEDICINE_ORANGE_BBOX_WIDTH	14
#define	MEDICINE_ORANGE_BBOX_HEIGHT	16

#define MEDICINE_PINK_BBOX_WIDTH	14
#define	MEDICINE_PINK_BBOX_HEIGHT	14	

#define	MEDICINE_TYPE_3_4_BBOX_WIDTH	14
#define	MEDICINE_TYPE_3_4_BBOX_HEIGHT	15

#define MEDICINE_ANISET_ID			170001

#define	MEDICINE_ANIMATION_ORANGE			0
#define	MEDICINE_ANIMATION_PINK			1
#define	MEDICINE_ANIMATION_TYPE_3			2
#define	MEDICINE_ANIMATION_TYPE_4			3

#define	MEDICINE_SS_APPEAR		100
#define	MEDICINE_SS_DISAPPEAR	200

#define	MEDICINE_GRAVITY			0.1f

/// START /// 

#define	STAR_GRAVITY			0.001f
#define STAR_VX					0.15f
#define STAR_WALKING_FRICTION	0.0003f

#define	STAR_BBOX_WIDTH			16
#define	STAR_BBOX_HEIGHT		16

#define	STAR_SS_HIDE				100
#define	STAR_SS_PENDING			200
#define	STAR_SS_CREATED			300
#define	STAR_SS_READY			400
#define	STAR_SS_WALKING_RIGHT	500
#define	STAR_SS_WALKING_LEFT		600
#define	STAR_SS_EXPLOSIVE		700

#define STAR_ANIMATION_SMALL			0
#define STAR_ANIMATION_CREATED		1
#define STAR_ANIMATION_MAIN			2
#define STAR_ANIMATION_EXPLOSIVE		3

#define STAR_SMALL_V			0.05f

#define STAR_SMALL_1_X0			0
#define STAR_SMALL_1_Y0			32
#define STAR_SMALL_1_VX			0
#define STAR_SMALL_1_VY			-1

#define STAR_SMALL_2_X0			30.4f
#define STAR_SMALL_2_Y0			9.92f
#define STAR_SMALL_2_VX			-0.95f
#define STAR_SMALL_2_VY			-0.31f

#define STAR_SMALL_3_X0			18.9f
#define STAR_SMALL_3_Y0			-25.92f
#define STAR_SMALL_3_VX			-0.59f
#define STAR_SMALL_3_VY			0.81f

#define STAR_SMALL_4_X0			-18.9f
#define STAR_SMALL_4_Y0			-25.92f
#define STAR_SMALL_4_VX			0.59f
#define STAR_SMALL_4_VY			0.81f

#define STAR_SMALL_5_X0			-30.4f
#define STAR_SMALL_5_Y0			9.92f
#define STAR_SMALL_5_VX			0.95f
#define STAR_SMALL_5_VY			-0.31f

#define STAR_EXPLOSIVE_TIME		250
///////////////////////
/// SWING

#define	SWING_BBOX_WIDTH	38
#define	SWING_BBOX_HEIGHT	68

#define	SWING_SS_STAND	100
#define	SWING_SS_MOVE	200
#define	SWING_SS_OPEN	300
#define	SWING_SS_STOP	400

#define	SWING_ANIMATION_STAND		0
#define	SWING_ANIMATION_MOVE		1
#define	SWING_ANIMATION_OPEN		2
#define	SWING_ANIMATION_STOP		3

#define	SWING_SPEED_X		0.015
#define SWING_TIME_OPEN		300
#define	SWING_TIME_STOP		200

#define	SWING_LIMIT_X		1920

////// 
/// TUBE //// 
#define TUBE_ANIMATION_TYPE_1		0
#define TUBE_ANIMATION_TYPE_2		1
#define TUBE_ANIMATION_TYPE_3		2
#define TUBE_ANIMATION_TYPE_4		3
#define TUBE_ANIMATION_TYPE_5		4
#define TUBE_ANIMATION_TYPE_6		5
#define TUBE_ANIMATION_TYPE_7		6
#define TUBE_ANIMATION_TYPE_8		7
#define TUBE_ANIMATION_TYPE_9		8
#define TUBE_ANIMATION_TYPE_10	9

#define TUBE_BBOX_WIDTH	16
#define TUBE_BBOX_HEIGHT	16

//////////////
