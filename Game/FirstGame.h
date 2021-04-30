#ifndef FIRSTGAME_H
#define FIRSTGAME_H

#include "../Engine/Core/EngineCore.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"
class FirstGame : public GameInterface
{
public:
	FirstGame();
	virtual ~FirstGame();

	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
private:
	int currentSceneNum;
	Scene* currentScene;
	void BuildScene();
};

#endif // !FIRSTGAME_H