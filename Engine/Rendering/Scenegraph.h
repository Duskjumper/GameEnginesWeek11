#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory>
#include <unordered_map>
#include <map>
#include <vector>
#include "GameObject.h"

class Scenegraph
{
public:
	Scenegraph(const Scenegraph&) = delete;
	Scenegraph(Scenegraph&&) = delete;
	Scenegraph& operator=(const Scenegraph&) = delete;
	Scenegraph& operator=(Scenegraph&&) = delete;

	static Scenegraph* GetInstance();
	void OnDestroy();
	void AddModel(Model* model_);
	void AddGameObject(GameObject* go_, std::string tag_ = "");
	GameObject* GetGameObject(std::string tag_);

	void Update(const float deltaTime_);
	void Render(Camera* camera_);
private:
	Scenegraph();
	~Scenegraph();

	static std::unique_ptr<Scenegraph> sceneGraphInstance;
	friend std::default_delete<Scenegraph>;

	static std::unordered_map<GLuint, std::vector<Model*>> sceneModels;
	static std::map<std::string, GameObject*> sceneGameObjects;
};

#endif // !SCENEGRAPH_H