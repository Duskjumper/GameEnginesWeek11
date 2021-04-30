#include "Engine/Core/EngineCore.h"
#include "Game/FirstGame.h"

int main(int argc, char* argv[]) {
	EngineCore::getInstance()->SetGameInterface(new FirstGame);
	if (!EngineCore::getInstance()->OnCreate("GameEngines4Engine", 800, 600)) {
		Debug::FatalError("Engine failed to initalize", __FILE__, __LINE__);
		return 0;
	}
	EngineCore::getInstance()->Run();
	return 0;
}