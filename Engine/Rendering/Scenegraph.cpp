#include "Scenegraph.h"

std::unique_ptr<Scenegraph> Scenegraph::sceneGraphInstance = nullptr;
std::unordered_map<GLuint, std::vector<Model*>> Scenegraph::sceneModels =
    std::unordered_map<GLuint, std::vector<Model*>>();
std::map<std::string, GameObject*> Scenegraph::sceneGameObjects =
    std::map<std::string, GameObject*>();


Scenegraph* Scenegraph::GetInstance()
{
    if (sceneGraphInstance.get() == nullptr) {
        sceneGraphInstance.reset(new Scenegraph);
    }
    return sceneGraphInstance.get();
}

void Scenegraph::OnDestroy()
{
    if (sceneGameObjects.size() > 0) {
        for (auto go : sceneGameObjects) {
            delete go.second;
            go.second = nullptr;
        }
        sceneGameObjects.clear();
    }

    if (sceneModels.size() > 0) {
        for (auto entry : sceneModels) {
            if (entry.second.size() > 0) {
                for (auto m : entry.second) {
                    delete m;
                    m = nullptr;
                }
                entry.second.clear();
            }
        }
        sceneModels.clear();
    }
}

void Scenegraph::AddModel(Model* model_)
{
    GLuint shader = model_->GetShaderProgram();
    if (sceneModels.find(shader) == sceneModels.end()) {
        sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(
            shader, std::vector<Model*>()));
        sceneModels[shader].reserve(10);
    }
    sceneModels[shader].push_back(model_);
}

void Scenegraph::AddGameObject(GameObject* go_, std::string tag_)
{
    if (tag_ == "") {
        std::string newTag = "GameOBject" + std::to_string(sceneGameObjects.size() + 1);
        go_->SetTag(newTag);
        sceneGameObjects[newTag] = go_;
    }
    else if (sceneGameObjects.find(tag_) == sceneGameObjects.end()) {
        go_->SetTag(tag_);
        sceneGameObjects[tag_] = go_;
    }
    else {
        Debug::Error("Trying to add Game Object with tag:" + tag_ +
            " that already exists", "Scenegraph.cpp", __LINE__);
        std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
        go_->SetTag(newTag);
        sceneGameObjects[newTag] = go_;
    }
}

GameObject* Scenegraph::GetGameObject(std::string tag_)
{
    if (sceneGameObjects.find(tag_) != sceneGameObjects.end()) {
        return sceneGameObjects[tag_];
    }
    return nullptr;
}

void Scenegraph::Update(const float deltaTime_)
{
    for (auto go : sceneGameObjects) {
        go.second->Update(deltaTime_);
    }
}

void Scenegraph::Render(Camera* camera_)
{
    for (auto entry : sceneModels) {
        glUseProgram(entry.first);
        for (auto m : entry.second) {
            m->Render(camera_);
        }
    }
}

Scenegraph::~Scenegraph()
{
    OnDestroy();
}
Scenegraph::Scenegraph() {

}
