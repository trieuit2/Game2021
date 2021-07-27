#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "BrickPink.h"
#include "InclinedBrick.h"
#include "Conveyor.h"
#include "Swing.h"
#include "PlayScene.h"
#include "Game.h"
#include "Gimmick.h"



class CBlackEnemy : public CGameObject
{
public:
	bool onGround = true;
	bool canTurnAround = false;
	int turn_count = 0;
	int jump_count = 0;
	float ax = 0;

	DWORD transform_start = 0;
	bool transforming = false;

	bool carry_player = false;
	bool detectedStraighRoad = false;
	bool facingBrick = false; //neu va cham theo chieu ngang voi brick thi true
	bool onFastConveyor = false;
	bool onSlowConveyor = false;

	CBlackEnemy(int direction); //-1 left, 1 right
	~CBlackEnemy() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Jump();
	bool onTopOf(CGameObject* object);
	bool isUnder(CGameObject* object, float equal = 1);
	void CalculateSpeed();
	void TurnAroundSlowly();
	void TurnAroundImmediately();
	void DetectPlayer();
	void Transform();
	bool onSideOf(CGameObject* object, float equal = 1);
	bool InJumpablePosition();
	void DetectStar();
	int CheckSideOfStar();
};

