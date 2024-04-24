#pragma once
#include "Scene.h"
#include "../Geometry.h"
#include <map>
#include <memory>
#include <string>
#include <array>

enum Menu
{
	start,
	level
};

enum Level
{
	practice,
	easy,
	normal,
	hard
};

class InputState;
class Operate;
class Font;

class SceneTitle :
    public Scene
{
public:
	SceneTitle(SceneManager& manager);
	virtual ~SceneTitle();

	virtual void Update(const InputState& input);
	virtual void Draw();

	void SetLevel(int selectLevel);

private:
	void UpdateCursor();
	void UpdateNormal(const InputState& input);
	void UpdateSelectStart(const InputState& input);
	void UpdateSelectLevel(const InputState& input);
	void UpdateChar();

	void DrawMenu();
	void DrawNormal();
	void DrawSelectStart();
	void DrawSelectLevel();
	void DrawChar();
	void DrawLevelComment();

private:
	Rect menuCursorRect_;
	Rect levelCursorRect_;

	std::map<Menu, std::wstring> menu_;
	std::map<Level, std::wstring> level_;
	std::shared_ptr<Operate> operate_;
	std::shared_ptr<Font> font_;

	//メンバ関数ポインタ
	void (SceneTitle::* updateFunc_) (const InputState& input);
	void (SceneTitle::* drawFunc_) (void);
	
	int menuIndex = 0;
	int levelIndex = 0;
	int currentLevel = 0;

	bool selectStart = false;
	bool selectLevel = false;

	int backHandle;
	int playerHandle;
	int enemyHandle;
	int cursorHandle;
	int selectHandle;

	int playerImgIdx = 0;
	int enemyImgIdx = 0;
	int cursorImgIdx = 0;
	
	int frame;
	int playerAnimFrame;
	int enemyAnimFrame;
};

