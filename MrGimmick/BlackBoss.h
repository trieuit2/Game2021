#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "PlayScene.h"
#include "Game.h"
#include "Gimmick.h"



class CBlackBoss : public CGameObject
{
public:
	bool onGround = true;
	float ax = 0;
	// IDLE:
	ULONGLONG idle_time = 0;

	// Shooting time:
	ULONGLONG shoot_time = 0;
	int shots_count = 0;

	// Blink:
	ULONGLONG blink_time = 0;

	//life 
	int life_count = BLACKBOSS_LIFE_COUNT;

	CBlackBoss ();
	~CBlackBoss() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	bool onTopOf(CGameObject* object);
	void RenderEars();
	void CalculateState();
	void Shoot(float init_vx, float init_vy);
	void FirstShoot();
	void CalculateShooting();
	void DetectStar();
	void CalculateSpeed();
	void CreateReward();
};

