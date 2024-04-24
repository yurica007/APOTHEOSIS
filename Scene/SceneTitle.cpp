#include "SceneTitle.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "../InputState.h"
#include "../Operate.h"
#include "../Font.h"
#include "../GameData.h"
#include <DxLib.h>

namespace
{
	constexpr int kMenuPosX = Data::kScreenWidth / 2;
	constexpr int kMenuPosY = Data::kScreenHeight / 2 + 100;
	constexpr int kLevelPosY = 400;
	constexpr int kMenuSpace = 55;
	constexpr int kSelectMenuPosX = kMenuPosX - 50;

	constexpr int kCursorImgWidth = 64;
	constexpr int kCursorImgHeight = 64;
	constexpr int kCursorImgIdx = 6;

	constexpr int kCharImgWidth = 32;
	constexpr int kCharImgHeight = 32;
	constexpr int kPlayerImgIdx = 6;
	constexpr int kEnemyImgIdx = 2;

	constexpr int kCursorSpaceX = 30;
	constexpr int kCursorSpaceY = 20;

	constexpr int kPlayerAnimFrame = 10;
	constexpr int kEnemyAnimFrame = 20;
	constexpr int kSelectColor = 0xffffff;
	constexpr int kNormalColor = 0x666666;
}

SceneTitle::SceneTitle(SceneManager& manager) :
	Scene(manager)
{
	menuCursorRect_.center = {};
	levelCursorRect_ = menuCursorRect_;

	menu_[Menu::start] = L"ゲーム開始";
	menu_[Menu::level] = L"難易度変更";

	level_[Level::practice] = L"練習";
	level_[Level::easy] = L"初級";
	level_[Level::normal] = L"中級";
	level_[Level::hard] = L"上級";

	operate_ = std::make_shared<Operate>();
	font_ = std::make_shared<Font>();
	font_->Load();

	updateFunc_ = &SceneTitle::UpdateNormal;
	drawFunc_ = &SceneTitle::DrawNormal;
	
	backHandle = LoadGraph(L"Data/background/Battleground3.png");
	playerHandle = LoadGraph(L"Data/char/player.png");
	enemyHandle = LoadGraph(L"Data/char/enemy.png");
	cursorHandle = LoadGraph(L"Data/icon/Cursor.png");
	selectHandle = LoadGraph(L"Data/icon/Select.png");

	frame = kPlayerAnimFrame;
	playerAnimFrame = kPlayerAnimFrame;
	enemyAnimFrame = kEnemyAnimFrame;
}

SceneTitle::~SceneTitle()
{
	font_->Delete();
	DeleteGraph(backHandle);
	DeleteGraph(cursorHandle);
	DeleteGraph(selectHandle);
}

void SceneTitle::Update(const InputState& input)
{
	operate_->UpdateOperateTitle();
	(this->*updateFunc_)(input);
	UpdateChar();
}

