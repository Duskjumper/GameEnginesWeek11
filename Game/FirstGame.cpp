#include "FirstGame.h"

FirstGame::FirstGame() : GameInterface(), currentSceneNum(0), currentScene(nullptr)
{
}

FirstGame::~FirstGame()
{
	delete currentScene;
	currentScene = nullptr;
}

bool FirstGame::OnCreate()
{
	if (EngineCore::getInstance()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}
	Debug::Warning("Engine scene is not initialized to 0", __FILE__, __LINE__);		
	return false;
}

void FirstGame::Update(const float deltaTime_)
{
	if (currentSceneNum != EngineCore::getInstance()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void FirstGame::Render()
{
	currentScene->Render();
}

void FirstGame::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;
	
	switch (EngineCore::getInstance()->GetCurrentScene()) {
	case 1: 
		currentScene = new GameScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = EngineCore::getInstance()->GetCurrentScene();
	if (!currentScene->OnCreate()) {
		Debug::Warning("Scene failed to create", __FILE__, __LINE__);
		EngineCore::getInstance()->Exit();
	}
}
