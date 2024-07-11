#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "SymbolCharacterManager.h"

#define ID_ANI_HUB 103001
#define HUB_WIDTH 251
#define HUB_BBOX_WIDTH 251
#define HUB_BBOX_HEIGHT 30

class CHub : public CGameObject {
public:
	CHub(float x, float y) : CGameObject(x, y) {}
	void Render();
	void RenderLife();
	void RenderPoint();
	void RenderPower();
	void RenderCoin();
	void RenderCard();
	void RenderWordName();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
