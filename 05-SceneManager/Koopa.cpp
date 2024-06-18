#include "Koopa.h"
#include "debug.h" 
#include "Goomba.h"
#include "QuestionBrick.h"

CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	InBrick = new CInvisibleBrick(x, y);
	this->ay = KOOPA_GRAVITY;
	die_start = -1;
	SetState(KOOPA_STATE_WALKING);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_DIE)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_DIE / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {
	DebugOut(L">>> Koopa touch goomba \n");
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() != GOOMBA_STATE_DIE)
	{
		goomba->SetState(GOOMBA_STATE_DIE);
	}
}

void CKoopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e) {
	DebugOut(L">>> Koopa touch Qbrick \n");
	CQuestionBrick* brick = dynamic_cast<CQuestionBrick*>(e->obj);
	brick->SetState(QUESTION_BRICK_STATE_UNBOX);
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		nx = e->nx;
	}
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	
	if ((state == KOOPA_STATE_DIE) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
//	DebugOut(L">>> Koopa  is in : %d : %d >>> \n",int(x),int(y));

	if (state == KOOPA_STATE_WALKING) {
		if (vx > 0)
		{
			InBrick->SetPosition(x + KOOPA_BBOX_WIDTH / 2 + INVISIBLE_BRICK_BBOX_WIDTH / 2, y);
		}
		else
		{
			InBrick->SetPosition(x - (KOOPA_BBOX_HEIGHT / 2 + INVISIBLE_BRICK_BBOX_WIDTH / 2), y);
		}
		InBrick->Update(dt, coObjects);
		float brick_x, brick_y;
		InBrick->GetPosition(brick_x, brick_y);
		if (brick_y - y > 0)
		{
			vx = -vx;
		}

	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING;
	if (!CheckInCam()) return;
	if (state == KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_KOOPA_DIE;
	}
	if (state == KOOPA_STATE_WALKING)
	{
		if (vx < 0)  aniId = ID_ANI_KOOPA_WALKING;
		if (vx > 0)  aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}

	if (state == KOOPA_STATE_DEFEND)
	{
		aniId = ID_ANI_KOOPA_DEFEND;
	}
	if (state == KOOPA_STATE_BE_KICKING)
	{
		aniId = ID_ANI_KOOPA_DEFEND;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	InBrick->Render();
	RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_DEFEND:
		vy = 0;
		vx = 0;
		break;
	case KOOPA_STATE_BE_KICKING:
		vx = nx*KOOPA_WALKING_SPEED * 3;
		break;
	}

}
