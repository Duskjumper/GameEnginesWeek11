#include "GameObject.h"

/* GameObject::GameObject(Model* model_) : model(nullptr), position(glm::vec3()), angle(0.0f),
rotation(glm::vec3(0.0f,1.0f,0.0f)), scale(glm::vec3(1.0f)), modelInstance(0) {
	model = model_;
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
	}
} */
GameObject::GameObject(Model* model_, glm::vec3 position_) : model(nullptr), angle(0.0f),
rotation(glm::vec3(0.0f, 1.0f, 0.0f)), scale(glm::vec3(1.0f)), modelInstance(0), ishit(false) {
	model = model_;
	position = position_;
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->GetBoundingBox();
		boundingBox.transform = model->GetTransform(modelInstance);
	}

	std::cout << "Min: " << glm::to_string(boundingBox.minVert)
		<< ", Max: " << glm::to_string(boundingBox.maxVert) << std::endl;
}
GameObject::~GameObject()
{
	model = nullptr;
}

void GameObject::Render(Camera* camera_)
{
	if (model) {
		model->Render(camera_);
	}
}

void GameObject::Update(const float deltaTime_)
{
	SetAngle(angle + 0.005f);
}

glm::vec3 GameObject::GetPosition()
{
	return position;
}

float GameObject::GetAngle()
{
	return angle;
}

glm::vec3 GameObject::GetRotation()
{
	return rotation;
}

glm::vec3 GameObject::GetScale()
{
	return scale;
}

std::string GameObject::GetTag() const
{
	return tag;
}

bool GameObject::GetHit() const
{
	return ishit;
}

void GameObject::SetPosition(glm::vec3 position_)
{
	position = position_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
		boundingBox.minVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
		boundingBox.maxVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
	}
}

void GameObject::SetTag(std::string tag_)
{
	tag = tag_;
}

void GameObject::SetHit(bool hit_, int buttonType_)
{
	ishit = hit_;
	if (ishit) {
		std::cout << tag << " was hit" << std::endl;
	}
}

BoundingBox GameObject::GetBoundingBox() const
{
	return boundingBox;
}
