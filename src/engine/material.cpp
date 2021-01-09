#include "engine/material.hpp"

Material::Material (Gem gem) {
	assignGem(gem);
}
Material::Material(Stone stone) {
	assignStone(stone);
}
Material::Material(Metal metal) {
	assignMetal(metal);
}
Material::Material(Type type, Color color) {
	switch (type) {
	case Type::plastic: assignPlastic(color);  break;
	case Type::rubber: assignRubber(color); break;
	default:;
	}
}


void Material::assignGem(Gem gem) {
	switch (gem) {
	case Gem::emerald:
		_ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f),
			_diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f),
			_specular = glm::vec3(0.633f, 0.727811f, 0.633f),
			_shininess = 0.6f; break;
	case Gem::ruby:
		_ambient = glm::vec3(0.1745f, 0.01175f, 0.01175f),
			_diffuse = glm::vec3(0.61424f, 0.04136f, 0.04136f),
			_specular = glm::vec3(0.727811f, 0.626959f, 0.626959f),
			_shininess = 0.6f; break;
	default:;
	};
}
void Material::assignStone(Stone stone) {
	switch (stone) {
	case Stone::jade:
		_ambient = glm::vec3(0.135f, 0.2225f, 0.1575f),
			_diffuse = glm::vec3(0.54f, 0.89f, 0.63f),
			_specular = glm::vec3(0.316228f, 0.316228f, 0.316228f),
			_shininess = 0.1f; break;
	case Stone::obsidian:
		_ambient = glm::vec3(0.05375f, 0.05f, 0.06625f),
			_diffuse = glm::vec3(0.18275f, 0.17f, 0.22525f),
			_specular = glm::vec3(0.332741f, 0.328634f, 0.346435f),
			_shininess = 0.3f; break;
	case Stone::pearl:
		_ambient = glm::vec3(0.25f, 0.20725f, 0.20725f),
			_diffuse = glm::vec3(1.0f, 0.829f, 0.829f),
			_specular = glm::vec3(0.296648f, 0.296648f, 0.296648f),
			_shininess = 0.088f; break;
	case Stone::turquoise:
		_ambient = glm::vec3(0.1f, 0.18725f, 0.1745f),
			_diffuse = glm::vec3(0.396f, 0.74151f, 0.69102f),
			_specular = glm::vec3(0.297254f, 0.30829f, 0.306678f),
			_shininess = 0.1f; break;
	default:;
	};
}
void Material::assignMetal(Metal metal) {
	switch (metal) {
	case Metal::brass:
		_ambient = glm::vec3(0.329412f, 0.223529f, 0.027451f),
			_diffuse = glm::vec3(0.780392f, 0.568627f, 0.113725f),
			_specular = glm::vec3(0.992157f, 0.941176f, 0.807843f),
			_shininess = 0.21794872f; break;
	case Metal::bronze:
		_ambient = glm::vec3(0.2125f, 0.1275f, 0.054f),
			_diffuse = glm::vec3(0.714f, 0.4284f, 0.18144f),
			_specular = glm::vec3(0.393548f, 0.271906f, 0.166721f),
			_shininess = 0.2f; break;
	case Metal::chrome:
		_ambient = glm::vec3(0.25f, 0.25f, 0.25f),
			_diffuse = glm::vec3(0.4f, 0.4f, 0.4f),
			_specular = glm::vec3(0.774597f, 0.774597f, 0.774597f),
			_shininess = 0.6f; break;
	case Metal::copper:
		_ambient = glm::vec3(0.19125f, 0.0735f, 0.0225f),
			_diffuse = glm::vec3(0.7038f, 0.27048f, 0.0828f),
			_specular = glm::vec3(0.256777f, 0.137622f, 0.086014f),
			_shininess = 0.1f; break;
	case Metal::gold:
		_ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f),
			_diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f),
			_specular = glm::vec3(0.628281f, 0.555802f, 0.366065f),
			_shininess = 0.4f; break;
	case Metal::silver:
		_ambient = glm::vec3(0.19225f, 0.19225f, 0.19225f),
			_diffuse = glm::vec3(0.50754f, 0.50754f, 0.50754f),
			_specular = glm::vec3(0.508273f, 0.508273f, 0.508273f),
			_shininess = 0.4f; break;
	default:;
	};
}
void Material::assignPlastic(Color plastic) {
	_ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	_shininess = 0.25f;

	switch (plastic) {
		case Color::black:
			_diffuse = glm::vec3(0.01f, 0.01f, 0.01f),
			_specular = glm::vec3(0.5f, 0.5f, 0.5f); break;
		case Color::white:
			_diffuse = glm::vec3(0.55f, 0.55f, 0.55f),
			_specular = glm::vec3(0.7f, 0.7f, 0.7f); break;
		case Color::red:
			_diffuse = glm::vec3(0.5f, 0.0f, 0.0f),
			_specular = glm::vec3(0.7f, 0.6f, 0.6f); break;
		case Color::green:
			_diffuse = glm::vec3(0.1f, 0.35f, 0.1f),
			_specular = glm::vec3(0.45f, 0.55f, 0.45f); break;
		case Color::yellow:
			_diffuse = glm::vec3(0.5f, 0.5f, 0.0f),
			_specular = glm::vec3(0.6f, 0.6f, 0.5f); break;
		case Color::cyan:
			_ambient = glm::vec3(0.0f, 0.1f, 0.06f),
			_diffuse = glm::vec3(0.0f, 0.50980392f, 0.50980392f),
			_specular = glm::vec3(0.50196078f, 0.50196078f, 0.50196078f); break;
		default:;
	};
}
void Material::assignRubber(Color rubber) {
	_shininess = 0.078125f;

	switch (rubber) {
		case Color::black:
			_ambient = glm::vec3(0.02f, 0.02f, 0.02f),
			_diffuse = glm::vec3(0.01f, 0.01f, 0.01f),
			_specular = glm::vec3(0.4f, 0.4f, 0.4f); break;
		case Color::white:
			_ambient = glm::vec3(0.05f, 0.05f, 0.05f),
			_diffuse = glm::vec3(0.5f, 0.5f, 0.5f),
			_specular = glm::vec3(0.7f, 0.7f, 0.7f); break;
		case Color::red:
			_ambient = glm::vec3(0.05f, 0.0f, 0.0f),
			_diffuse = glm::vec3(0.5f, 0.4f, 0.4f),
			_specular = glm::vec3(0.7f, 0.04f, 0.04f); break;
		case Color::green:
			_ambient = glm::vec3(0.0f, 0.05f, 0.0f),
			_diffuse = glm::vec3(0.4f, 0.5f, 0.4f),
			_specular = glm::vec3(0.04f, 0.7f, 0.04f); break;
		case Color::yellow:
			_ambient = glm::vec3(0.05f, 0.05f, 0.0f),
			_diffuse = glm::vec3(0.5f, 0.5f, 0.4f),
			_specular = glm::vec3(0.7f, 0.7f, 0.04f); break;
		case Color::cyan:
			_ambient = glm::vec3(0.0f, 0.05f, 0.05f),
			_diffuse = glm::vec3(0.4f, 0.5f, 0.5f),
			_specular = glm::vec3(0.04f, 0.7f, 0.7f); break;
		default:;
	};
}