#pragma once
#include "Hub.h"


void CHub::RenderLife() {
	float top, left;
	top = GetTop();
	left = GetLeft();
	float icon_number_life_x = left + 55;
	float icon_number_life_y = top + 15;

	float icon_life_x = left + HUD_LIFE_BBOX_WIDTH / 2 + 14;
	float icon_life_y = top + HUD_LIFE_BBOX_HEIGHT / 2 + 13;

	float icon_x_x = icon_life_x + HUD_LIFE_BBOX_WIDTH / 2 + HUD_X_ICON_BBOX_WIDTH / 2 + 3;
	float icon_x_y = icon_life_y + 1;

	CSymbolCharacterManager::RenderIcon("LIFE", icon_life_x, icon_life_y);
	CSymbolCharacterManager::RenderIcon("X", icon_x_x, icon_x_y);
	//hardcode data
	CSymbolCharacterManager::RenderNumber(3, icon_number_life_x, icon_number_life_y);
};
void CHub::RenderPoint() {};
void CHub::RenderPower() {};
void CHub::RenderWordName() {
	float top, left;
	top = GetTop();
	left = GetLeft();
	float world_name_y = top + 5;
	float world_name_x = left + 55;
	CSymbolCharacterManager::RenderString("WORLD", world_name_x - HUD_CHAR_BBOX_WIDTH * 5, world_name_y);
	CSymbolCharacterManager::RenderNumber(1, world_name_x - HUD_CHAR_BBOX_WIDTH * 5 + 40, world_name_y);
};
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
	RenderWordName();
	RenderLife();
	//RenderBoundingBox();
}

void CHub::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - HUB_BBOX_WIDTH / 2;
	t = y - HUB_BBOX_HEIGHT / 2;
	r = l + HUB_BBOX_WIDTH;
	b = t + HUB_BBOX_HEIGHT;
}