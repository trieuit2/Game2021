#include "BlackEnemy.h"
#include "Utils.h"
#include "InclinedBrick.h"

CBlackEnemy::CBlackEnemy(int direction)
{
	SetState(BLACKENEMY_SS_WALK);
	if (direction == 1) //chinh huong di ban dau
		ax = BLACKENEMY_ACCELERATION; // moi vo di sang Phai 1
	else
		ax = -BLACKENEMY_ACCELERATION; // moi vo di sang trai -1

	this->canTurnAround = false; //tranh truong hop moi vao da quay dau
}

void CBlackEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	vx += ax * dt;
	vy -= BLACKENEMY_GRAVITY * dt;

	onInclinedBrick = false;
	detectedStraighRoad = false;
	onGround = false;
	facingBrick = false;
	onFastConveyor = false;
	onSlowConveyor = false;

	CalculateSpeed();
	DetectPlayer();
	Transform();
	DetectStar();

	vector<LPGAMEOBJECT> newCoObjects;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBrick*>(coObjects->at(i))) newCoObjects.push_back(coObjects->at(i));
		else if (dynamic_cast<CConveyor*>(coObjects->at(i))) newCoObjects.push_back(coObjects->at(i));
		else if (dynamic_cast<CSwing*>(coObjects->at(i))) newCoObjects.push_back(coObjects->at(i));
		else if (dynamic_cast<CBrickPink*>(coObjects->at(i))) newCoObjects.push_back(coObjects->at(i));

		if (dynamic_cast<CInclinedBrick*>(coObjects->at(i))) {
			CInclinedBrick* brick = dynamic_cast<CInclinedBrick*>(coObjects->at(i));
			if (onTopOf(brick)) this->detectedStraighRoad = true;
			if (state != BLACKENEMY_SS_DIE) brick->Collision(this, dy); //fix loi chet roi van leo doc duoc
		}
		if (dynamic_cast<CConveyor*>(coObjects->at(i))) {
			CConveyor* conveyor = dynamic_cast<CConveyor*>(coObjects->at(i));
			if (onTopOf(conveyor)) { this->onGround = true; this->detectedStraighRoad = true;}
		}
		if (dynamic_cast<CBrick*>(coObjects->at(i))) {
			CBrick* brick = dynamic_cast<CBrick*>(coObjects->at(i));
			if (onTopOf(brick)) this->onGround = true;
			if (onSideOf(brick)) { this->facingBrick = true;
			}
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != BLACKENEMY_SS_DIE)
		CalcPotentialCollisions(&newCoObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		if (!onInclinedBrick)
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

		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			float ol, ot, or , ob;
			e->obj->GetBoundingBox(ol, ot, or , ob);
			

			if (state == BLACKENEMY_SS_BULLET) state = BLACKENEMY_SS_WALK;
			if (e->ny > 0) onGround = true;

			if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick *brick = dynamic_cast<CBrick*>(e->obj);
				x = x0 + min_tx * dx + nx * 0.1f;
				y = y0 + min_ty * dy + ny * 0.1f;
				if (onInclinedBrick) x = x0 + dx;
				if (e->nx != 0)
				{
					vx = 0;
					if (state == BLACKENEMY_SS_WALK) {
						if (this->onGround && InJumpablePosition())
							Jump();
					}
				}
				if (e->ny > 0)
				{
					vy = 0;
					if (((l < ol - 3 && vx < 0) || (r > or + 3 && vx > 0)) && InJumpablePosition() && !detectedStraighRoad) Jump(); //bien detectedStraighRoad phat hien duong thang khong cho nhay
				}
				if (e->ny < 0 && !facingBrick && !onGround)
					vy = -BLACKENEMY_GRAVITY;
			}
			if (dynamic_cast<CConveyor*>(e->obj))
			{
				x = x0 + min_tx * dx + nx * 0.1f;
				y = y0 + min_ty * dy + ny * 0.1f;
				if (onInclinedBrick) x = x0 + dx;
				CConveyor* conveyor = dynamic_cast<CConveyor*>(e->obj);
				if (e->ny < 0) {
					if(state != BLACKENEMY_SS_FLY)
						vy = -BLACKENEMY_GRAVITY;
				}
				if (e->ny > 0) {
					if (conveyor->GetDirection() > 0) {
						x += 1.0f;
						onFastConveyor = true;
					}
					else {
						x -= 1.0f;
						onSlowConveyor = true;
					}
				}
			}
		}
	}
	// clean up newCoObjects
	for (UINT i = 0; i < newCoObjects.size(); i++) newCoObjects[i] = nullptr;
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBlackEnemy::Render()
{
	int ani = 0;
	if (state == BLACKENEMY_SS_WALK || state == BLACKENEMY_SS_BULLET) { //==============WALK
		if (ax > 0)
			ani = BLACKENEMY_ANIMATION_WALK_RIGHT;
		else
			ani = BLACKENEMY_ANIMATION_WALK_LEFT;
	}
	else if (state == BLACKENEMY_SS_TRANSFORM) {  //==============TRANSFORM
		if (vx > 0)
			ani = BLACKENEMY_ANIMATION_FLY_RIGHT;
		else
			ani = BLACKENEMY_ANIMATION_FLY_LEFT;
	}
	else if (state == BLACKENEMY_SS_FLY) { //==============FLY
		if (ax > 0) {
			if (this->onGround)
				ani = BLACKENEMY_ANIMATION_FLY_ONGROUND_RIGHT;
			else
				ani = BLACKENEMY_ANIMATION_FLY_RIGHT;
		}
		else {
			if (this->onGround)
				ani = BLACKENEMY_ANIMATION_FLY_ONGROUND_LEFT;
			else
				ani = BLACKENEMY_ANIMATION_FLY_LEFT;
		}
	}
	else if (state == BLACKENEMY_SS_DIE) { //============== DIE
		if (nx > 0)
			ani = BLACKENEMY_ANIMATION_DIE_RIGHT;
		else
			ani = BLACKENEMY_ANIMATION_DIE_LEFT;
	}
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox(3);
}

