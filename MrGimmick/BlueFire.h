#pragma once
#include "GameObject.h"
#include "Utils.h"


class CBlueFire : public CGameObject
{
public:
	CBlueFire() : CGameObject()
	{
	}
	~CBlueFire() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

