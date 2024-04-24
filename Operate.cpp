#include "Operate.h"
#include "GameData.h"
#include "Font.h"
#include <DxLib.h>

constexpr int kCursorImgWidth = 32;
constexpr int kCursorImgHeight = 32;
constexpr int kButtomImgWidth = 16;
constexpr int kButtomImgHeight = 16;

constexpr int kUpDownImgIdx = 3;
constexpr int kLeftRightImgIdx = 5;
constexpr int kButtomImgIdxWidth = 5;
constexpr int kButtomImgIdxHeight = 4;

constexpr int kCursorFrameTimer = 60;
constexpr int kButtonFrameTimer = 60;

constexpr int kLineNum = 3;
constexpr int kLineFrame = 30;

Operate::Operate()
{
	font_ = std::make_shared<Font>();
	font_->Load();
	font_->SetFontType(FontType::operate);

	fontHandle = font_->GetFontType();

	cursorFrameTimer = kCursorFrameTimer;
	buttonFrameTimer = kButtonFrameTimer;

	optionCursor = LoadGraph(L"Data/padCursor.png");
	optionButton = LoadGraph(L"Data/padButton.png");
}

Operate::~Operate()
{
	font_->Delete();
	DeleteGraph(optionButton);
	DeleteGraph(optionCursor);
}

void Operate::UpdateOperateTitle()
{
	cursorFrameTimer--;
	buttonFrameTimer--;

	if (cursorFrameTimer < 0)
	{
		cursorFrameTimer = kCursorFrameTimer;
		if (upDownImgIdx < kUpDownImgIdx - 1) upDownImgIdx++;
		else upDownImgIdx = 0;
	}

	if (buttonFrameTimer < 0)
	{
		buttonFrameTimer = kButtonFrameTimer;
		if (buttonImgIdx < kButtomImgIdxWidth - 1) buttonImgIdx++;
		else buttonImgIdx = 0;
	}
}

void Operate::UpdateOperateGame()
{
	cursorFrameTimer--;
	buttonFrameTimer--;
	
	if (cursorFrameTimer < 0)
	{
		cursorFrameTimer = kCursorFrameTimer;
		if (upDownImgIdx < kUpDownImgIdx - 1) upDownImgIdx++;
		else upDownImgIdx = 0;

		if (leftRightImgIdx < kLeftRightImgIdx - 1) leftRightImgIdx++;
		else leftRightImgIdx = 0;
		if (leftRightImgIdx != 0 && leftRightImgIdx < kUpDownImgIdx) leftRightImgIdx = kUpDownImgIdx;
	}

	if (buttonFrameTimer < 0)
	{
		buttonFrameTimer = kButtonFrameTimer;
		if (buttonImgIdx < kButtomImgIdxWidth - 1) buttonImgIdx++;
		else buttonImgIdx = 0;
	}
}

void Operate::DrawOperateTitle(bool isSelectLevel)
{
	Rect upDownCursorRect_;
	Rect cursorOperateRect_;
	const float cursorCenterX = Data::kCenterX - 200.0f;
	const float cursorCenterY = 775.0f;

	upDownCursorRect_.center = { cursorCenterX, cursorCenterY };
	cursorOperateRect_.center = upDownCursorRect_.center + Position2{ 50.0f, -10.0f };

	DrawRectRotaGraphF(upDownCursorRect_.center.x, upDownCursorRect_.center.y,
		kCursorImgWidth * upDownImgIdx, 0,
		kCursorImgWidth, kCursorImgHeight,
		3, 0.0f,
		optionCursor, true);
	DrawStringFToHandle(cursorOperateRect_.center.x, cursorOperateRect_.center.y, L"カーソル移動", 0xffffff, fontHandle);

	Rect buttonRect_;
	Rect ButtonOperateRect_;
	const float buttonCenterX = Data::kCenterX + 200.0f;
	const float buttonCenterY = 775.0f;
	const float buttonSpace = 30.0f;

	for (int imgIdxY = 0; imgIdxY < kButtomImgIdxHeight; imgIdxY++)
	{
		int imgIdxX = 2;
		if (imgIdxY == 0) buttonRect_.center = { buttonCenterX - buttonSpace, buttonCenterY };
		if (imgIdxY == 1)
		{
			buttonRect_.center = { buttonCenterX, buttonCenterY + buttonSpace };
			ButtonOperateRect_.center = buttonRect_.center + Position2{ -static_cast<float>(font_->GetFontSize() * (strlen("キャンセル") / 2)), 30.0f};
			if (isSelectLevel)
			{
				imgIdxX = buttonImgIdx;
				DrawStringFToHandle(ButtonOperateRect_.center.x, ButtonOperateRect_.center.y, L"キャンセル", 0xffffff, fontHandle);
			}
		}
		if (imgIdxY == 2) buttonRect_.center = { buttonCenterX, buttonCenterY - buttonSpace };
		if (imgIdxY == 3)
		{
			buttonRect_.center = { buttonCenterX + buttonSpace, buttonCenterY };
			ButtonOperateRect_.center = buttonRect_.center + Position2{ 30.0f, -10.0f };
			imgIdxX = buttonImgIdx;
			DrawStringFToHandle(ButtonOperateRect_.center.x, ButtonOperateRect_.center.y, L"決定", 0xffffff, fontHandle);
		}

		DrawRectRotaGraphF(buttonRect_.center.x, buttonRect_.center.y,
			kButtomImgWidth * imgIdxX, kButtomImgHeight * imgIdxY,
			kButtomImgWidth, kButtomImgHeight,
			2, 0.0f,
			optionButton, true);
	}
}

