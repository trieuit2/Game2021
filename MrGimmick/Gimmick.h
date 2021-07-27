#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "BrickPink.h"
#include "InclinedBrick.h"
#include "Conveyor.h"
#include "Swing.h"
#include "Medicine.h"




class CGimmick : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;

	DWORD stunning_start;
	float ax = NULL;

	
	bool updated = false;
public:
	float ay = 0;
	bool onGround = false;
	bool falling = false;
	bool jumping = false;
	bool stunning = false;
	bool onEnemy = false;
	bool facingBrick = false; //fix loi dung tren lung quai bi xuyen gach
	bool underBrick = false;

	void CreateDieEffect();

	CGimmick();
	void CalculateSpeed(DWORD dt);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = DWORD(GetTickCount64()); }
	void SetdifY(float y) { this->y += y; };

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	bool onTopOf(CGameObject* object, float equal = 1);
	bool onSideOf(CGameObject* object, float equal = 1);
	void standOn(CGameObject* object);
	bool isUnder(CGameObject* object, float equal = 1);
	int getUntouchable() { return untouchable; }
};