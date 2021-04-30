#include "LightSource.h"

LightSource::LightSource()
{
	pos = glm::vec3(0.0f);
	ambient = 1.0f;
	diffuse = 1.0f;
	specular = 1.0f;
	colour = glm::vec3(0.0f, 1.0f, 0.0f);
}

LightSource::LightSource(glm::vec3 pos_, float ambient_, float diffuse_, float specular_, glm::vec3 colour_)
{
	pos = pos_;
	ambient = ambient_;
	diffuse = diffuse_;
	specular = specular_;
	colour = colour_;
}

glm::vec3 LightSource::getPos()
{
	return pos;
}

void LightSource::setPos(glm::vec3 position_)
{
	pos = position_;
}

float LightSource::getAmb()
{
	return ambient;
}

void LightSource::setAmb(float ambient_)
{
	ambient = ambient_;
}

float LightSource::getDif()
{
	return diffuse;
}

void LightSource::setDif(float diffuse_)
{
	diffuse = diffuse_;
}

float LightSource::getSpec()
{
	return specular;
}

void LightSource::setSpec(float specular_)
{
	specular = specular_;
}

glm::vec3 LightSource::getColour()
{
	return colour;
}

void LightSource::setColour(glm::vec3 colour_)
{
	colour = colour_;
}
