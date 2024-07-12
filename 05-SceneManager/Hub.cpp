#pragma once
#include "PlayScene.h"
#include "debug.h"
#include "Mario.h"

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
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int life = mario->GetLife();
	CSymbolCharacterManager::RenderIcon("LIFE", icon_life_x, icon_life_y);
	CSymbolCharacterManager::RenderIcon("X", icon_x_x, icon_x_y);
	//hardcode data
	CSymbolCharacterManager::RenderNumber(life, icon_number_life_x - 10, icon_number_life_y);
};
void CHub::RenderPoint() {
	float top, left;
	top = GetTop();
	left = GetLeft();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int point = mario->GetPoint();
	float point_x = left + 69;
	float point_y = top + 15;
	CSymbolCharacterManager::RenderNumber(point, point_x, point_y, 6);
};
void CHub::RenderPower() {
	float top, left;
	top = GetTop();
	left = GetLeft();
	float power_y = top + 8;
	float power_x = left + 63;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int power = int(mario->GetPower());
	DebugOut(L">>> Mario power >>> %d", power);
	for (int i = 0; i < 7; i++){
		CSymbolCharacterManager::RenderIcon("BLACK ARROW", power_x + i*HUD_CHAR_BBOX_WIDTH +3, power_y);
	}
	for (int i = 0; i < power; i++) {
		CSymbolCharacterManager::RenderIcon("WHITE ARROW", power_x + i * HUD_CHAR_BBOX_WIDTH + 3, power_y);
	}
	CSymbolCharacterManager::RenderIcon("BLACK POWER", power_x + 8 * HUD_CHAR_BBOX_WIDTH, power_y);
	if (power == 8)
	{
		CSymbolCharacterManager::RenderIcon("WHITE POWER", power_x + 8 * HUD_CHAR_BBOX_WIDTH, power_y);
	}
};
void CHub::RenderWordName() {
	float top, left;
	top = GetTop();
	left = GetLeft();
	float world_name_y = top + 5;
	float world_name_x = left + 55;
	CSymbolCharacterManager::RenderString("WORLD", world_name_x - HUD_CHAR_BBOX_WIDTH * 5, world_name_y);
	CSymbolCharacterManager::RenderNumber(1, world_name_x - HUD_CHAR_BBOX_WIDTH * 5 + 38, world_name_y);
};
void CHub::RenderCoin() {
	float top, left;
	top = GetTop();
	left = GetLeft();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float coin_x = left + 140;
	float coin_y = top + 5;
	float dolar_y = top + 7;
	int coin = mario->GetCoin();
	CSymbolCharacterManager::RenderIcon("DOLAR",coin_x - HUD_CHAR_BBOX_WIDTH - 3 , dolar_y);
	//hardcode render 10 coin point handle integrate later
	CSymbolCharacterManager::RenderNumber(coin,coin_x,coin_y);
};
void CHub::RenderCard() {};
void CHub::RenderTimeOut() {
	float top, left;
	top = GetTop();
	left = GetLeft();
	float time_x = left + 139;
	float time_y = top + 15;
	float clock_x = left + 129;
	float clock_y = top + 19;
	CSymbolCharacterManager::RenderIcon("CLOCK", clock_x, clock_y);
	CSymbolCharacterManager::RenderNumber(100, time_x, time_y,3);

};

void CHub::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_HUB)->Render(x, y);
	RenderCoin();
	RenderWordName();
	RenderLife();
	RenderPoint();
	RenderTimeOut();
	RenderPower();
	//RenderBoundingBox();
}

void CHub::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - HUB_BBOX_WIDTH / 2;
	t = y - HUB_BBOX_HEIGHT / 2;
	r = l + HUB_BBOX_WIDTH;
	b = t + HUB_BBOX_HEIGHT;
}
