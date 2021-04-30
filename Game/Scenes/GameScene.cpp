#include "GameScene.h"

GameScene::GameScene() {
}

GameScene::~GameScene()
{

}

bool GameScene::OnCreate()
{
	Debug::Info("Creating GameScene", "GameScene.cpp", __LINE__);

	EngineCore::getInstance()->SetCamera(new Camera());
	EngineCore::getInstance()->GetCamera()->SetPos(glm::vec3(0.0f, 0.0f, 4.0f));
	LightSource* test;
	test = new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	EngineCore::getInstance()->GetCamera()->AddLightSource(test);


	Model* diceModel = new Model("Resources/Models/Dice.obj",
		"Resources/Materials/Dice.mtl",
		ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* appleModel = new Model("Resources/Models/Apple.obj",
		"Resources/Materials/Apple.mtl",
		ShaderHandler::GetInstance()->GetShader("basicShader"));
	Scenegraph::GetInstance()->AddModel(diceModel);
	Scenegraph::GetInstance()->AddModel(appleModel);
	
	Scenegraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(-2.0f, 0.0f, -2.0f)));
	Scenegraph::GetInstance()->AddGameObject(new GameObject(appleModel, glm::vec3(1.5f, 0.0f, 0.0f)),
		"Apple");

	diceModel = nullptr;
	appleModel = nullptr;
	
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	Scenegraph::GetInstance()->Update(deltaTime_);
}
void GameScene::Render()
{
	Scenegraph::GetInstance()->Render(EngineCore::getInstance()->GetCamera());
} 
