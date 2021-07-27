#include "BrickPink.h"
#include "Utils.h"
#include "PlayScene.h"
#include "Gimmick.h"




void CBrickPink::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// Calculate dx, dy 
	CGameObject::Update(dt);

	if (vyb == 1)
	{
		if (y > top && vy > 0)
		{
			vy = -vy;
		}
		if (y < toptrans && vy < 0)
			vy = -vy;
	}
	if (vyb == 0)
	{
		if (x > leftrans && vx > 0)
		{
			vx = -vx;
			nx = -nx;
		}
		if (x < left && vx < 0)
		{
			vx = -vx;
			nx = -nx;
		}
	}
	x += dx;
	y += dy;

	CGimmick* gimmick = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (this->CheckAABB(gimmick)) {
		gimmick->y = y + 16.4f;
	}
}

CBrickPink::CBrickPink(float left, float top, float leftrans, float toptrans, float av) : CGameObject() {
	this->left = left;
	this->top = top;
	this->leftrans = leftrans;
	this->toptrans = toptrans;
	this->av = av;
	if (left == leftrans)
	{
		this->vy = BRICK_SPEED * av;
		vyb = 1;
	}
	if (top == toptrans)
	{
		this->vx = BRICK_SPEED * av;
		this->nx = 1;
		vyb = 0;
	}
}

void CBrickPink::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + BRICK_BBOX_WIDTH;
	b = t - BRICK_BBOX_HEIGHT;
}

void CBrickPink::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox(2);
}