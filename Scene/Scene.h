#pragma once
#include "../Geometry.h"

//�v���g�^�C�v�錾
class SceneManager;	//�V�[���}�l�[�W���[
class InputState;	//���̓X�e�[�g
//���̎��_�ł�SceneManager��InputState��
//�|�C���^�������͎Q�ƂƂ��Ă��������Ȃ��B

/// <summary>
/// �V�[�����N���X
/// </summary>
class Scene
{
public:
	Scene(SceneManager& manager) :
		manager_(manager)
	{
	}
	virtual ~Scene() {};
	//�V�[�����X�V����
	virtual void Update(const InputState& input) = 0;
	//�V�[����`�悷��
	virtual void Draw() = 0;

protected:
	SceneManager& manager_; //�V�[���}�l�[�V���[�ւ̎Q��

	void FadeInUpdate();
	void FadeOutUpdate();

	void DrawFunction(Rect pos_, int imgWidth, int imgHeight, int imgIdxWidth, int imgIdxHeight, double largeRate, int handle, bool isTurn);
	void DrawBackGround(int handle);

	static constexpr int fadeInterval = 60;
	int fadeTimer = fadeInterval;
	int fadeValue = 255;

	int currentLevel = 0;
};

