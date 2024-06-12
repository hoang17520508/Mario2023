#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000
#define ID_ANI_COIN_JUMP 300001

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16
#define COIN_STATE_NORMAL 1
#define COIN_STATE_JUMP 2


class CCoin : public CGameObject {
	float ax;
	float ay;
public:
	CCoin(float x, float y) : CGameObject(x, y) {
		ax = 0;
		ay = 0.003f;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void SetState(int state);
	void OnNoCollision(DWORD dt);
};