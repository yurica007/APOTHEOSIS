#include "Scene.h"
#include "../GameData.h"
#include <DxLib.h>

void Scene::FadeInUpdate()
{
	fadeValue = static_cast<int>(255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval));
	fadeTimer--;
	if (fadeTimer < 0) fadeTimer = 0;
}

void Scene::FadeOutUpdate()
{
	fadeValue = static_cast<int>(255 * static_cast<float>(fadeTimer) / static_cast<float>(fadeInterval));
	fadeTimer++;
	if (fadeInterval < fadeTimer) fadeTimer = fadeInterval;
}

void Scene::DrawFunction(Rect pos_, int imgWidth, int imgHeight, int imgIdxWidth, int imgIdxHeight, double largeRate, int handle, bool isTurn)
{
	DrawRectRotaGraphF(pos_.center.x, pos_.center.y,
		imgWidth * imgIdxWidth, imgHeight * imgIdxHeight,
		imgWidth, imgHeight,
		largeRate, 0.0f,
		handle, true, isTurn);
}

void Scene::DrawBackGround(int handle)
{
	DrawExtendGraph(0, 0, Data::kScreenWidth, Data::kScreenHeight, handle, true);
}

