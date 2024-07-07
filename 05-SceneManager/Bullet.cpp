#include "Bullet.h"
#include "Mario.h"
#include "PlayScene.h"
#include "debug.h"

void CBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BULLET_BBOX_WIDTH / 2;
	top = y - BULLET_BBOX_HEIGHT / 2;
	right = left + BULLET_BBOX_WIDTH;
	bottom = top + BULLET_BBOX_WIDTH;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBullet::Render()
{
	if (!CheckInCam() || vx == 0) return;
	CAnimations::GetInstance()->Get(ID_ANI_BULLET)->Render(x, y);
}

//void CBullet::OnNoCollision(DWORD dt)
//{
//	x += vx * dt;
//	y += vy * dt;
//}

void CBullet::OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt)
{

}

void CBullet::SetState(int state)
{
}

void CBullet::Shoot(float enemyX, float enemyY, float plant_y)
{	
	// check in zone to attack
//	DebugOut(L"check v bullet enemyX :%d enemyY: %d plannY : %d", int(enemyX), int(enemyY), int(plant_y));
	if (abs(x - enemyX) <= MAX_ATTACK_ZONE)
	{
		if (checkShootFar(x, enemyX)) {
			DebugOut(L"far==");
			if (y > enemyY) {
				vy = -VY_BULLET_MARIO_FAR;
			}
			else
			{
				vy = VY_BULLET_MARIO_FAR;
			}
		}
		else
		{
			if (y > enemyY) {
				vy = -VY_BULLET_MARIO_CLOSE;
			}
			else
			{
				vy = VY_BULLET_MARIO_CLOSE;
			}
		}
		if (x - enemyX >= 0)  //ban qua ben trai
		{
			vx = -VX_BULLET;
		}
		else {
			vx = VX_BULLET;
		}
	}
	else {
		vx = 0;
		vy = 0;
	}
	//DebugOut(L"check v bullet %d  :  %d", float(vx), float(vy));
	SetSpeed(vx, vy);
}

