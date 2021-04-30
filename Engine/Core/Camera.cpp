#include "Camera.h"

#include "EngineCore.h"

Camera::Camera()
{
	fieldOfView = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);	worldUp = up;;
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspective = glm::perspective(fieldOfView,
		EngineCore::getInstance()->GetScreenWidth() /
		EngineCore::getInstance()->GetScreenHeight(), 
		nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, EngineCore::getInstance()->GetScreenWidth(),
		0.0f, EngineCore::getInstance()->GetScreenHeight(),
		-1.0f, 1.0f);
		
	UpdateCameraVector();
}
Camera::~Camera()
{
}

void Camera::AddLightSource(LightSource* lightSource_)
{
	lightSources.push_back(lightSource_);
}

std::vector<LightSource*> Camera::GetLightSources()
{
	return lightSources;
}

void Camera::SetPos(glm::vec3 pos_)
{
	pos = pos_;
	UpdateCameraVector();
}

void Camera::SetRot(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVector();
}

glm::mat4 Camera::GetView() const
{
	return view;
}

glm::mat4 Camera::GetPersepective() const
{
	return perspective;
}

glm::mat4 Camera::getOrthographic() const
{
	return orthographic;
}

glm::vec3 Camera::GetPos() const
{
	return pos;
}

void Camera::ProcessMouseMovement(glm::vec2 offset_)
{
	offset_ *= 0.05f;

	yaw += offset_.x;
	pitch += offset_.y;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	if (yaw < 0.0f) {
		yaw += 360.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}
	UpdateCameraVector();
}

void Camera::ProcessMouseZoom(int y_)
{
	if (y_ < 0 || y_ > 0) {
		pos += static_cast<float>(y_) * (forward * 2.0f);
	}
	UpdateCameraVector();
}

void Camera::UpdateCameraVector()
{
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));

	view = glm::lookAt(pos, pos + forward, up);
}
