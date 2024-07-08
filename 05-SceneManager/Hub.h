#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_HUB 103001
#define HUB_WIDTH 16
#define HUB_BBOX_WIDTH 16
#define HUB_BBOX_HEIGHT 16

class CHub : public CGameObject {
public:
	CHub(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
