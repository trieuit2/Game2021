#pragma once
#include "GameObject.h"
#include "Gimmick.h"
#include "PlayScene.h"
#include "algorithm"



class CDoor : public CGameObject
{
	DWORD open_start = 0;

public:
	CDoor();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void StartOpen() { open_start = GetTickCount64(); }
	void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

