#include "QuestionBrick.h"
#include "Coin.h"
#include "Leaf.h"
#include "Mushroom.h"
#include "PlayScene.h"

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

void CQuestionBrick::OnNoCollision(DWORD dt)
{
	if (!is_open) return;

	x += vx * dt;
	y += vy * dt;

}

void CQuestionBrick::SetState(int state)
{
	CGameObject::SetState(state);
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	switch (state)
{
	case QUESTION_BRICK_STATE_UNBOX:
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (type_question_brick == QUESTION_BRICK_TYPE_MUSHROOM) {
			switch (mario->GetLevel())
			{
			case MARIO_LEVEL_BIG:
			{
				// sinh leaf
				CLeaf* mushroom = (CLeaf*)scene->AddObject(new CLeaf(x + QUESTION_BRICK_BBOX_WIDTH, y - QUESTION_BRICK_BBOX_HEIGHT*2));
				break;
			}
			case MARIO_LEVEL_TAIL:
			{
				CCoin* coin = (CCoin*)scene->AddObject(new CCoin(x, y - QUESTION_BRICK_BBOX_HEIGHT / 2));
				coin->SetPosition(x, y);
				coin->SetState(2);
				mario->CollectCoin();
				break;
			}
			case MARIO_LEVEL_SMALL:
			{
				CMushroom* mushroom = (CMushroom*)scene->AddObject(new CMushroom(x + QUESTION_BRICK_BBOX_WIDTH, y - QUESTION_BRICK_BBOX_HEIGHT / 2));
				break;
			}
			}
		}
		else {
			CCoin* coin = (CCoin*)scene->AddObject(new CCoin(x, y - QUESTION_BRICK_BBOX_HEIGHT / 2));
			coin->SetPosition(x, y);
			coin->SetState(2);
			mario->CollectCoin();
		}

		// TODO: case leaf handle later
		
		SetState(QUESTION_BRICK_STATE_DISABLE);
		is_open = TRUE;
		break;
	}	
}	
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTION_BRICK_BBOX_WIDTH / 2;
	t = y - QUESTION_BRICK_BBOX_HEIGHT / 2;
	r = l + QUESTION_BRICK_BBOX_WIDTH;
	b = t + QUESTION_BRICK_BBOX_HEIGHT;
}