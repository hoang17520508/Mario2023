#include "Coin.h"
#include "debug.h"

void CCoin::Render()
{
	int ani_id = ID_ANI_COIN;
	CAnimations* animations = CAnimations::GetInstance();
	if (state == COIN_STATE_JUMP && (original_y - y > MAX_JUMP_DISTANCE)) { DebugOut(L">>> COIN JUMP MAX >>> \n"); this->Delete(); }
	if (state == COIN_STATE_JUMP)
	{
		ani_id = ID_ANI_COIN_JUMP;
	}
	animations->Get(ani_id)->Render(x, y);

	//RenderBoundingBox();
}


void CCoin::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case COIN_STATE_NORMAL:
		vx = vy = ax = ay = 0;
		break;
	case COIN_STATE_JUMP:
		vx = 0;
		ay = 0.001f;
		vy = -0.31f;
		break;
	}
}


void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	vx += ax * dt;
	vy += ay * dt;

	CGameObject::Update(dt, co_objects);
	CCollision::GetInstance()->Process(this, dt, co_objects);
}

void CCoin::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}



void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}