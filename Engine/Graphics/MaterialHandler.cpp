#include "MaterialHandler.h"

std::vector<Material> MaterialHandler::materials = std::vector<Material>();
std::unique_ptr<MaterialHandler> MaterialHandler::materialInstance = nullptr;

MaterialHandler* MaterialHandler::GetInstance()
{
    if (materialInstance.get() == nullptr) {
        materialInstance.reset(new MaterialHandler);
    }
    return materialInstance.get();
}

void MaterialHandler::AddMaterial(Material mat_)
{
    materials.push_back(mat_);
}

const Material MaterialHandler::GetMaterial(const std::string& matName_) const
{
    for (auto mat : materials) {
        if (mat.name == matName_) {
            return mat;
        }
    }
    return Material();
}


void MaterialHandler::OnDestroy()
{
    if (materials.size() > 0) {
        materials.clear();
    }
}

MaterialHandler::~MaterialHandler()
{
    OnDestroy();
}
MaterialHandler::MaterialHandler() {
    materials.reserve(10);
}
