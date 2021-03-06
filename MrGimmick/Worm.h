#pragma once
#include "GameObject.h"

#define WORM_BBOX_WIDTH	23
#define WORM_BBOX_HEIGHT	14

#define WORM_WALKING_SPEED		0.075f 
#define WORM_DIE_DEFLECT_SPEED	 0.5f
#define WORM_GRAVITY	0.001f

#define WORM_SS_DIE				0
#define WORM_SS_WALKING_RIGHT	100
#define WORM_SS_WALKING_LEFT		200

#define WORM_ANIMATION_DIE_RIGHT	0
#define WORM_ANIMATION_DIE_LEFT	1
#define WORM_ANIMATION_RIGHT	2
#define WORM_ANIMATION_LEFT	3



class CWorm : public CGameObject
{
	int length;
	bool firstLocation = true;
	float leftLimit, rightLimit;
public:
	CWorm();
	CWorm(int length);
	~CWorm() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

