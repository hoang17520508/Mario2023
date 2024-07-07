#include "Leaf.h"
#include "debug.h"

void CLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_LEAF_FALLING_LEFT;
	if (vx >= 0)
	{
		aniId = ID_ANI_LEAF_FALLING_RIGHT;
	}
	else
	{
		aniId = ID_ANI_LEAF_FALLING_LEFT;
	}

	if (animations->Get(aniId))
		animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
}


void CLeaf::SetState(int state)
{
	switch (state) {
	case LEAF_STATE_IDLE:
		vy = -LEAF_SPEED_IDLE;
		break;
	case LEAF_STATE_FALLING:
		vy = 0;
		vx = -LEAF_VX_SPEED;
		fallingInWindTime = GetTickCount64();
		break;
	default:break;
	}
}


void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{

	vy = LEAF_GRAVITY * dt;
	if (GetTickCount64() - fallingInWindTime >= 350)
	{
			vx = - vx;
			fallingInWindTime = GetTickCount64();
	}
	 if (vy != 0)
	{
		if (original_y - y > LEAF_HEIGHT )
		{
			SetState(LEAF_STATE_FALLING);
		}
			
	}
	x += vx * dt;
	y += vy * dt;
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}



void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_WIDTH / 2;
	t = y - LEAF_HEIGHT / 2;
	r = l + LEAF_WIDTH;
	b = t + LEAF_HEIGHT;
}