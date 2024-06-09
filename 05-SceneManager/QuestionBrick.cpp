#include "QuestionBrick.h"

void CQuestionBrick::Render()
{
	int id_ani = ID_ANI_QUESTION_BRICK;
	CAnimations* animations = CAnimations::GetInstance();
	if (state == QUESTION_BRICK_STATE_DISABLE)
	{
		id_ani = ID_ANI_QUESTION_BRICK_DISABLE;
	}

	animations->Get(id_ani)->Render(x, y);
	//RenderBoundingBox();
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTION_BRICK_BBOX_WIDTH / 2;
	t = y - QUESTION_BRICK_BBOX_HEIGHT / 2;
	r = l + QUESTION_BRICK_BBOX_WIDTH;
	b = t + QUESTION_BRICK_BBOX_HEIGHT;
}