#pragma once
#include "../Geometry.h"

//プロトタイプ宣言
class SceneManager;	//シーンマネージャー
class InputState;	//入力ステート
//この時点ではSceneManagerとInputStateは
//ポインタもしくは参照としてしか扱えない。

/// <summary>
/// シーン基底クラス
/// </summary>
class Scene
{
public:
	Scene(SceneManager& manager) :
		manager_(manager)
	{
	}
	virtual ~Scene() {};
	//シーンを更新する
	virtual void Update(const InputState& input) = 0;
	//シーンを描画する
	virtual void Draw() = 0;

protected:
	SceneManager& manager_; //シーンマネーシャーへの参照

	void FadeInUpdate();
	void FadeOutUpdate();

	void DrawFunction(Rect pos_, int imgWidth, int imgHeight, int imgIdxWidth, int imgIdxHeight, double largeRate, int handle, bool isTurn);
	void DrawBackGround(int handle);

	static constexpr int fadeInterval = 60;
	int fadeTimer = fadeInterval;
	int fadeValue = 255;

	int currentLevel = 0;
};

