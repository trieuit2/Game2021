#include "Boom.h"
#include "PlayScene.h"
#include "algorithm"

CBoom::CBoom() : CGameObject()
{
	SetState(BOOM_SS_ALIVE);
}

void CBoom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BOOM_BBOX_WIDTH;
	bottom = y - BOOM_BBOX_HEIGHT;

	if (state == BOOM_SS_EXPLODE)
	{
		left = x;
		top = y;
		right = x + BOOM_BBOX_EXPLODE_WIDTH;
		bottom = y - BOOM_BBOX_EXPLODE_HEIGHT;
	}
}

void CBoom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	vector<LPGAMEOBJECT> newCoObjects;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBrick*>(coObjects->at(i))) newCoObjects.push_back(coObjects->at(i));
		else if (dynamic_cast<CInclinedBrick*>(coObjects->at(i))) newCoObjects.push_back(coObjects->at(i));
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != BOOM_SS_DIE)
		CalcPotentialCollisions(&newCoObjects, coEvents);

	if (state == BOOM_SS_EXPLODE)
	{
		if (explode_start == 0)
		{
			StartExplode();
		}
		if (GetTickCount64() - explode_start >= BOOM_EXPLODE_TIME)
		{
			SetState(BOOM_SS_DIE);
		}
	}

	CGimmick* gimmick = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (this->CheckAABB(gimmick) && this->state != BOOM_SS_DIE)
		gimmick->SetState(GIMMICK_SS_STUN);
	if (state == BOOM_SS_ALIVE)
	{
		if (gimmick->y < this->y)
		{
			if (gimmick->x + GIMMICK_BBOX_WIDTH >= this->x && gimmick->x <= this->x + BOOM_BBOX_WIDTH)
			{
				SetState(BOOM_SS_FALLING);
			}
		}
	}


	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		float x0 = x;
		float y0 = y;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->ny != 0)
				{
					DebugOut(L"[INFO] Collisions");
					SetState(BOOM_SS_EXPLODE);
				}
			}
			if (dynamic_cast<CInclinedBrick*>(e->obj))
			{
				CInclinedBrick* incline_brick = dynamic_cast<CInclinedBrick*>(e->obj);
				if (e->ny != 0)
				{
					SetState(BOOM_SS_EXPLODE);
				}
			}
		}
	}

	// clean up newCoObjects
	for (UINT i = 0; i < newCoObjects.size(); i++) newCoObjects[i] = nullptr;
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void CBoom::Render()
{
	int ani = -1;


	if (state == BOOM_SS_DIE)
		return;
	else if (state == BOOM_SS_ALIVE)
		ani = BOOM_ANIMATION_ALIVE;
	else if (state == BOOM_SS_FALLING)
		ani = BOOM_ANIMATION_DEAD;
	else if (state == BOOM_SS_EXPLODE)
		ani = BOOM_ANIMATION_EXPLODE;

	int alpha = 255;

	if (state == BOOM_SS_EXPLODE)
		animation_set->at(ani)->Render(x - 1, y - 5, alpha);
	else
		animation_set->at(ani)->Render(x, y, alpha);

	//RenderBoundingBox(2);
}

void CBoom::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case BOOM_SS_FALLING:
		vy = -BOOM_GRAVITY;
		break;
	case BOOM_SS_EXPLODE:
		vy = 0;
		break;
	}
}