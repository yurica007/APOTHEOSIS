#include "Enemy.h"
#include "../GameData.h"
#include <DxLib.h>

namespace
{
	constexpr float kPosX = Data::kCenterX + Data::kLineRange;
	constexpr float kMoveSpeed = 3.0f;

	constexpr int kIdelImgIdxWidth = 2;
	constexpr int kDamageImgIdxWidth = 3;
	constexpr int kDeadImgIdxWidth = 8;

	constexpr int kCollisionRangeWidth = 60;
	constexpr int kCollisionRangeHeight = 80;

	constexpr int kLifePosX = Data::kScreenWidth - 75;
	constexpr int kLifePosY = 50;

	constexpr int kFrame = 30;
}

void Enemy::SetInitializeData()
{
	rect_.center = { kPosX, Data::kPosCenterY };
	rect_.size = { kCollisionRangeWidth,kCollisionRangeHeight };
	destinationRect_.center = rect_.center;

	charHandleName = L"Data/char/enemy.png";
	lifeHandleName = L"Data/icon/HeatFull.png";
	handleTurn = true;

#ifdef _DEBUG
	lifes = 3;
#else
	lifes = 6;
#endif
	lifesPosX = kLifePosX;
	lifesPosY = kLifePosY;

	idelImgIdx = kIdelImgIdxWidth;
	damageImgIdx = kDamageImgIdxWidth;
	deadImgIdx = kDeadImgIdxWidth;

	frame = kFrame;
	Maxframe = kFrame;
	isPlayer = false;
}

void Enemy::UpdateOrigin(const InputState& input)
{
	if (moveFrame < 0)
	{
		destinationRect_.center.y = (GetRand(Data::kMoveLine - 1) - 2) * Data::kMoveSpace + Data::kPosCenterY;
		linePosY = destinationRect_.center.y;
		moveFrame = 60;
	}
		
	Vector2 vel_ = destinationRect_.center - rect_.center;
		
	if (vel_.Length() < kMoveSpeed)
	{
		rect_.center = destinationRect_.center;
		moveFrame--;
		return;
	}
		
	if (0.0f != vel_.Length()) vel_.Nomalize();
		
	rect_.center += vel_ * kMoveSpeed;
}

const float Enemy::GetPosLine() const
{
	return linePosY;
}