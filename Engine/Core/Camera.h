#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../Engine/FX/LightSource.h"
#include <vector>

class Camera
{
public:
	Camera();
	~Camera();
	void AddLightSource(LightSource* lightSource_);
	std::vector<LightSource*> GetLightSources();
	void SetPos(glm::vec3 pos_);
	void SetRot(float yaw_, float pitch_);

	glm::mat4 GetView() const;
	glm::mat4 GetPersepective() const;
	glm::mat4 getOrthographic() const;
	glm::vec3 GetPos() const;

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseZoom(int y_);

private:
	void UpdateCameraVector();
	glm::vec3 pos;
	glm::mat4 perspective, orthographic, view;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;
	std::vector<LightSource*> lightSources;
};
#endif 
