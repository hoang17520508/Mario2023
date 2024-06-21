#pragma once
#pragma once
#include "GameObject.h"

#define BULLET_BBOX_WIDTH	8
#define BULLET_BBOX_HEIGHT	8

#define BULLET_SPEED	0.08f
#define BULLET_GRAVITY	0.000008f

#define ID_ANI_BULLET 302001

#define BULLET_STATE_IDLE 100
#define BULLET_STATE_SHOOT 200

#define VX_BULLET	0.05f

#define VY_BULLET_MARIO_CLOSE	0.03f
#define VY_BULLET_MARIO_FAR	0.05f

#define MAX_ATTACK_ZONE	150
#define MIN_ATTACK_ZONE	100

class CBullet :
	public CGameObject
{

public:

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt);
	BOOLEAN active;
	virtual void SetActive(BOOLEAN active_value) { active = active_value; };
	CBullet(float x, float y)  {
		active = false;
	};
	void SetState(int state);
	void Shoot(float enemyX, float enemyY, float plant_y);
};

