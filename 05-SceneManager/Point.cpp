#include "Point.h"
#include "debug.h"

void CPoint::Render()
{
	int ani_id = ID_ANI_POINT;
	CAnimations* animations = CAnimations::GetInstance();
	if (state == POINT_STATE_JUMP && (y - original_y  > MAX_JUMP_DISTANCE)) { DebugOut(L">>> POINT JUMP MAX >>> \n"); this->Delete(); }
	animations->Get(ani_id)->Render(x, y);

	//RenderBoundingBox();
}


void CPoint::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case POINT_STATE_NORMAL:
		vx = vy = ax = ay = 0;
		break;
	case POINT_STATE_JUMP:
		vx = 0;
		ay = 0.001f;
		vy = -0.31f;
		break;
	}
}


void CPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	vx += ax * dt;
	vy += ay * dt;

	CGameObject::Update(dt, co_objects);
	CCollision::GetInstance()->Process(this, dt, co_objects);
}

void CPoint::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}



void CPoint::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - POINT_BBOX_WIDTH / 2;
	t = y - POINT_BBOX_HEIGHT / 2;
	r = l + POINT_BBOX_WIDTH;
	b = t + POINT_BBOX_HEIGHT;
}