void CBlackEnemy::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BLACKENEMY_SS_WALK:
		ax = -BLACKENEMY_ACCELERATION; // moi vo di sang Phai
		break;
	case BLACKENEMY_SS_TRANSFORM:
		if (ax > 0)
			nx = 1;
		else
			nx = -1; //Xac dinh huong de chuyen sang trang thai FLY
		ax = 0;
		vx = 0;
		break;
	case BLACKENEMY_SS_FLY: 
		if (nx > 0) 
			ax = BLACKENEMY_FLY_ACCELERATION;
		else
			ax = -BLACKENEMY_FLY_ACCELERATION;
		break;
	case BLACKENEMY_SS_BULLET:
		ax = BLACKENEMY_ACCELERATION;
		break;
	case BLACKENEMY_SS_DIE:
		ax = 0;
		if (CheckSideOfStar() == -1){
			vx = BLACKENEMY_DEFLECT_SPEED_X;
		}
		else {
			vx = -BLACKENEMY_DEFLECT_SPEED_X;
		}
		vy = BLACKENEMY_DEFLECT_SPEED_Y;
		break;
	}
}

void CBlackEnemy::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	if (state == BLACKENEMY_SS_FLY) t = y - 1;
		else t = y;
	r = x + BLACKENEMY_WIDTH;
	b = y - BLACKENEMY_HEIGHT;
}

void CBlackEnemy::Jump()
{
	CScene* scene = CGame::GetInstance()->GetCurrentScene();
	CGimmick* player = ((CPlayScene*)scene)->GetPlayer();

	vy = BLACKENEMY_JUMP_SPEED;
	
	player->onEnemy = true; 
	
	if (this->carry_player && vx == 0)
		jump_count += 1;
}

bool CBlackEnemy::onTopOf(CGameObject* object)
{
	float ol, ot, or , ob;
	object->GetBoundingBox(ol, ot, or , ob);
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	if (r >= ol && l <= or && abs(b - ot) < 1)
		return true;
	return false;
}

