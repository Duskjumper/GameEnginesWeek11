#ifndef ENGINECORE_H
#define ENGINECORE_H

#include "Window.h"
#include "Timer.h"
#include <memory>
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"

#include "../Events/EventListener.h"

#include "../Rendering/GameObject.h"
#include "../Rendering/Scenegraph.h"

#include "../Graphics/ShaderHandler.h"
#include "../Rendering/TextureHandler.h"
#include "../Graphics/MaterialHandler.h"

#include "Camera.h"

class EngineCore
{
public:
	EngineCore(const EngineCore&) = delete;
	EngineCore(EngineCore&&) = delete;
	EngineCore& operator =(const EngineCore&) = delete;
	EngineCore& operator =(EngineCore&&) = delete;
	
	static EngineCore* getInstance();

	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	void Exit();

	bool GetIsRunning() const;
	int GetCurrentScene() const;
	float GetScreenHeight() const;
	float GetScreenWidth() const;
	Camera* GetCamera() const;
	
	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum_);
	void SetCamera(Camera* camera_);

	void NotifyOfMousePressed(glm::ivec2 mouse_, int buttonType_);
	void NotifyOfMouseReleased(glm::ivec2 mouse_, int buttonType_);
	void NotifyOfMouseMove(glm::ivec2 mouse_);
	void NotifyOfMouseScroll(int y_);


private:
	EngineCore();
	~EngineCore();
	void Update(const float deltaTime);
	void Render();
	void OnDestroy();

	static std::unique_ptr<EngineCore> engineInstance;
	friend std::default_delete<EngineCore>;

	Timer* timer;
	Window* window;
	bool isRunning;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;

	Camera* camera;
};

#endif // !ENGINECORE_H