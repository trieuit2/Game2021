#pragma once
#include "GameObject.h"
#include "Gimmick.h"



class CMedicine : public CGameObject
{
	int type;

public:
	CMedicine(int type);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};