void Operate::DrawOperateGame()
{
	const int operateWidth = 150;
	const int operateHeight = 60;

	// 今から描く画像と、すでに描画されているスクリーンとのブレンドの仕方を指定している
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	// 画面全体を真っ黒に塗りつぶす
	DrawBoxAA(operateWidth, operateHeight, Data::kScreenWidth - operateWidth, Data::kCenterY - operateHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	frameTimer--;
	skipTimer--;
	if (frameTimer < -30)frameTimer = 30;
	if(frameTimer < 0) DrawStringToHandle(10, 10, L"操作確認",0xffffff , fontHandle);

	Rect upDownCursorRect_;
	Rect upDownCursorOperateRect_;
	const float cursorSpace = 110.0f;
	const float cursorCenterX = 300.0f;
	const float cursorCenterY = operateHeight + cursorSpace;

	upDownCursorRect_.center = { cursorCenterX, cursorCenterY };
	upDownCursorOperateRect_.center = upDownCursorRect_.center + Position2{ 50.0f, -10.0f };

	DrawRectRotaGraphF(upDownCursorRect_.center.x, upDownCursorRect_.center.y,
		kCursorImgWidth * upDownImgIdx, 0,
		kCursorImgWidth, kCursorImgHeight,
		3, 0.0f,
		optionCursor, true);
	DrawStringFToHandle(upDownCursorOperateRect_.center.x, upDownCursorOperateRect_.center.y, L"レーン移動", 0xffffff, fontHandle);

	Rect leftRightCursorRect_;
	Rect leftRightCursorOperateRect_;
	leftRightCursorRect_.center = upDownCursorRect_.center + Position2{ 0.0f,cursorSpace };
	leftRightCursorOperateRect_.center = leftRightCursorRect_.center + Position2{ 50.0f, -10.0f };

	DrawRectRotaGraphF(leftRightCursorRect_.center.x, leftRightCursorRect_.center.y,
		kCursorImgWidth * leftRightImgIdx, 0,
		kCursorImgWidth, kCursorImgHeight,
		3, 0.0f,
		optionCursor, true);
	DrawStringFToHandle(leftRightCursorOperateRect_.center.x, leftRightCursorOperateRect_.center.y, L"前後移動", 0xffffff, fontHandle);

	Rect buttonRect_;
	Rect buttonOperateRect_;
	const float buttonCenterX = 600.0f;
	const float buttonCenterY = 225.0f;
	const float buttonSpace = 30.0f;

	for (int imgIdxY = 0; imgIdxY < kButtomImgIdxHeight; imgIdxY++)
	{
		int imgIdxX = 2;
		if (imgIdxY == 0) buttonRect_.center = { buttonCenterX - buttonSpace, buttonCenterY };
		if (imgIdxY == 1)
		{
			buttonRect_.center = { buttonCenterX, buttonCenterY + buttonSpace };
			if (skipTimer < 0)
			{
				skipTimer = -1;
				imgIdxX = buttonImgIdx;
				if (frameTimer < 0)
				{
					buttonOperateRect_.center = buttonRect_.center + Position2{ -static_cast<float>(font_->GetFontSize() * (strlen("スキップ") / 2)), 30.0f };
					DrawStringFToHandle(buttonOperateRect_.center.x, buttonOperateRect_.center.y, L"スキップ", 0xffffff, fontHandle);
				}
			}
		}
		if (imgIdxY == 2) buttonRect_.center = { buttonCenterX, buttonCenterY - buttonSpace };
		if (imgIdxY == 3)
		{
			buttonRect_.center = { buttonCenterX + buttonSpace, buttonCenterY };
			buttonOperateRect_.center = buttonRect_.center + Position2{ 30.0f, -10.0f };
			imgIdxX = buttonImgIdx;
			DrawStringFToHandle(buttonOperateRect_.center.x, buttonOperateRect_.center.y, L"弾発射", 0xffffff, fontHandle);
		}

		DrawRectRotaGraphF(buttonRect_.center.x, buttonRect_.center.y,
			kButtomImgWidth * imgIdxX, kButtomImgHeight * imgIdxY,
			kButtomImgWidth, kButtomImgHeight,
			2, 0.0f,
			optionButton, true);
	}

	const float lineCenterX = Data::kCenterX + 200.0f;
	const float lineRange = 200.0f;
	float lineY = 150.0f;
	const float lineSpace = 50.0f;
	
	int color = 0xffffff;
	lineFrame--;

	for (int i = 0; i < kLineNum; i++)
	{
		if (lineFrame < 0)
		{
			lineFrame = kLineFrame;
			redLine++;
		}
		if (redLine > kLineNum - 1) redLine = 0;
		if (redLine == i) color = 0xff0000;
		else color = 0xffffff;

		DrawLine(lineCenterX - lineRange, lineY + i * lineSpace, lineCenterX + lineRange, lineY + i * lineSpace, color);
	}
	int fontSize = font_->GetFontSize() * GetStringLength(L"赤は敵の移動先を表示");
	DrawStringToHandle(lineCenterX - fontSize, 300, L"赤は敵の移動先を表示", 0xffffff, fontHandle);
}