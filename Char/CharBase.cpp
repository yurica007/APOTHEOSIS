#include "CharBase.h"
#include "../GameData.h"
#include "../InputState.h"
#include <DxLib.h>

namespace
{
	constexpr int kUltimateTimer = 180;

	constexpr int kImgWidth = 32;
	constexpr int kImgHeight = 32;
}

CharBase::CharBase()
{
	updateFunc_ = &CharBase::UpdateNormal;

	charHandleName = 0;
	lifeHandleName = 0;

	charHandle = -1;
	lifeHandle = -1;

	lifes = 0;
	lifesPosX = 0;
	lifesPosY = 0;

	ultimateTimer = kUltimateTimer;
}

CharBase::~CharBase()
{
	DeleteGraph(charHandle);
	DeleteGraph(lifeHandle);
}

const Rect& CharBase::GetRect() const
{
	return rect_;
}

const Position2& CharBase::GetPosition() const
{
	return rect_.center;
}

void CharBase::SetLevel(int selectLevel)
{
	level = selectLevel;
}

void CharBase::Init()
{
	SetInitializeData();

	updateFunc_ = &CharBase::UpdateNormal;

	charHandle = LoadGraph(charHandleName);
	lifeHandle = LoadGraph(lifeHandleName);

	ultimateTimer = kUltimateTimer;
}

void CharBase::OnDamage()
{
	if (isUltimate) return;
	if (level != Data::kLevelPractice) lifes--;
	if (0 < lifes) updateFunc_ = &CharBase::UpdateDamage;
	else
	{
		isEnable = true;
		updateFunc_ = &CharBase::UpdateDead;
	}
	imgIdxX = 0;
	onDamage = true;
}

bool CharBase::IsDamage()
{
	if (onDamage) return true;
	else return false;
}

const bool CharBase::IsEnable() const
{
	return isEnable;
}

const bool CharBase::IsDead() const
{
	return isDead;
}

void CharBase::Update(const InputState& input)
{
	(this->*updateFunc_)();
	UpdateLife();
	if (onDamage || isDead) return;
	UpdateOrigin(input);
}

void CharBase::UpdateNormal()
{
	frame--;
	if (isPlayer) imgIdxY = 0;
	else imgIdxY = 0;

	if (frame < 0)
	{
		frame = Maxframe;
		if (imgIdxX < idelImgIdx - 1) imgIdxX++;
		else imgIdxX = 0;
	}
}

void CharBase::UpdateDamage()
{
	frame--;
	if (isPlayer) imgIdxY = 4;
	else imgIdxY = 6;

	if (frame < 0)
	{
		frame = Maxframe;
		if (imgIdxX < damageImgIdx - 1) imgIdxX++;
		else
		{
			updateFunc_ = &CharBase::UpdateNormal;
			imgIdxX = 0;
			onDamage = false;
			if (isPlayer) isUltimate = true;
		}
	}
}

void CharBase::UpdateDead()
{
	frame--;
	if (isPlayer) imgIdxY = 3;
	else imgIdxY = 7;

	if (frame < 0)
	{
		frame = Maxframe;
		if (imgIdxX < deadImgIdx - 1) imgIdxX++;
		else
		{
			onDamage = false;
			isDead = true;
		}
	}
}

void CharBase::Draw()
{
	DrawLifes();
	if (0 < ultimateTimer && ultimateTimer % 60 < 40)
	{
		DrawRectRotaGraphF(rect_.center.x, rect_.center.y,
			kImgWidth * imgIdxX, kImgHeight * imgIdxY,
			kImgWidth, kImgHeight,
			3, 0.0f,
			charHandle, true, handleTurn);
	}
#ifdef _DEBUG
	DrawBox(rect_.Left(), rect_.Top(), rect_.Right(), rect_.Bottom(), 0xffffff, false);
#endif
}

void CharBase::DrawLifes()
{
	if (level == Data::kLevelPractice) return;
	for (int i = 0; i < lifes; i++)
	{
		int lifePosY = lifesPosY + i * 75;
		DrawRotaGraph(lifesPosX, lifePosY,
			extRate, 0.0,
			lifeHandle, true);
	}
}

void CharBase::UpdateLife()
{
	if (level != 0)
	{
		if (0.6 < extRate) isEnlarge = false;
		if (extRate < 0.4) isEnlarge = true;

		if (isEnlarge) extRate += 0.01;
		else extRate -= 0.01;
	}
}
