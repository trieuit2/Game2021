#include "Swing.h"
#include "Gimmick.h"
#include "PlayScene.h"
#include "algorithm"

CSwing::CSwing() : CGameObject()
{
	SetState(SWING_SS_STAND);
}

void CSwing::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y - 62.0f;
	right = x + SWING_BBOX_WIDTH;
	bottom = y - SWING_BBOX_HEIGHT;
}

void CSwing::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	x += dx;

	CGimmick* gimmick = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();


	if (x + SWING_BBOX_WIDTH / 2  >= SWING_LIMIT_X)
	{
		if (state == SWING_SS_MOVE)
			SetState(SWING_SS_OPEN);
	}
	
	if (state == SWING_SS_OPEN)
	{
		if (open_start == 0)
		{
			StartOpen();
		}
		if (GetTickCount64() - open_start >= SWING_TIME_STOP)
		{
			SetState(SWING_SS_STOP);
		}
	}
}

void CSwing::Render()
{
	int ani = -1;

	if (state == SWING_SS_STAND)
	{
		ani = SWING_ANIMATION_STAND;
	}
	else if (state == SWING_SS_MOVE)
		ani = SWING_ANIMATION_MOVE;
	else if (state == SWING_SS_OPEN)
		ani = SWING_ANIMATION_OPEN;
	else if (state == SWING_SS_STOP)
		ani = SWING_ANIMATION_STOP;

	int alpha = 255;
	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox(3);
}

void CSwing::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SWING_SS_STAND:
		vx = 0;
		break;
	case SWING_SS_MOVE:
		vx = SWING_SPEED_X;
		break;
	case SWING_SS_OPEN:
		vx = 0;
		break;
	}
}