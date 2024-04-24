#include "Shot.h"
#include "../GameData.h"
#include <DxLib.h>

constexpr int kImgWidth = 96;
constexpr int kImgHeight = 96;
constexpr int kNormalImgIdx = 9;
constexpr int kImpactImgIdx = 7;

constexpr int KCollisionRangeWidth = 55;
constexpr int KCollisionRangeHeight = 45;

constexpr int kFrame = 10;

Shot::Shot() : vel_(15.0f, 0.0f)
{
	rect_.center = {};
	rect_.size = { KCollisionRangeWidth, KCollisionRangeHeight };

	updateFunc_ = &Shot::UpdateNormal;
	drawFunc_ = &Shot::DrawNormal;

	normalHandle = LoadGraph(L"Data/shot/Shot.png");
	impactHandle = LoadGraph(L"Data/shot/ShotImpact.png");
	frame = kFrame;
}

const Rect& Shot::GetRect() const
{
	return rect_;
}

void Shot::Impact()
{
	updateFunc_ = &Shot::UpdateImpact;
	drawFunc_ = &Shot::DrawImpact;
	imgIdx = 0;
	isEnable = false;
	isImpact = true;
}

void Shot::Fire(const Position2& pos)
{
	rect_.center = pos;
	isEnable = true;
}

bool Shot::IsEnable()
{
	return isEnable;
}

bool Shot::IsFire()
{
	if (!isEnable && !isImpact) return true;
	else return false;
}

void Shot::Update()
{
	(this->*updateFunc_)();
	if (Data::kScreenWidth < rect_.center.x)
	{
		imgIdx = 0;
		isEnable = false;
	}
}

void Shot::UpdateNormal()
{
	if (!isEnable) return;
	frame--;
	if (frame < 0)
	{
		frame = kFrame;
		if (imgIdx < kNormalImgIdx - 1) imgIdx++;
		else imgIdx = 0;
	}
	rect_.center += vel_;
}

void Shot::UpdateImpact()
{
	frame--;
	if (frame < 0)
	{
		frame = kFrame;
		if (imgIdx < kImpactImgIdx - 1) imgIdx++;
		else
		{
			updateFunc_ = &Shot::UpdateNormal;
			drawFunc_ = &Shot::DrawNormal;
			imgIdx = 0;
			isImpact = false;
		}
	}
}

void Shot::Draw()
{
	(this->*drawFunc_)();
}

void Shot::DrawNormal()
{
	if (!isEnable) return;
	DrawRectRotaGraphF(rect_.center.x, rect_.center.y,
		kImgWidth * imgIdx, 0,
		kImgWidth, kImgHeight,
		Data::kShotEnlargeRate, 0.0f,
		normalHandle, true);
#ifdef _DEBUG
	DrawBox(rect_.Left(), rect_.Top(), rect_.Right(), rect_.Bottom(), 0xffffff, false);
#endif
}

void Shot::DrawImpact()
{
	DrawRectRotaGraphF(rect_.center.x, rect_.center.y,
		0, kImgHeight * imgIdx,
		kImgWidth, kImgHeight,
		Data::kShotEnlargeRate, 0.0f,
		impactHandle, true);
#ifdef _DEBUG
	DrawBox(rect_.Left(), rect_.Top(), rect_.Right(), rect_.Bottom(), 0xffffff, false);
#endif
}
