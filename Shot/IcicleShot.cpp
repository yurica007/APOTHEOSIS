#include "IcicleShot.h"

namespace
{
	constexpr int kImgWidth = 32;
	constexpr int kImgHeight = 48;

	constexpr int KCollisionRangeWidth = 10;
	constexpr int KCollisionRangeHeight = 25;

	constexpr int kNormalImgIdx = 10;
	constexpr int kImpactImgIdx = 8;
}

void IcicleShot::SetInitializeData()
{
	rect_.center = { 0.0f, -KCollisionRangeHeight };
	rect_.size = { KCollisionRangeWidth,KCollisionRangeHeight };

	normalImgWidth = kImgWidth;
	normalImgHeight = kImgHeight;

	impactImgWidth = kImgWidth;
	impactImgHeight = kImgHeight;

	collisionRangeWidth = KCollisionRangeWidth;
	collisionRangeHeight = KCollisionRangeHeight;

	normalHandleName = L"Data/shot/IcicleNormal.png";
	impactHandleName = L"Data/shot/IcicleImpact.png";

	normalImgIdx = kNormalImgIdx;
	impactImgIdx = kImpactImgIdx;
}
