#pragma once
#include "GameObject.h"

class CSwing : public CGameObject
{
	DWORD open_start = 0;

public:
	CSwing();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void StartOpen() { open_start = GetTickCount64(); }
	void SetState(int state);

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};