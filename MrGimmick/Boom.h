#pragma once
#include "GameObject.h"
#include "Gimmick.h"



class CBoom : public CGameObject
{
	DWORD explode_start = 0;

public:
	CBoom();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void StartExplode() { explode_start = GetTickCount64(); }

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

