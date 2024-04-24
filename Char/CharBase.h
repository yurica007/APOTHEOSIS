#pragma once
#include "../Geometry.h"

class InputState;

class CharBase
{
public:
	CharBase();
	virtual ~CharBase();

	const Rect& GetRect() const;
	const Position2& GetPosition() const;

	void SetLevel(int selectLevel);

	void Init();
	void OnDamage();
	bool IsDamage();
	const bool IsEnable() const;
	const bool IsDead() const;

	void Update(const InputState& input);
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();

	void Draw();
	void DrawLifes();

	void UpdateLife();

protected:
	virtual void SetInitializeData() = 0;
	virtual void UpdateOrigin(const InputState& input) = 0;

	Rect rect_;

	void (CharBase::* updateFunc_)(void);

	const wchar_t* charHandleName;
	const wchar_t* lifeHandleName;

	int charHandle;
	int lifeHandle;
	bool handleTurn = false;

	int imgIdxX = 0;
	int imgIdxY = 0;

	int idelImgIdx = 0;
	int damageImgIdx = 0;
	int deadImgIdx = 0;

	int level = 0;
	int lifes;
	int lifesPosX;
	int lifesPosY;

	double extRate = 0.5;
	bool isEnlarge = true;

	int frame = 0;
	int Maxframe = 0;
	int ultimateTimer;

	bool isPlayer = false;
	bool isUltimate = false;
	bool onDamage = false;
	bool isEnable = false;
	bool isDead = false;
};

