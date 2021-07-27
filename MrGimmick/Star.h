#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Conveyor.h"
#include "InclinedBrick.h"
#include "constant.h"

class CStar : public CGameObject
{
	float star_small_1_x = STAR_SMALL_1_X0;
	float star_small_1_y = STAR_SMALL_1_Y0;

	float star_small_2_x = STAR_SMALL_2_X0;
	float star_small_2_y = STAR_SMALL_2_Y0;

	float star_small_3_x = STAR_SMALL_3_X0;
	float star_small_3_y = STAR_SMALL_3_Y0;

	float star_small_4_x = STAR_SMALL_4_X0;
	float star_small_4_y = STAR_SMALL_4_Y0;

	float star_small_5_x = STAR_SMALL_5_X0;
	float star_small_5_y = STAR_SMALL_5_Y0;

	DWORD explosive_start;
public:
	CStar();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Ready();
	void Shot();
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

