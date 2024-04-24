#pragma once
#include "Scene.h"
#include "../Geometry.h"
#include <memory>

class Font;

class SceneResult :
    public Scene
{
public:
	SceneResult(SceneManager& manager);
	virtual ~SceneResult();

	virtual void Update(const InputState& input);
	virtual void Draw();

	void SetLevel(int selectLevel);
	void SetLesult(bool result);

private:

	void DrawWin();
	void DrawLose();

private:
	Rect rect_;

	std::shared_ptr<Font> font_;

	void (SceneResult::* drawFunc_)(void);

	int backWinHandle;
	int backLoseHandle;
	
	int drawFrame;
	int resultTimer = 300;

	int level = 0;
	bool isEnd = false;
	bool isWin = false;
};
