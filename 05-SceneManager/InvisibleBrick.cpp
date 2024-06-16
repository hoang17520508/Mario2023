#include "InvisibleBrick.h"
#include "Game.h"
#include "Textures.h"


CInvisibleBrick::CInvisibleBrick(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = INVISIBLE_BRICK_GRAVITY;
}

void CInvisibleBrick::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, 0.7, rect.right - 1, rect.bottom - 1);
}
void CInvisibleBrick::Render()
{
	/*CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_INVISIBLE_BRICK)->Render(x, y);*/
	RenderBoundingBox();
}

void CInvisibleBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CInvisibleBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};


void CInvisibleBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - INVISIBLE_BRICK_BBOX_WIDTH / 2;
	t = y - INVISIBLE_BRICK_BBOX_HEIGHT / 2;
	r = l + INVISIBLE_BRICK_BBOX_WIDTH;
	b = t + INVISIBLE_BRICK_BBOX_HEIGHT;
}