#pragma once

#include <deque>

class Scene;
class InputState;

class SceneManager
{
public:
	/// <summary>
	/// シーンの切り替えを行う
	/// </summary>
	/// <param name="scene">切り替えたい次シーンのアドレス</param>
	void ChangeScene(Scene* scene);

	/// <summary>
	/// シーンを上に積む
	/// Updateで実行されるのは上に積まれたシーンのみ
	/// </summary>
	void PushuScene(Scene* scene);

	/// <summary>
	/// シーンを削除する
	/// Updateで実行されるのは上に積まれたシーンのみ
	/// </summary>
	void PopScene();

	/// <summary>
	/// 各シーンのUpdateを行う
	/// </summary>
	/// <param name="input">入力ステート</param>
	void Update(const InputState& input);
	/// <summary>
	/// 各シーンの描画を行う
	/// </summary>
	void Draw();

private:
	//「今実行中」のシーンを切り替えていきたいので参照ではなくポインタとして宣言
	std::deque<Scene*> scenes_;
};

