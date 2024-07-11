#pragma once
#include "Hub.h"


void CHub::RenderLife() {};
void CHub::RenderPoint() {};
void CHub::RenderPower() {};
void CHub::RenderCoin() {
	float top, left;
	top = GetTop();
	left = GetLeft();
	float coin_x = left + 140;
	float coin_y = top + 5;
	float dolar_y = top + 7;
	CSymbolCharacterManager::RenderIcon("DOLAR",coin_x - HUD_CHAR_BBOX_WIDTH - 3 , dolar_y);
	//hardcode render 10 coin point handle integrate later
	CSymbolCharacterManager::RenderNumber(10,coin_x,coin_y);
};
void CHub::RenderCard() {};

void CHub::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_HUB)->Render(x, y);
	RenderCoin();
	//RenderBoundingBox();
}

void CHub::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - HUB_BBOX_WIDTH / 2;
	t = y - HUB_BBOX_HEIGHT / 2;
	r = l + HUB_BBOX_WIDTH;
	b = t + HUB_BBOX_HEIGHT;
}