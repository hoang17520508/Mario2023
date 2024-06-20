#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PLANT_LEFT 602002
#define ID_ANI_PLANT_RIGHT 602005
#define PLANT_BBOX_WIDTH 26
#define PLANT_BBOX_HEIGHT 34
#define PLANT_SPEED 0.03f
#define PLANT_STATE_UP 100
#define PLANT_STATE_DOWN 200
#define PLANT_TIME_OUT_UP_STATE 3400 
#define PLANT_TIME_OUT_DOWN_STATE 5000

class CPlant : public CGameObject {
protected:
	float ax, ay;
	float vx, vy;

	float min_y;
	float max_y;

	BOOLEAN is_upping, is_downing;
	ULONGLONG time_down_start, time_up_start;
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	void RenderBoundingBox();
public:
	CPlant(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	virtual void SetState(int state);
};