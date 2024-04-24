#pragma once

#include <deque>

class Scene;
class InputState;

class SceneManager
{
public:
	/// <summary>
	/// �V�[���̐؂�ւ����s��
	/// </summary>
	/// <param name="scene">�؂�ւ��������V�[���̃A�h���X</param>
	void ChangeScene(Scene* scene);

	/// <summary>
	/// �V�[������ɐς�
	/// Update�Ŏ��s�����̂͏�ɐς܂ꂽ�V�[���̂�
	/// </summary>
	void PushuScene(Scene* scene);

	/// <summary>
	/// �V�[�����폜����
	/// Update�Ŏ��s�����̂͏�ɐς܂ꂽ�V�[���̂�
	/// </summary>
	void PopScene();

	/// <summary>
	/// �e�V�[����Update���s��
	/// </summary>
	/// <param name="input">���̓X�e�[�g</param>
	void Update(const InputState& input);
	/// <summary>
	/// �e�V�[���̕`����s��
	/// </summary>
	void Draw();

private:
	//�u�����s���v�̃V�[����؂�ւ��Ă��������̂ŎQ�Ƃł͂Ȃ��|�C���^�Ƃ��Đ錾
	std::deque<Scene*> scenes_;
};

