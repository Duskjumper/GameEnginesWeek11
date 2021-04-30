#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <vector>
#include <glm/vec3.hpp>

class LightSource
{
public:
	LightSource();
	LightSource(glm::vec3 pos_, float ambient_, float diffuse_, float specular_, glm::vec3 colour_);
	glm::vec3 getPos();
	void setPos(glm::vec3 position_);
	float getAmb();
	void setAmb(float ambient_);
	float getDif();
	void setDif(float diffuse_);
	float getSpec();
	void setSpec(float specular_);
	glm::vec3 getColour();
	void setColour(glm::vec3 colour_);
private:
	glm::vec3 pos;
	float ambient;
	float diffuse;
	float specular;
	glm::vec3 colour;
};

#endif // !LIGHTSOURCE_H