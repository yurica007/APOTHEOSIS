#include "SceneGame.h"
#include "SceneManager.h"
#include "SceneResult.h"
#include "../Char/Player.h"
#include "../Char/Enemy.h"
#include "../Operate.h"
#include "../Shot/Shot.h"
#include "../Shot/IceShot.h"
#include "../Shot/ThunderShot.h"
#include "../Shot/IcicleShot.h"
#include "../InputState.h"
#include "../GameData.h"
#include <DxLib.h>

namespace
{
	constexpr int kLevelEasyShotInterval = 60;
	constexpr int kLevelNormalShotInterval = 15;
	constexpr int kLevelHardShotInterval = 20;
}

SceneGame::SceneGame(SceneManager& manager) :
	Scene(manager)
{
	player_ = std::make_shared<Player>();
	player_->Init();
	enemy_ = std::make_shared<Enemy>();
	enemy_->Init();
	operate_ = std::make_shared<Operate>();

	shot_ = std::make_shared<Shot>();

	iceShot_ = std::make_shared<IceShot>();
	iceShot_->Init();
	thunderShot_ = std::make_shared<ThunderShot>();
	thunderShot_->Init();
	for (auto& icicleShot : icicleShot_)
	{
		icicleShot = std::make_shared<IcicleShot>();
		icicleShot->Init();
	}

	updateLevelFunc_ = &SceneGame::UpdateLevelEasy;
	drawLevelFunc_ = &SceneGame::DrawLevelEasy;

	levelHardInterval = kLevelHardShotInterval;
	
	screenHandle = MakeScreen(Data::kScreenWidth, Data::kScreenHeight, true);
	backHandle = LoadGraph(L"Data/background/Battleground1.png");
}

SceneGame::~SceneGame()
{
	DeleteGraph(backHandle);
}

void SceneGame::Update(const InputState& input)
{
	player_->SetLevel(level);
	enemy_->SetLevel(level);
	player_->Update(input);
	enemy_->Update(input);

	if (!player_->IsEnable() && !enemy_->IsEnable())
	{
		//弾の発射処理
		if (input.IsTriggered(InputType::shot))
		{
			if (shot_->IsFire())
			{
				shot_->Fire(player_->GetPosition());
			}
		}
	}
	shot_->Update();
	if (shot_->IsEnable())
	{
		if (shot_->GetRect().IsHit(enemy_->GetRect()))
		{
			shot_->Impact();
			enemy_->OnDamage();
		}
	}

	switch (level)
	{
	case Data::kLevelPractice:
		updateLevelFunc_ = &SceneGame::UpdateLevelPractice;
		drawLevelFunc_ = &SceneGame::DrawLevelPractice;
		break;
	case Data::kLevelEasy:
		updateLevelFunc_ = &SceneGame::UpdateLevelEasy;
		drawLevelFunc_ = &SceneGame::DrawLevelEasy;
		break;
	case Data::kLevelNormal:
		updateLevelFunc_ = &SceneGame::UpdateLevelNormal;
		drawLevelFunc_ = &SceneGame::DrawLevelNormal;
		break;
	case Data::kLevelHard:
		updateLevelFunc_ = &SceneGame::UpdateLevelHard;
		drawLevelFunc_ = &SceneGame::DrawLevelHard;
		break;
	}

	(this->*updateLevelFunc_)();

	if (player_->IsDamage())
	{
		shakeX = GetRand(5);
		shakeY = GetRand(5);
	}
	else
	{
		shakeX = 0;
		shakeY = 0;
	}

	if (level == Data::kLevelPractice && input.IsTriggered(InputType::skip)) isSkip = true;
	
	//プレイヤーもしくはエネミーが死んだらシーンを切り替える
	if (player_->IsDead() || enemy_->IsDead() || isSkip)
	{
		FadeOutUpdate();
		if (fadeValue < 255)
		{
			return;
		}
		bool isWin = false;
		if (player_->IsDead()) isWin = false;
		else if (enemy_->IsDead()) isWin = true;
	
		if ((level == Data::kLevelPractice && isWin) || isSkip)
		{
			SceneGame* nextScene = new SceneGame(manager_);
			nextScene->SetLevel(level + 1);
			manager_.ChangeScene(nextScene);
			return;
		}
		else
		{
			SceneResult* nextScene = new SceneResult(manager_);
			nextScene->SetLevel(level);
			nextScene->SetLesult(isWin);
			manager_.ChangeScene(nextScene);
			return;
		}
	}
	else
	{
		FadeInUpdate();
		if (0 < fadeValue) return;
	}
}