void CBlackEnemy::CalculateSpeed()
{
	CScene* scene = CGame::GetInstance()->GetCurrentScene();
	CGimmick* player = ((CPlayScene*)scene)->GetPlayer();

	// ===== WALK:
	if (state == BLACKENEMY_SS_WALK && vx > BLACKENEMY_WALK_SPEED)
		vx = BLACKENEMY_WALK_SPEED;
	if (state == BLACKENEMY_SS_WALK && vx < -BLACKENEMY_WALK_SPEED)
		vx = -BLACKENEMY_WALK_SPEED;
	// ===== FLY:
	//SPEED X:
	if (state == BLACKENEMY_SS_FLY && vx > BLACKENEMY_FLY_SPEED)
		vx = BLACKENEMY_FLY_SPEED;
	if (state == BLACKENEMY_SS_FLY && vx < -BLACKENEMY_FLY_SPEED)
		vx = -BLACKENEMY_FLY_SPEED;
	//SPEED Y:
	if (state == BLACKENEMY_SS_FLY) {
		if (this->y < player->y) vy = BLACKENEMY_FLY_SPEED_Y;
		if (this->y > player->y) vy = -BLACKENEMY_FLY_SPEED_Y;
		if (this->y == player->y) vy = 0; //fix loi giat giat
	}
	// ===== BULLET:
	if (state == BLACKENEMY_SS_BULLET && vx > BLACK_ENEMY_BULLET_SPEED)
		vx = BLACK_ENEMY_BULLET_SPEED;
	if (state == BLACKENEMY_SS_BULLET && vx < -BLACK_ENEMY_BULLET_SPEED)
		vx = -BLACK_ENEMY_BULLET_SPEED;
}

void CBlackEnemy::TurnAroundSlowly()
{
	if (state == BLACKENEMY_SS_WALK)
	{
		if (vx > 0)
			ax = -BLACKENEMY_ACCELERATION;
		if (vx < 0)
			ax = BLACKENEMY_ACCELERATION;
	}
	if (state == BLACKENEMY_SS_FLY)
	{
		if (vx > 0)
			ax = -BLACKENEMY_FLY_ACCELERATION;
		if (vx < 0)
			ax = BLACKENEMY_FLY_ACCELERATION;
	}
}

void CBlackEnemy::TurnAroundImmediately()
{
	if (state == BLACKENEMY_SS_WALK)
	{
		if (vx > 0) {
			vx = 0;
			ax = -BLACKENEMY_ACCELERATION;
		}
		if (vx < 0) {
			vx = 0;
			ax = BLACKENEMY_ACCELERATION;
		}
	}
	if (state == BLACKENEMY_SS_FLY)
	{
		if (vx > 0) {
			vx = 0;
			ax = -BLACKENEMY_FLY_ACCELERATION;
		}
		if (vx < 0) {
			vx = 0;
			ax = BLACKENEMY_FLY_ACCELERATION;
		}
	}
	
}

