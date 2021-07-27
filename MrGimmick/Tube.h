#pragma once
#include "GameObject.h"
#include "constant.h"


class CTube : public CGameObject
{
	int type;
public:
	CTube(int type) : CGameObject() {
		this->type = type;
	}
	~CTube() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

