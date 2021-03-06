#include "Worm.h"
#include "Brick.h"
#include "Conveyor.h"
#include "InclinedBrick.h"
#include "Utils.h"
#include "Gimmick.h"

CWorm::CWorm() : CGameObject()
{
	
	SetState(WORM_SS_WALKING_RIGHT);
}

CWorm::CWorm(int l) : CGameObject()
{
	length = l;
	SetState(WORM_SS_WALKING_RIGHT);
}

void CWorm::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (firstLocation)
	{
		float tmp = y;
		GetPosition(leftLimit, tmp);
		rightLimit = leftLimit + (length - 1) * 16;
		firstLocation = false;
	}
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy -= WORM_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != WORM_SS_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		if (x >= (rightLimit) || x <= (leftLimit))
		{
			vx = -vx;
		}
		else
		{
			x += dx;
		}
		x -= dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
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
				y = y0 + min_ty * dy + ny * 0.1f;
				if (e->ny != 0)
				{
					vy = 0;
				}
			}
			x = x0 + min_tx * dx + nx * 0.1f;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CWorm::Render()
{
	int ani = -1;
	if (state == WORM_SS_DIE)
	{
		if (nx > 0)
			ani = WORM_ANIMATION_DIE_RIGHT;
		else
			ani = WORM_ANIMATION_DIE_LEFT;
	}
	else
	{
		if (vx > 0)
		{
			ani = WORM_ANIMATION_RIGHT;
		}
		else
		{
			ani = WORM_ANIMATION_LEFT;
		}
	}

	int alpha = 255;
	animation_set->at(ani)->Render(x, y, alpha);
}

void CWorm::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case WORM_SS_WALKING_RIGHT:
		vx = WORM_WALKING_SPEED;
		nx = 1;
		break;
	case WORM_SS_WALKING_LEFT:
		vx = -WORM_WALKING_SPEED;
		nx = -1;
		break;
	case WORM_SS_DIE:
		vx = 0;
		break;
	}
}

void CWorm::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + WORM_BBOX_WIDTH;
	b = t - WORM_BBOX_HEIGHT;
}