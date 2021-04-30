#include "StartScene.h"

StartScene::StartScene() {}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	Debug::Info("Start scene ", "StartScene.cpp", __LINE__);
	EngineCore::getInstance()->SetCurrentScene(1);
	return true;
}

void StartScene::Update(const float deltaTime_)
{
}

void StartScene::Render()
{
}
