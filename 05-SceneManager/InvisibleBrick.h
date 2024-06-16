#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_INVISIBLE_BRICK 10000
#define INVISIBLE_BRICK_WIDTH 1
#define INVISIBLE_BRICK_BBOX_WIDTH 22
#define INVISIBLE_BRICK_BBOX_HEIGHT 22
#define INVISIBLE_BRICK_GRAVITY 0.002f

class CInvisibleBrick : public CGameObject {
protected:
	float ax, ay;
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	void RenderBoundingBox();
public:
	CInvisibleBrick(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};