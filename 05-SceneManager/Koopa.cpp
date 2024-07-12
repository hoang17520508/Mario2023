#include "Koopa.h"
#include "debug.h" 
#include "Goomba.h"
#include "QuestionBrick.h"
#include "PlayScene.h"

CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->original_x = x;
	this->original_y = y;
	InBrick = new CInvisibleBrick(x, y);
	this->ay = KOOPA_GRAVITY;
	die_start = -1;
	SetState(KOOPA_STATE_WALKING);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_DEFEND)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_DEFEND_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_DEFEND_BBOX_HEIGHT;
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
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() != GOOMBA_STATE_DIE)
	{
		goomba->SetState(GOOMBA_STATE_DIE);
	}
}

void CKoopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e) {
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

	//DebugOut(L">>> Koopa touch current state : %d \n",int(state));
	if (state == KOOPA_STATE_DEFEND || state == KOOPA_STATE_BE_KICKING)
	{
		if ((GetTickCount64() - refresh_time >= KOOPA_REFRESH_TIME) && !CheckInCam())
		{
			SetState(KOOPA_STATE_WALKING);
			SetPosition(original_x, original_y);
		}
	}

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
	// CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	// TODO handle hold koopa
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
		aniId = ID_ANI_KOOPA_BE_KICKING;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	InBrick->Render();
	//RenderBoundingBox();
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
		refresh_time = GetTickCount64();
		vy = 0;
		vx = 0;
		break;
	case KOOPA_STATE_BE_KICKING:
		refresh_time = GetTickCount64();
		vx = nx*KOOPA_WALKING_SPEED * 5;
		break;
	}

}
