#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "constant.h"


class CChain : public CGameObject
{
	int type;
public:
	CChain(int type) : CGameObject()
	{
		this->type = type;
	}
	~CChain() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

