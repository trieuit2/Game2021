#pragma once
#include "GameObject.h"
#include "constant.h"



class CConveyor : public CGameObject
{
	int direction;
public:
	CConveyor(int direction) : CGameObject() {
		this->direction = direction;
	}
	int GetDirection() { return this->direction; }
	~CConveyor() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

