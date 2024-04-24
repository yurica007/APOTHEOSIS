#include "IceShot.h"

namespace
{
	constexpr int kImgWidth = 128;
	constexpr int kImgHeight = 128;

	constexpr int KCollisionRangeWidth = 20;
	constexpr int KCollisionRangeHeight = 20;

	constexpr int kNormalImgIdx = 4;
	constexpr int kImpactImgIdx = 6;
}

void IceShot::SetInitializeData()
{
	rect_.center = {};
	rect_.size = { KCollisionRangeWidth,KCollisionRangeWidth };

	normalImgWidth = kImgWidth;
	normalImgHeight = kImgHeight;

	impactImgWidth = kImgWidth;
	impactImgHeight = kImgHeight;

	collisionRangeWidth = KCollisionRangeWidth;
	collisionRangeHeight = KCollisionRangeHeight;

	normalHandleName = L"Data/shot/IceShot.png";
	impactHandleName = L"Data/shot/IceImpact.png";

	normalImgIdx = kNormalImgIdx;
	impactImgIdx = kImpactImgIdx;
}
