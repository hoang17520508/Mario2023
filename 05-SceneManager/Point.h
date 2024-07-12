#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_POINT 1
#define ID_ANI_POINT_JUMP 300001

#define	POINT_WIDTH 10
#define POINT_BBOX_WIDTH 10
#define POINT_BBOX_HEIGHT 16
#define POINT_STATE_NORMAL 1
#define POINT_STATE_JUMP 2
#define MAX_JUMP_DISTANCE 1


class CPoint : public CGameObject {
	float ax;
	float ay;
	float original_y;
public:
	CPoint(float x, float y) : CGameObject(x, y) {
		ax = 0;
		ay = 0.003f;
		original_y = y;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void SetState(int state);
	void OnNoCollision(DWORD dt);
};