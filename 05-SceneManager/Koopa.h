#pragma once
#include "GameObject.h"
#include "InvisibleBrick.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f


#define KOOPA_BBOX_WIDTH 20
#define KOOPA_BBOX_HEIGHT 22
#define KOOPA_BBOX_HEIGHT_DIE 7

#define KOOPA_DIE_TIMEOUT 500

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_WALKING_LEFT 100
#define KOOPA_STATE_WALKING_RIRHT 101
#define KOOPA_STATE_DEFEND 102
#define KOOPA_STATE_BE_KICKING 103
#define KOOPA_STATE_BE_HOLDING 104
#define KOOPA_STATE_BE_REFRESH 105
#define KOOPA_STATE_DIE 106

#define ID_ANI_KOOPA_WALKING 601002
#define ID_ANI_KOOPA_WALKING_RIGHT 601001
#define ID_ANI_KOOPA_WALKING_LEFT 601002
#define ID_ANI_KOOPA_DEFEND 601003
#define ID_ANI_KOOPA_BE_KICKING 601004
#define ID_ANI_KOOPA_BE_HOLDING 601005
#define ID_ANI_KOOPA_BE_REFRESH 601006
#define ID_ANI_KOOPA_DIE 5001

#define KOOPA_REFRESH_TIME 10000
class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;
	ULONGLONG refresh_time;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	//void OnCollisionWithWingGoomba(LPCOLLISIONEVENT e);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y);
	CInvisibleBrick* InBrick;
	virtual void SetState(int state);
};