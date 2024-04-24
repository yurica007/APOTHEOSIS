#pragma once
#include "Geometry.h"
#include <memory>

class Font;

class Operate
{
public:
	Operate();
	~Operate();

	void UpdateOperateTitle();
	void UpdateOperateGame();

	void DrawOperateTitle(bool isSelectLevel);
	void DrawOperateGame();

private:
	std::shared_ptr<Font> font_;

	int fontHandle;

	int cursorFrameTimer;
	int buttonFrameTimer;

	int upDownImgIdx = 0;
	int leftRightImgIdx = 0;
	int buttonImgIdx = 0;

	int frameTimer = 30;
	int skipTimer = 300;

	int optionCursor;
	int optionButton;

	int lineFrame = 0;
	int redLine = 0;
};

