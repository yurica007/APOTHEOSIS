#include "SceneResult.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "../InputState.h"
#include "../Font.h"
#include "../GameData.h"
#include <DxLib.h>

namespace
{
	constexpr int kImgWidth = 64;
	constexpr int kImgHeight = 64;

	constexpr int kImgIdx = 9;
	constexpr int kFrame = 20;
}

SceneResult::SceneResult(SceneManager& manager) :
	Scene(manager)
{
	rect_.center = { Data::kScreenWidth / 2, Data::kScreenHeight / 2 };
	rect_.size = { kImgWidth,kImgHeight };

	font_ = std::make_shared<Font>();
	font_->Load();
	font_->SetFontType(FontType::result);

	drawFunc_ = &SceneResult::DrawLose;

	backWinHandle = LoadGraph(L"Data/background/Cartoon_Forest_BG_02.png");
	backLoseHandle = LoadGraph(L"Data/background/Battleground4.png");
	drawFrame = kFrame;
}

SceneResult::~SceneResult()
{
	DeleteGraph(backWinHandle);
	DeleteGraph(backLoseHandle);
}

void SceneResult::Update(const InputState& input)
{
	if(isWin) drawFunc_ = &SceneResult::DrawWin;
	if (fadeValue < 255) resultTimer--;

	if (input.IsTriggered(InputType::select)) isEnd = true;
	if (isEnd || resultTimer < 0)
	{
		FadeOutUpdate();
		if (fadeValue < 255) return;

		SceneTitle* nextScene = new SceneTitle(manager_);
		if (isWin && level < Data::kLevelHard) nextScene->SetLevel(level + 1);
		else if (level == Data::kLevelHard) nextScene->SetLevel(Data::kLevelHard);
		else if (!isWin) nextScene->SetLevel(level);
		manager_.ChangeScene(nextScene);
		return;
	}
	else
	{
		FadeInUpdate();
		if (0 < fadeValue) return;
	}
}

void SceneResult::Draw()
{
	(this->*drawFunc_)();
	// ������`���摜�ƁA���łɕ`�悳��Ă���X�N���[���Ƃ̃u�����h�̎d�����w�肵�Ă���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	// ��ʑS�̂�^�����ɓh��Ԃ�
	DrawBox(0, 0, Data::kScreenWidth, Data::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneResult::SetLevel(int selectLevel)
{
	level = selectLevel;
}

void SceneResult::SetLesult(bool result)
{
	isWin = result;
}

void SceneResult::DrawWin()
{
	DrawBackGround(backWinHandle);

	int fontHandle = font_->GetFontType();
	int fontSize = font_->GetFontSize() * static_cast<int>(strlen("GAMECLEAR") / 2);
	
	DrawStringFToHandle(rect_.center.x - fontSize, rect_.center.y, L"GAMECLEAR", 0xffffff, fontHandle);
}

void SceneResult::DrawLose()
{
	DrawBackGround(backLoseHandle);

	int fontHandle = font_->GetFontType();
	int fontSize = font_->GetFontSize() * static_cast<int>(strlen("�����΂Ŏ���ł��܂���...") / 2);
	DrawStringFToHandle(rect_.center.x - fontSize, rect_.center.y, L"�����΂Ŏ���ł��܂���...", 0xffffff, fontHandle);
}
