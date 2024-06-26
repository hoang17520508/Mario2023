#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QUESTION_BRICK 100000
#define ID_ANI_QUESTION_BRICK_DISABLE 100002
#define QUESTION_BRICK_WIDTH 16
#define QUESTION_BRICK_STATE_IDLE 1
#define QUESTION_BRICK_STATE_DISABLE 2
#define QUESTION_BRICK_STATE_UNBOX 3
#define QUESTION_BRICK_BBOX_WIDTH 16
#define QUESTION_BRICK_BBOX_HEIGHT 16
#define QUESTION_BRICK_TYPE_COIN 1
#define QUESTION_BRICK_TYPE_MUSHROOM 2

class CQuestionBrick : public CGameObject {
	BOOLEAN is_open = FALSE;
	float type_question_brick;
public:
	CQuestionBrick(float x, float y, float type = QUESTION_BRICK_TYPE_COIN) : CGameObject (x, y)
	{
		is_open = FALSE;
		type_question_brick = type;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	BOOLEAN CheckOpen() { return is_open; }
	void SetState(int state);
	void OnNoCollision(DWORD dt);
	void OpenQuestionBrick() { SetState(QUESTION_BRICK_STATE_UNBOX); };

};