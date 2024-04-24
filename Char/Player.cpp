#include "Player.h"
#include "../InputState.h"
#include "../GameData.h"

namespace
{
	constexpr float kNormalSpeed = 5.0f;

	constexpr float kPosX = 600.0f;

	constexpr int kIdelImgIdxWidth = 6;
	constexpr int kDamageImgIdxWidth = 4;
	constexpr int kDeadImgIdxWidth = 9;

	constexpr int KCollisionRangeWidth = 15;
	constexpr int KCollisionRangeHeight = 15;

	constexpr int kLifePosX = 75;
	constexpr int kLifePosY = 50;

	constexpr int kFrame = 10;
	constexpr int kUltimateTimer = 180;
}

void Player::SetInitializeData()
{
	rect_.center = { kPosX, Data::kPosCenterY };
	rect_.size = { KCollisionRangeWidth,KCollisionRangeHeight };

	charHandleName = L"Data/char/player.png";
	lifeHandleName = L"Data/icon/HeatFull.png";
	handleTurn = false;

#ifdef _DEBUG
	lifes = 2;
#else
	lifes = 4;
#endif
	lifesPosX = kLifePosX;
	lifesPosY = kLifePosY;

	idelImgIdx = kIdelImgIdxWidth;
	damageImgIdx = kDamageImgIdxWidth;
	deadImgIdx = kDeadImgIdxWidth;

	frame = kFrame;
	Maxframe = kFrame;
	isPlayer = true;
}

void Player::UpdateOrigin(const InputState& input)
{
	if (isUltimate) ultimateTimer--;
	if (ultimateTimer < 0)
	{
		ultimateTimer = kUltimateTimer;
		isUltimate = false;
	}
	
	Vector2 velocity = { 0.0f, 0.0f };
	
	if (input.IsPressed(InputType::left)) velocity.x = -kNormalSpeed;
	if (input.IsPressed(InputType::right)) velocity.x = kNormalSpeed;
	if (input.IsTriggered(InputType::up)) rect_.center.y -= Data::kMoveSpace;
	if (input.IsTriggered(InputType::down))rect_.center.y += Data::kMoveSpace;
	
	if (velocity.Length() > 0.0f) velocity.Nomalize();
	
	velocity *= kNormalSpeed;
	rect_.center += velocity;
	
	float lineRangeLeft = Data::kCenterX, lineRangeRight = (Data::kCenterX + Data::kMoveRange) - Data::kLineReduce * level;
	switch (level)
	{
	case Data::kLevelPractice:
		lineRangeLeft -= Data::kPracticeMoveRange;
		break;
	case Data::kLevelEasy:
		lineRangeLeft -= Data::kEasyMoveRange;
		break;
	default:
		lineRangeLeft -= Data::kNormalMoveRange;
		break;
	}
	if (rect_.center.x < lineRangeLeft) rect_.center.x = lineRangeLeft;
	if (lineRangeRight < rect_.center.x) rect_.center.x = lineRangeRight;
	if (rect_.center.y < Data::kCenterY) rect_.center.y = Data::kCenterY;
	if (Data::kScreenHeight - Data::kMoveSpace < rect_.center.y) rect_.center.y = Data::kScreenHeight - Data::kMoveSpace;
}
