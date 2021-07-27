#include "Medicine.h"

CMedicine::CMedicine(int type) : CGameObject()
{
	this->type = type;
	SetState(MEDICINE_SS_APPEAR);
}

void CMedicine::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}

void CMedicine::Render()
{
	int ani;

	if (state == MEDICINE_SS_DISAPPEAR)
		return;
	else
	{
		switch (this->type)
		{
		case 1:
			ani = MEDICINE_ANIMATION_ORANGE;
			break;
		case 2:
			ani = MEDICINE_ANIMATION_PINK;
			break;
		case 3:
			ani = MEDICINE_ANIMATION_TYPE_3;
			break;
		case 4:
			ani = MEDICINE_ANIMATION_TYPE_4;
			break;
		default:
			break;
		}
	}

	int alpha = 255;
	animation_set->at(ani)->Render(x, y, alpha);
	//RenderBoundingBox(1);
}

void CMedicine::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state != MEDICINE_SS_DISAPPEAR)
	{
		if (type == 1)
		{
			l = x;
			t = y;
			r = l + MEDICINE_ORANGE_BBOX_WIDTH;
			b = t - MEDICINE_ORANGE_BBOX_HEIGHT;
		}
		else if (type == 2)
		{
			l = x;
			t = y;
			r = l + MEDICINE_PINK_BBOX_WIDTH;
			b = t - MEDICINE_PINK_BBOX_HEIGHT;
		}
		else if (type == 3 || type == 4)
		{
			l = x;
			t = y;
			r = l + MEDICINE_TYPE_3_4_BBOX_WIDTH;
			b = t - MEDICINE_TYPE_3_4_BBOX_HEIGHT;
		}
	}
}

void CMedicine::SetState(int state) 
{
	CGameObject::SetState(state);
}

