#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "constant.h"



class CCogwheel : public CGameObject
{
	int type;
public:
	CCogwheel(int type) : CGameObject()
	{
		this->type = type;
	}
	~CCogwheel() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

