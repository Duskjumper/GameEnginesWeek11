#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "../../Engine/Core/EngineCore.h"

class StartScene : public Scene {
public:
	StartScene();
	virtual ~StartScene();

	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
};

#endif // !STARTSCENE_H