void SceneTitle::Draw()
{
	DrawBackGround(backHandle);
	operate_->DrawOperateTitle(selectLevel);
	(this->*drawFunc_)();
	DrawChar();

	// 今から描く画像と、すでに描画されているスクリーンとのブレンドの仕方を指定している
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	// 画面全体を真っ黒に塗りつぶす
	DrawBox(0, 0, Data::kScreenWidth, Data::kScreenHeight , 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::SetLevel(int selectLevel)
{
	currentLevel = selectLevel;
}

void SceneTitle::UpdateCursor()
{
	frame--;
	if (frame < 0)
	{
		frame = kPlayerAnimFrame;
		if (cursorImgIdx < kCursorImgIdx - 1) cursorImgIdx++;
		else cursorImgIdx = 0;
	}
}

void SceneTitle::UpdateNormal(const InputState& input)
{
	FadeInUpdate();
	UpdateCursor();
	if (0 < fadeValue) return;
	const int menuCount = static_cast<int>(menu_.size());
	if (!selectStart && !selectLevel)
	{
		if (input.IsTriggered(InputType::up)) menuIndex = ((menuIndex - 1) + menuCount) % menuCount;
		if (input.IsTriggered(InputType::down)) menuIndex = (menuIndex + 1) % menuCount;
		if (input.IsTriggered(InputType::select) && menuIndex == static_cast<int>(Menu::start))
		{
			updateFunc_ = &SceneTitle::UpdateSelectStart;
			drawFunc_ = &SceneTitle::DrawSelectStart;
			selectStart = true;
			frame = kPlayerAnimFrame;
			cursorImgIdx = 0;
			DeleteGraph(cursorHandle);
		}
		if (input.IsTriggered(InputType::select) && menuIndex == static_cast<int>(Menu::level))
		{
			updateFunc_ = &SceneTitle::UpdateSelectLevel;
			drawFunc_ = &SceneTitle::DrawSelectLevel;
			selectLevel = true;
		}
	}
}

void SceneTitle::UpdateSelectStart(const InputState& input)
{
	if (cursorImgIdx == kCursorImgIdx)
	{
		FadeOutUpdate();
		if (fadeValue < 255) return;

		SceneGame *nextScene = new SceneGame(manager_);
		nextScene->SetLevel(currentLevel);
		manager_.ChangeScene(nextScene);
		selectStart = false;
		return;
	}
	else
	{
		frame--;
		if (frame < 0)
		{
			frame = kPlayerAnimFrame;
			if (cursorImgIdx < kCursorImgIdx - 1) cursorImgIdx++;
			else cursorImgIdx = kCursorImgIdx;
		}
	}
}

void SceneTitle::UpdateSelectLevel(const InputState& input)
{
	const int difficultyCount = static_cast<int>(level_.size());
	if (input.IsTriggered(InputType::up)) levelIndex = ((levelIndex - 1) + difficultyCount) % difficultyCount;
	if (input.IsTriggered(InputType::down)) levelIndex = (levelIndex + 1) % difficultyCount;

	bool selectPractice = input.IsTriggered(InputType::select) && levelIndex == static_cast<int>(Level::practice);
	bool selectEasy = input.IsTriggered(InputType::select) && levelIndex == static_cast<int>(Level::easy);
	bool selectNormal = input.IsTriggered(InputType::select) && levelIndex == static_cast<int>(Level::normal);
	bool selectHard = input.IsTriggered(InputType::select) && levelIndex == static_cast<int>(Level::hard);

	if (selectPractice || selectEasy || selectNormal || selectHard) currentLevel = levelIndex;

	if (input.IsTriggered(InputType::cancel) ||
		selectPractice || selectEasy || selectNormal || selectHard)
	{
		updateFunc_ = &SceneTitle::UpdateNormal;
		drawFunc_ = &SceneTitle::DrawNormal;
		levelIndex = currentLevel;
		selectLevel = false;
	}
	UpdateCursor();	
}

void SceneTitle::UpdateChar()
{
	playerAnimFrame--;
	if (playerAnimFrame < 0)
	{
		playerAnimFrame = kPlayerAnimFrame;
		if (playerImgIdx < kPlayerImgIdx - 1) playerImgIdx++;
		else playerImgIdx = 0;
	}
	enemyAnimFrame--;
	if (enemyAnimFrame < 0)
	{
		enemyAnimFrame = kEnemyAnimFrame;
		if (enemyImgIdx < kEnemyImgIdx - 1) enemyImgIdx++;
		else enemyImgIdx = 0;
	}

}

void SceneTitle::DrawMenu()
{
	font_->SetFontType(FontType::title);
	int fontHandle = font_->GetFontType();
	int fontSize = font_->GetFontSize() * (GetStringLength(L"APOTHEOSIS") / 2);

	int posX = Data::kScreenWidth / 2 - fontSize, posY = 400;
	DrawStringToHandle(posX, posY, L"APOTHEOSIS", 0xffffff, fontHandle);

	font_->SetFontType(FontType::menu);
	int i = 0, menuPosX = kMenuPosX, color;

	for (auto& menu : menu_)
	{
		if (menuIndex == i)
		{
			menuPosX = kSelectMenuPosX;
			color = kSelectColor;
		}
		else
		{
			menuPosX = kMenuPosX;
			color = kNormalColor;
		}
		int fontHandle = font_->GetFontType();
		int fontSize = font_->GetFontSize() * static_cast<int>(menu.second.size());

		menuCursorRect_.center.x = static_cast<float>(kSelectMenuPosX - fontSize - kCursorSpaceX);
		DrawStringToHandle(menuPosX - fontSize, kMenuPosY + i * kMenuSpace, menu.second.c_str(), color, fontHandle);
		i++;
	}
}

void SceneTitle::DrawNormal()
{
	if (!selectLevel)
	{
		DrawMenu();
		menuCursorRect_.center.y = static_cast<float>(kMenuPosY + kCursorSpaceY + menuIndex * kMenuSpace);

		DrawFunction(menuCursorRect_, kCursorImgWidth, kCursorImgHeight, cursorImgIdx, 0, 2.0, cursorHandle, false);
	}
}

void SceneTitle::DrawSelectStart()
{
	DrawMenu();
	DrawFunction(menuCursorRect_, kCursorImgWidth, kCursorImgHeight, 0, cursorImgIdx, 2.0, selectHandle, false);
}

void SceneTitle::DrawSelectLevel()
{
	int i = 0, levelPosX = kMenuPosX, color = kNormalColor;
	for (auto& level : level_)
	{
		if (levelIndex == i)
		{
			levelPosX = kSelectMenuPosX;
			color = kSelectColor;
		}
		else
		{
			levelPosX = kMenuPosX;
			color = kNormalColor;
		}
		font_->SetFontType(FontType::menu);
		int fontHandle = font_->GetFontType();
		int fontSize = font_->GetFontSize() * static_cast<int>(level.second.size());
		levelCursorRect_.center.x = static_cast<float>(kSelectMenuPosX - fontSize - kCursorSpaceX);

		int posX = levelPosX - fontSize, posY = kLevelPosY + i * kMenuSpace;
		DrawStringToHandle(posX, posY, level.second.c_str(), color, fontHandle);

		if (currentLevel == static_cast<int>(level.first))
		{
			fontSize = font_->GetFontSize() * static_cast<int>((strlen("現在の難易度") + 2) / 2 + level.second.size());
			DrawFormatStringToHandle(kMenuPosX - fontSize, 650, 0xffffff, fontHandle, L"現在の難易度：%s", level.second.c_str());
		}
		i++;
	}
	levelCursorRect_.center.y = static_cast<float>(kLevelPosY + kCursorSpaceY + levelIndex * kMenuSpace);
	DrawFunction(levelCursorRect_, kCursorImgWidth, kCursorImgHeight, cursorImgIdx, 0, 2.0, cursorHandle, false);

	DrawLevelComment();
}

void SceneTitle::DrawChar()
{
	Rect playerRect_;
	playerRect_.center = { Data::kCenterX - 400.0f, 650.0f };
	
	DrawFunction(playerRect_, kCharImgWidth, kCharImgHeight, playerImgIdx, 0, 3.0, playerHandle, false);

	Rect enemyRect_;
	enemyRect_.center = { Data::kCenterX + 400.0f, 650.0f };

	DrawFunction(enemyRect_, kCharImgWidth, kCharImgHeight, enemyImgIdx, 0, 3.0, enemyHandle, true);
}

void SceneTitle::DrawLevelComment()
{
	font_->SetFontType(FontType::comment);
	int fontHandle = font_->GetFontType();

	switch (levelIndex)
	{
	case Data::kLevelPractice:
		DrawStringToHandle(900, kLevelPosY + levelIndex * kMenuSpace + 15, L"操作方法の確認ができる", 0xffffff, fontHandle);
		break;
	case Data::kLevelEasy:
		DrawStringToHandle(900, kLevelPosY + levelIndex * kMenuSpace + 15, L"敵の弾数が増える", 0xffffff, fontHandle);
		break;
	case Data::kLevelNormal:
		DrawStringToHandle(900, kLevelPosY + levelIndex * kMenuSpace + 15, L"敵の弾速が上がる", 0xffffff, fontHandle);
		break;
	case Data::kLevelHard:
		DrawStringToHandle(900, kLevelPosY + levelIndex * kMenuSpace + 15, L"敵の弾速が徐々に上がる", 0xffffff, fontHandle);
		break;
	}
}
