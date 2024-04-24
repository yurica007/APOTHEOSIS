#include "ThunderShot.h"

namespace
{
	constexpr int kNormalImgWidth = 48;
	constexpr int kNormalImgHeight = 48;

	constexpr int kImpactImgWidth = 64;
	constexpr int kImpactImgHeight = 64;

	constexpr int KCollisionRangeWidth = 20;
	constexpr int KCollisionRangeHeight = 20;

	constexpr int kNormalImgIdx = 16;
	constexpr int kImpactImgIdx = 6;
}

void ThunderShot::SetInitializeData()
{
	rect_.center = {};
	rect_.size = { KCollisionRangeWidth, KCollisionRangeHeight };

	isAccelerat = true;
	isWidthLong = true;

	normalImgWidth = kNormalImgWidth;
	normalImgHeight = kNormalImgHeight;

	impactImgWidth = kImpactImgWidth;
	impactImgHeight = kImpactImgHeight;

	collisionRangeWidth = KCollisionRangeWidth;
	collisionRangeHeight = KCollisionRangeHeight;

	normalHandleName = L"Data/shot/ThunderShot.png";
	impactHandleName = L"Data/shot/ThunderImpact.png";

	normalImgIdx = KCollisionRangeWidth;
	impactImgIdx = KCollisionRangeHeight;
}
