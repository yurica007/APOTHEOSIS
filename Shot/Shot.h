#pragma once
#include "../Geometry.h"

class Shot
{
public:
	Shot();

	const Rect& GetRect() const;
	void Impact();
	void Fire(const Position2& pos);

	bool IsEnable();
	bool IsFire();
	void Update();
	void UpdateNormal();
	void UpdateImpact();

	void Draw();
	void DrawNormal();
	void DrawImpact();
private:
	Rect rect_ = {};
	Vector2 vel_ = {};

	//メンバ関数ポインタ
	void (Shot::* updateFunc_) (void);
	void (Shot::* drawFunc_) (void);

	int normalHandle;
	int impactHandle;
	int imgIdx = 0;

	int frame;

	bool isEnable = false;
	bool isImpact = false;
};

