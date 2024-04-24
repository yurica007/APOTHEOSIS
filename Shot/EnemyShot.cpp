#include "EnemyShot.h"
#include "../GameData.h"
#include <DxLib.h>

namespace
{
	constexpr int kFrame = 20;
}

EnemyShot::EnemyShot()
{
	updateFunc_ = &EnemyShot::UpdateNormal;
	drawFunc_ = &EnemyShot::DrawNormal;

	normalHandle = -1;
	impactHandle = -1;
	normalHandleName = 0;
	impactHandleName = 0;

	frame = kFrame;
}

EnemyShot::~EnemyShot()
{
	DeleteGraph(normalHandle);
	DeleteGraph(impactHandle);
}

void EnemyShot::Fire(const Position2& pos, const Vector2& vel)
{
	rect_.center = pos;
	vel_ = vel;
	isEnable = true;
}

const Rect& EnemyShot::GetRect() const
{
	return rect_;
}

void EnemyShot::Init()
{
	SetInitializeData();

	updateFunc_ = &EnemyShot::UpdateNormal;
	drawFunc_ = &EnemyShot::DrawNormal;

	normalHandle = LoadGraph(normalHandleName);
	impactHandle = LoadGraph(impactHandleName);

	frame = kFrame;
}

void EnemyShot::Impact()
{
	updateFunc_ = &EnemyShot::UpdateImpact;
	drawFunc_ = &EnemyShot::DrawImpact;
	imgIdxX = 0;
	imgIdxY = 0;
	isEnable = false;
	isImpact = true;
}

void EnemyShot::Update()
{
	(this->*updateFunc_)();
	isCollision = true;
	if (rect_.center.x < 0 || Data::kScreenHeight < rect_.center.y - collisionRangeHeight)
	{
		imgIdxX = 0;
		imgIdxY = 0;
		isEnable = false;
	}
}

void EnemyShot::Draw()
{
	(this->*drawFunc_)();
#ifdef _DEBUG
	DrawBox(rect_.Left(), rect_.Top(), rect_.Right(), rect_.Bottom(), 0xffffff, false);
#endif
}


void EnemyShot::UpdateNormal()
{
	if (!isEnable) return;
	frame--;
	if (frame < 0)
	{
		frame = kFrame;
		if (isWidthLong)
		{
			if (imgIdxX < normalImgIdx - 1) imgIdxX++;
			else imgIdxX = 0;
		}
		else
		{
			if (imgIdxY < normalImgIdx - 1) imgIdxY++;
			else imgIdxY = 0;
		}
		
	}
	if (isAccelerat) vel_.x -= 0.1f;
	rect_.center += vel_;
}

void EnemyShot::UpdateImpact()
{
	frame--;
	if (frame < 0)
	{
		frame = kFrame;
		if (isWidthLong)
		{
			if (imgIdxX < impactImgIdx - 1) imgIdxX++;
			else
			{
				FinishImpact();
				imgIdxX = 0;
			}
		}
		else
		{
			if (imgIdxY < impactImgIdx - 1) imgIdxY++;
			else
			{
				FinishImpact();
				imgIdxY = 0;
			}
		}
	}
}

void EnemyShot::DrawNormal()
{
	DrawRectRotaGraphF(rect_.center.x, rect_.center.y,
		normalImgWidth * imgIdxX, normalImgHeight * imgIdxY,
		normalImgWidth, normalImgHeight,
		1.0, 0.0f,
		normalHandle, true, true);
}

void EnemyShot::DrawImpact()
{
	DrawRectRotaGraphF(rect_.center.x, rect_.center.y,
		impactImgWidth * imgIdxX, normalImgHeight * imgIdxY,
		impactImgWidth, impactImgHeight,
		1.0, 0.0f,
		impactHandle, true, true);
}

void EnemyShot::FinishImpact()
{
	rect_.center = { 0.0f, static_cast<float>(-collisionRangeHeight) };
	updateFunc_ = &EnemyShot::UpdateNormal;
	drawFunc_ = &EnemyShot::DrawNormal;
	isImpact = false;
}

bool EnemyShot::IsEnable() const
{
	return isEnable;
}

void EnemyShot::Delete()
{
	isEnable = false;
}

bool EnemyShot::IsFire() const
{
	if (!isEnable && !isImpact) return true;
	else return false;
}

bool EnemyShot::IsCollision() const
{
	if (isEnable && isCollision) return true;
	else return false;
}