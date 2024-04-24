#pragma once

namespace Data
{
	constexpr int kScreenWidth = 1600;	//16n
	constexpr int kScreenHeight = 900;	//9n
	constexpr int kColorData = 32;

	//�f�o�b�O���̓t���X�N���[���ŕ\�����Ȃ�
#ifdef _DEBUG
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif

	//���C���Q�[�������̒��S���W
	constexpr float kCenterX = kScreenWidth / 2;
	constexpr float kCenterY = kScreenHeight / 2;

	constexpr int kLevelPractice = 0;
	constexpr int kLevelEasy = 1;
	constexpr int kLevelNormal = 2;
	constexpr int kLevelHard = 3;

	//�e�̊g�嗦
	constexpr int kShotEnlargeRate = 1;

	constexpr int kMoveLine = 6;
	constexpr float kMoveSpace = kCenterY / kMoveLine;
	
	constexpr int kLineRange = 650;
	constexpr int kLineReduce = 30;
	constexpr int kMoveRange = 300;
	constexpr int kPracticeMoveRange = kLineRange;
	constexpr int kEasyMoveRange = 450;
	constexpr int kNormalMoveRange = 250;
	constexpr int kHardMoveRange = 200;

	constexpr float kPosCenterY = kCenterY + kMoveSpace * 2;
	constexpr int kDefaultFontSize = 16;
};