void CBlackEnemy::DetectPlayer()
{
	CScene* scene = CGame::GetInstance()->GetCurrentScene();
	CGimmick* player = ((CPlayScene*)scene)->GetPlayer();

	//Reset dem neu ngang hang hoac o duoi gimmick:
	if (this->y >= player->y) {
		turn_count = 0;
		jump_count = 0;
	}
	// Duoi theo gimmick:
	if (state == BLACKENEMY_SS_WALK)
	{
		if (!player->onEnemy) //ko dc quay dau tren khong trung
		{
			if (this->canTurnAround && this->x > player->x + PLAYER_MAX_RANGE_WALK && this->ax > 0)
			{
				TurnAroundSlowly();
				this->canTurnAround = false;

				if (this->y < player->y) //Neu Gimmick o tren cao bat dau dem
					turn_count += 1;
			}
			if (this->canTurnAround && this->x < player->x - PLAYER_MAX_RANGE_WALK && this->ax < 0)
			{
				TurnAroundSlowly();
				this->canTurnAround = false;

				if (this->y < player->y)
					turn_count += 1;
			}
		}
		else 
		{ // Dang bi gimmick cuoi thi quay dau theo huong gimmick lai'
			if (player->x > this->x + 5) //So pixel chenh lech de lai' theo huong
			{
				this->ax = BLACKENEMY_ACCELERATION;
			}
			if (player->x < this->x - 5)
			{
				this->ax = -BLACKENEMY_ACCELERATION;
			}
		}
		

	}

	if (state == BLACKENEMY_SS_FLY)
	{
		if (this->canTurnAround && this->x > player->x + PLAYER_MAX_RANGE_FLY + 16)
		{
			TurnAroundSlowly();
			this->canTurnAround = false;
		}
		if (this->canTurnAround && this->x < player->x - PLAYER_MAX_RANGE_FLY)
		{
			TurnAroundSlowly();
			this->canTurnAround = false;
		}
	}
	
	//reset quay dau
	if (!player->onEnemy) {
		if (!this->canTurnAround && (this->x >= player->x - (PLAYER_MAX_RANGE_FLY - 1)) && (this->x <= player->x + (PLAYER_MAX_RANGE_FLY - 1) /*+ 16*/)) //reset turn around, can dam bao so +- < PLAYER_MAX_RANGE_FLY
			this->canTurnAround = true;
	}
	
	if (!player->onEnemy) //Reset bien carry_player neu gimmick khong cuoi quai (vi gimmick 1 luc chi cuoi~ 1 con)
		carry_player = false;
}

void CBlackEnemy::Transform()
{
	if ((turn_count == TURN_COUNT_TO_TRANSFORM || jump_count >= JUMP_COUNT_TO_TRANSFORM )&& state == BLACKENEMY_SS_WALK) {
		SetState(BLACKENEMY_SS_TRANSFORM);
		this->transform_start = GetTickCount64();
		this->transforming = true;
		this->y += 1; // day len 1 chut tranh loi rot xuyen gach
	} //BAT DAU BIEN HINH

	if (state == BLACKENEMY_SS_TRANSFORM && this->transforming && GetTickCount64() - this->transform_start >= BLACKENEMY_TRANSFORM_TIME)
	{
		SetState(BLACKENEMY_SS_FLY);
		this->transform_start = 0;
		this->transforming = false;
	}

}

bool CBlackEnemy::onSideOf(CGameObject* object, float equal)
{
	float ol, ot, or , ob;
	object->GetBoundingBox(ol, ot, or , ob);
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	if (dynamic_cast<CBrick*>(object))
	{
		if (b <= ot && t >= ob && ((abs(l - or ) < equal && l >= or) || (abs(r - ol) < equal && r <= ol)))
			return true;
	}
	return false;
}

bool CBlackEnemy::isUnder(CGameObject* object, float equal)
{
	float ol, ot, or , ob;
	object->GetBoundingBox(ol, ot, or , ob);
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	if (dynamic_cast<CBrick*>(object) || dynamic_cast<CConveyor*>(object))
	{
		if (r >= ol && l <= or && (abs(ob - t) < equal))
			return true;
	}
	return false;
}

bool CBlackEnemy::InJumpablePosition()
{
	CScene* scene = CGame::GetInstance()->GetCurrentScene();
	CGimmick* player = ((CPlayScene*)scene)->GetPlayer();

	if (y - BLACKENEMY_HEIGHT <= player->y)
		return true;
	return false;
}

void CBlackEnemy::DetectStar()
{
	CScene* scene = CGame::GetInstance()->GetCurrentScene();
	CStar* star = ((CPlayScene*)scene)->GetStar();

	if (CheckAABB(star) && state != BLACKENEMY_SS_DIE && star->state != STAR_SS_HIDE 
		&& star->state != STAR_SS_EXPLOSIVE && star->state != STAR_SS_PENDING && star->state != STAR_SS_READY)
	{
		SetState(BLACKENEMY_SS_DIE);
	}
}

int CBlackEnemy::CheckSideOfStar() // -1 left, 1 right dung de xac dinh huong die
{
	CScene* scene = CGame::GetInstance()->GetCurrentScene();
	CStar* star = ((CPlayScene*)scene)->GetStar();
	if (star->x < x)
		return -1;
	else
		return 1;
}
