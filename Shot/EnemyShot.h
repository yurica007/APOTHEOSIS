#pragma once
#include "../Geometry.h"

class EnemyShot
{
public:
	EnemyShot();
	virtual ~EnemyShot();

	void Fire(const Position2& pos, const Vector2& vel);
	const Rect& GetRect() const;

	void Init();

	void Impact();
	void Update();
	void Draw();

	void UpdateNormal();
	void UpdateImpact();

	void DrawNormal();
	void DrawImpact();

	void FinishImpact();
	bool IsEnable() const;
	void Delete();
	bool IsFire() const;
	bool IsCollision() const;

protected:
	virtual void SetInitializeData() = 0;

	//メンバ関数ポインタ
	void (EnemyShot::* updateFunc_) (void);
	void (EnemyShot::* drawFunc_) (void);

	Rect rect_ = {};
	Vector2 vel_ = {};

	bool isEnable = false;
	bool isImpact = false;
	bool isCollision = false;

	bool isAccelerat = false;
	bool isWidthLong = false;

	int normalImgWidth = 0;
	int normalImgHeight = 0;

	int impactImgWidth = 0;
	int impactImgHeight = 0;

	int collisionRangeWidth = 0;
	int collisionRangeHeight = 0;

	int normalHandle = -1;
	int impactHandle = -1;
	const wchar_t* normalHandleName;
	const wchar_t* impactHandleName;

	int imgIdxX = 0;
	int imgIdxY = 0;

	int normalImgIdx = 0;
	int impactImgIdx = 0;
	int frame;
};