void SceneGame::Draw()
{
	SetDrawScreen(screenHandle);
	DrawBackGround(backHandle);
	DrawMoveLine();

	player_->Draw();
	enemy_->Draw();
	if (!player_->IsDead() && !enemy_->IsDead()) shot_->Draw();

	(this->*drawLevelFunc_)();
	// 今から描く画像と、すでに描画されているスクリーンとのブレンドの仕方を指定している
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	// 画面全体を真っ黒に塗りつぶす
	DrawBox(0, 0, Data::kScreenWidth, Data::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(shakeX, shakeY, screenHandle, true);
}

void SceneGame::SetLevel(int selectLevel)
{
	level = selectLevel;
	if (level == Data::kLevelNormal) shotTimer = kLevelNormalShotInterval;
	if (level == Data::kLevelHard) shotTimer = kLevelHardShotInterval;
}

void SceneGame::UpdateLevelPractice()
{
	UpdateIceShot();
	operate_->UpdateOperateGame();
}

void SceneGame::UpdateLevelEasy()
{
	UpdateIceShot();
	UpdateIcicleShot();
}

void SceneGame::UpdateLevelNormal()
{
	UpdateThunderShot();
	UpdateIcicleShot();
}

void SceneGame::UpdateLevelHard()
{
	UpdateThunderShot();
	UpdateIcicleShot();
}

void SceneGame::UpdateIceShot()
{
	if (!player_->IsEnable() && !enemy_->IsEnable())
	{
		if (iceShot_->IsFire())
		{
			iceShot_->Fire(enemy_->GetPosition(), Vector2{ -4.0f,0.0f });
		}
	}
	iceShot_->Update();
	if (!player_->IsDamage() && !player_->IsEnable() && !enemy_->IsEnable())
	{
		if (iceShot_->IsCollision())
		{
			if (iceShot_->GetRect().IsHit(player_->GetRect()))
			{
				iceShot_->Impact();
				player_->OnDamage();
			}
		}
	}
}

void SceneGame::UpdateThunderShot()
{
	if (!player_->IsEnable() && !enemy_->IsEnable())
	{
		if (thunderShot_->IsFire())
		{
			int fireLine = GetRand(5);
			Position2 enemyPos_ = enemy_->GetPosition();
			Position2 firePos_ = {enemyPos_.x, Data::kCenterY + fireLine * Data::kMoveSpace};

			thunderShot_->Fire(firePos_, Vector2{ -1.0f,0.0f });
		}
	}
	thunderShot_->Update();
	if (!player_->IsDamage() && !player_->IsEnable() && !enemy_->IsEnable())
	{
		if (thunderShot_->IsCollision())
		{
			if (thunderShot_->GetRect().IsHit(player_->GetRect()))
			{
				thunderShot_->Impact();
				player_->OnDamage();
			}
		}
	}
}

void SceneGame::UpdateIcicleShot()
{
	if (!player_->IsEnable() && !enemy_->IsEnable())
	{
		shotTimer--;
		for (auto& icicleShot : icicleShot_)
		{
			if (icicleShot->IsFire())
			{
				if (shotTimer < 0)
				{
					float lineRangeLeft = Data::kCenterX, lineRangeRight = (Data::kCenterX + Data::kMoveRange) - Data::kLineReduce * level;
					int shotRange = 0;
					switch (level)
					{
					case Data::kLevelEasy:
						lineRangeLeft -= Data::kEasyMoveRange;
						shotTimer = kLevelEasyShotInterval;
						break;
					case Data::kLevelNormal:
						lineRangeLeft -= Data::kNormalMoveRange;
						if (vel_.y < 10.0f) vel_.y += 0.05f;
						shotTimer = kLevelNormalShotInterval;
						break;
					case Data::kLevelHard:
						lineRangeLeft -= Data::kHardMoveRange;
						if(vel_.y < 15.0f) vel_.y += 0.15f;
						shotTimer = levelHardInterval;
						break;
					}
					shotRange = static_cast<int>(lineRangeRight - lineRangeLeft);

					Position2 pos_;
					pos_.x = static_cast<float>(GetRand(shotRange) + static_cast<int>(lineRangeLeft));

					icicleShot->Fire(pos_, vel_);

					levelHardInterval -= 1;
					if (levelHardInterval < 0) levelHardInterval = 0;
				}
			}
		}
	}
	for (auto& icicleShot : icicleShot_)
	{
		icicleShot->Update();
	}
	for (auto & icicleShot : icicleShot_)
	{
		if (!player_->IsDamage() && !player_->IsEnable() && !enemy_->IsEnable())
		{
			if (icicleShot->IsCollision())
			{
				if (icicleShot->GetRect().IsHit(player_->GetRect()))
				{
					icicleShot->Impact();
					player_->OnDamage();
				}
			}
		}
	}
}

void SceneGame::DrawLevelPractice()
{
	iceShot_->Draw();
	operate_->DrawOperateGame();
}

void SceneGame::DrawLevelEasy()
{	
	iceShot_->Draw();
	for (auto& icicleShot : icicleShot_)
	{
		icicleShot->Draw();
	}
}

void SceneGame::DrawLevelNormal()
{
	thunderShot_->Draw();
	for (auto& icicleShot : icicleShot_)
	{
		icicleShot->Draw();
	}
}

void SceneGame::DrawLevelHard()
{
	thunderShot_->Draw();
	for (auto& icicleShot : icicleShot_)
	{
		icicleShot->Draw();
	}
}

void SceneGame::DrawMoveLine()
{
	int color = 0xffffff;
	for (int i = 0; i < Data::kMoveLine; i++)
	{
		float lineRangeLeft = Data::kCenterX, lineRangeRight = (Data::kCenterX + Data::kMoveRange) - Data::kLineReduce * level;
		switch (level)
		{
		case Data::kLevelPractice:
			lineRangeLeft -= Data::kPracticeMoveRange;
			break;
		case Data::kLevelEasy:
			lineRangeLeft -= Data::kEasyMoveRange;
			break;
		default:
			lineRangeLeft -= Data::kNormalMoveRange;
			break;
		}

		float linePosY = Data::kCenterY + i * Data::kMoveSpace;
		if (enemy_->GetPosLine() == linePosY) color = 0xff0000;
		else color = 0xffffff;

		DrawLineAA(lineRangeLeft, linePosY, lineRangeRight, linePosY, color);
	}
}
