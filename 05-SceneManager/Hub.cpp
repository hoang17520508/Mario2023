#pragma once
#include "Hub.h"

void CHub::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_HUB)->Render(x, y);
	//RenderBoundingBox();
}

void CHub::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - HUB_BBOX_WIDTH / 2;
	t = y - HUB_BBOX_HEIGHT / 2;
	r = l + HUB_BBOX_WIDTH;
	b = t + HUB_BBOX_HEIGHT;
}