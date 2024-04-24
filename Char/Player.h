#pragma once
#include "CharBase.h"

class InputState;

class Player :
	public CharBase
{
public:
	Player() {}
	~Player() {}

	void SetInitializeData();
	void UpdateOrigin(const InputState& input);
};

