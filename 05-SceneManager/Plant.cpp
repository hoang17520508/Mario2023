#include "Plant.h"
#include "Game.h"
#include "Textures.h"
#include "PlayScene.h"


CPlant::CPlant(float x, float y) :CGameObject(x, y)
{
	ay = 0; 
	ax = 0;
	vx = 0; 
	vy = PLANT_SPEED;
	is_downing = FALSE;
	time_down_start = 0;
	time_up_start = 0;
	min_y = y - PLANT_BBOX_HEIGHT;
	original_x = x;
	original_y = y;

}


void CPlant::RenderBoundingBox()
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
void CPlant::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (!CheckInCam()) return;
	int ani_id = ID_ANI_PLANT_LEFT;
	float mario_x, mario_y;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	mario->GetPosition(mario_x, mario_y);
	if (mario_x >= x) {
		ani_id = ID_ANI_PLANT_RIGHT;
	}
	animations->Get(ani_id)->Render(x, y);
	//RenderBoundingBox();
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	float mario_x, mario_y;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	mario->GetPosition(mario_x, mario_y);

	if (is_upping) {
		if (y > min_y) {
			vy = -PLANT_SPEED;
		}
		else {
			vy = 0;
			y = min_y;
			if (GetTickCount64() - time_up_start > PLANT_TIME_OUT_UP_STATE) {
				SetState(PLANT_STATE_DOWN);
				CBullet* bullet = (CBullet*)scene->AddObject(new CBullet(original_x, original_y - PLANT_BBOX_HEIGHT));
				bullet->SetPosition(original_x , original_y - PLANT_BBOX_HEIGHT);
				bullet->Shoot(mario_x, mario_y, y);
				DebugOut(L" time to shoot");
			}
		}
	}
	else 
	{
		if (GetTickCount64() - time_down_start > PLANT_TIME_OUT_DOWN_STATE) {
			SetState(PLANT_STATE_UP);
		}
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPlant::SetState(int state)
{
	switch (state) {
	case PLANT_STATE_UP:
		time_up_start = GetTickCount64();
		time_down_start = 0;
		vy = -PLANT_SPEED;
		is_downing = FALSE;
		is_upping = TRUE;
		break;
	case PLANT_STATE_DOWN:
		time_down_start = GetTickCount64();
		time_up_start = 0;
		vy = PLANT_SPEED;
		is_upping = FALSE;
		is_downing = TRUE;
		break;
	default:
		break;
	}
}


void CPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PLANT_BBOX_WIDTH / 2;
	t = y - PLANT_BBOX_HEIGHT / 2;
	r = l + PLANT_BBOX_WIDTH;
	b = t + PLANT_BBOX_HEIGHT;
}