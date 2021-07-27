#include "Door.h"

CDoor::CDoor() : CGameObject()
{
	SetState(DOOR_SS_CLOSE);
}

void CDoor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// Calculate dx, dy 
	CGameObject::Update(dt);

	CGimmick* gimmick = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (state != DOOR_SS_STOP)
	{
		if (gimmick->x - x <= 56 && y - gimmick->y <= 70) {
			SetState(DOOR_SS_OPEN);
		}
	}
	if (state == DOOR_SS_OPEN)
	{
		if (open_start == 0)
		{
			StartOpen();
		}
		if (GetTickCount64() - open_start >= DOOR_LIMIT_TIME)
		{
			SetState(DOOR_SS_STOP);
		}
	}
}

void CDoor::Render()
{
	int ani;
	if (state == DOOR_SS_CLOSE) {
		ani = DOOR_ANIMATION_CLOSE;
	}
	else if (state == DOOR_SS_OPEN) {
		ani = DOOR_ANIMATION_OPEN;
	}
	else {
		ani = DOOR_ANIMATION_STOP;
	}
	int alpha = 255;
	animation_set->at(ani)->Render(x, y, alpha);
	//RenderBoundingBox(1);
}

void CDoor::SetState(int state)
{
	CGameObject::SetState(state);
}

void CDoor::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + DOOR_BBOX_WIDTH;
	bottom = top - DOOR_BBOX_HEIGHT;
}
