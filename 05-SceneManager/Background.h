#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BACKGROUND 99999
#define BACKGROUND_WIDTH 16
#define BACKGROUND_BBOX_WIDTH 16
#define BACKGROUND_BBOX_HEIGHT 16

class CBackground : public CGameObject {
public:
	CBackground(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
