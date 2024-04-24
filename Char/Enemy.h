#pragma once
#include "CharBase.h"
#include "../Geometry.h"

class InputState;

class Enemy :
	public CharBase
{
public:
	Enemy() {}
	~Enemy() {}

	void SetInitializeData();
	void UpdateOrigin(const InputState& input);

	const float GetPosLine() const;

private:
	Rect destinationRect_ = rect_;
	float linePosY = 0.0f;
	int moveFrame = 60;
};

