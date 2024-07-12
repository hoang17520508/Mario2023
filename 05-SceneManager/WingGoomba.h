#pragma once
#include "GameObject.h"

#define WINGGOOMBA_GRAVITY 0.002f
#define WINGGOOMBA_WALKING_SPEED 0.05f


#define WINGGOOMBA_BBOX_WIDTH 16
#define WINGGOOMBA_BBOX_HEIGHT 14
#define WINGGOOMBA_BBOX_HEIGHT_DIE 7

#define WINGGOOMBA_DIE_TIMEOUT 500

#define WINGGOOMBA_STATE_FLY 300
#define WINGGOOMBA_STATE_WALKING 100
#define NORMALGOOMBA_STATE_WALKING 101
#define WINGGOOMBA_STATE_DIE 200

#define ID_ANI_WINGGOOMBA_WALKING 600003
#define ID_ANI_WINGGOOMBA_DIE 5001
#define ID_ANI_NORMALGOOMBA_STATE_WALKING 5000


class CWingGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	BOOLEAN has_wing;

	ULONGLONG die_start;
	ULONGLONG time_jump_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CWingGoomba(float x, float y);
	virtual void SetState(int state);
	void beAttacked();
};
