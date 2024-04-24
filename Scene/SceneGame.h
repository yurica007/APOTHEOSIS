#pragma once
#include "Scene.h"
#include "../Geometry.h"
#include <memory>
#include <array>

class Player;
class Enemy;
class Operate;
class Shot;
class IceShot;
class ThunderShot;
class IcicleShot;
class InputState;

class SceneGame :
    public Scene
{
public:
    SceneGame(SceneManager& manager);
    virtual ~SceneGame();

    virtual void Update(const InputState& input);
    virtual void Draw();

    void SetLevel(int selectLevel);

private:
    void UpdateLevelPractice();
    void UpdateLevelEasy();
    void UpdateLevelNormal();
    void UpdateLevelHard();

    void UpdateIceShot();
    void UpdateThunderShot();
    void UpdateIcicleShot();

    void DrawLevelPractice();
    void DrawLevelEasy();
    void DrawLevelNormal();
    void DrawLevelHard();

    void DrawMoveLine();

private:
    Vector2 vel_ = { 0.0f, 5.0f };

    std::shared_ptr<Player> player_;
    std::shared_ptr<Enemy> enemy_;
    std::shared_ptr<Operate> operate_;

    std::shared_ptr<Shot> shot_;
    std::shared_ptr<IceShot> iceShot_;
    std::shared_ptr<ThunderShot> thunderShot_;
    std::array<std::shared_ptr<IcicleShot>, 10> icicleShot_;

    void (SceneGame::*updateLevelFunc_)(void);
    void (SceneGame::*drawLevelFunc_)(void);

    int shotTimer = 0;
    int levelHardInterval;
    int level = 0;

    int shakeX = 0;
    int shakeY = 0;

    int screenHandle;
    int backHandle;
    bool isSkip = false;
};

