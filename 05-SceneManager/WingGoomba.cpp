
#include "WingGoomba.h"

CWingGoomba::CWingGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = WINGGOOMBA_GRAVITY;
	die_start = -1;
	time_jump_start = 0;
	has_wing = true;
	SetState(WINGGOOMBA_STATE_WALKING);
}

void CWingGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == WINGGOOMBA_STATE_DIE)
	{
		left = x - WINGGOOMBA_BBOX_WIDTH / 2;
		top = y - WINGGOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + WINGGOOMBA_BBOX_WIDTH;
		bottom = top + WINGGOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - WINGGOOMBA_BBOX_WIDTH / 2;
		top = y - WINGGOOMBA_BBOX_HEIGHT / 2;
		right = left + WINGGOOMBA_BBOX_WIDTH;
		bottom = top + WINGGOOMBA_BBOX_HEIGHT;
	}
}

void CWingGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CWingGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	//if (dynamic_cast<CWingGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CWingGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// hardcode winggoomba in flatform
	if (!CheckInCam()) return;
	if (has_wing) {
		if (y > 150 && GetTickCount64() - time_jump_start > 2000)
		{
			SetState(WINGGOOMBA_STATE_WALKING);

		}

		if ((state == WINGGOOMBA_STATE_DIE) && (GetTickCount64() - die_start > WINGGOOMBA_DIE_TIMEOUT))
		{

			isDeleted = true;
			return;
		}
	}
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CWingGoomba::Render()
{
	int aniId = ID_ANI_WINGGOOMBA_WALKING;
	if (!CheckInCam()) { return; }
	if (state == WINGGOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_WINGGOOMBA_DIE;
	}
	if (state == NORMALGOOMBA_STATE_WALKING)
	{
		aniId = ID_ANI_NORMALGOOMBA_STATE_WALKING;
	}


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CWingGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WINGGOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (WINGGOOMBA_BBOX_HEIGHT - WINGGOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case WINGGOOMBA_STATE_WALKING:
		time_jump_start = GetTickCount64();
		vx = -WINGGOOMBA_WALKING_SPEED;
		vy = -0.19f;
		ay = 0.0005f;
		break;

	case NORMALGOOMBA_STATE_WALKING:
		vx = nx*WINGGOOMBA_WALKING_SPEED;
		break;
	}

}

void CWingGoomba::beAttacked() {
	if (has_wing) {
		has_wing = false;
		y = y - 2; // ajust goomba
		SetState(NORMALGOOMBA_STATE_WALKING);
		
	}
	else {
		SetState(WINGGOOMBA_STATE_DIE);
	}
}
