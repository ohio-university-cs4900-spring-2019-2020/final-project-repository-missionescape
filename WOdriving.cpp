#include "WOdriving.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include "Camera.h"
#include "Model.h"
#include <complex>
#include "Mat4Fwd.h"
#include <irrKlang.h>

using namespace Aftr;
using namespace irrklang;

WOdriving* WOdriving::New(const std::string modelFilename, Vector scale, MESH_SHADING_TYPE shadingType, std::string label, Vector pos) {
	return new WOdriving(modelFilename, scale, shadingType, label, pos);
}

WOdriving::WOdriving(const std::string modelFileName, Vector scale, MESH_SHADING_TYPE shadingType, std::string label, Vector pos) {
	this->speed = 5;
	this->roll = 0;
	this->driver = nullptr;
	this->orca = WO::New(modelFileName, scale, shadingType);
	this->orca->setLabel(label);
	this->orca->setPosition(pos);
}

WOdriving::~WOdriving() {}

void WOdriving::setDriver(Camera* driver) {
	this->driver = driver;
	if (driver != nullptr) {
		this->driver->setPosition(this->getPosition() + Vector(0, 0, this->calcVert()));
		this->driver->setParentWorldObject(this->orca);
	} else {
		this->keysPressed.clear();
	}
}

void WOdriving::onKeyDown(const SDL_KeyboardEvent& key) {
	SDL_Keycode keyDown = key.keysym.sym;
	if (keyDown == SDLK_PLUS || keyDown == SDLK_EQUALS) {
		if (this->speed < 10) {
			this->speed += 0.5;
		}
		else if (this->speed < 0 || this->speed > 10) {
			this->speed = 0;
		}
	}
	if (keyDown == SDLK_MINUS) {
		if (this->speed > 0) {
			this->speed += -0.5;
		}
		else if (this->speed < 0 || this->speed > 10) {
			this->speed = 0;
		}
	}
	if (isMovementKey(keyDown)) {
		std::set<SDL_Keycode>::iterator found = keysPressed.find(keyDown);
		if (found == keysPressed.end()) {
			keysPressed.insert(keyDown);
		} 
	}
}

void WOdriving::onKeyUp(const SDL_KeyboardEvent& key) {
	SDL_Keycode keyUp = key.keysym.sym;
	if (isMovementKey(keyUp)) {
		std::set<SDL_Keycode>::iterator found = keysPressed.find(keyUp);
		if (found != keysPressed.end()) {
			keysPressed.erase(found);
		}
	}
}

void WOdriving::onMouseDown(const SDL_MouseButtonEvent& e) {}
void WOdriving::onMouseUp(const SDL_MouseButtonEvent& e) {}
void WOdriving::onMouseMove(const SDL_MouseMotionEvent& e) {}
void WOdriving::onMouseWheelScroll(const SDL_MouseWheelEvent& e) { this->calcZoom(e); }

void WOdriving::calcZoom(const SDL_MouseWheelEvent& e) {
	float zoomLVL = e.direction * 0.1f;
	this->distanceFromorca -= zoomLVL;
}

float WOdriving::calcHori() {
	return this->distanceFromorca * std::cos(this->Rads(this->pitch));
}
float WOdriving::calcVert() {
	return this->distanceFromorca * std::sin(this->Rads(this->pitch));
}

void WOdriving::calcCamPos(float hori, float vert) {
	float theta = this->Degs(this->getLookDirection().y) + angleAround;
	float offX = hori * std::sin(this->Rads(theta));
	float offY = hori * std::cos(this->Rads(theta));
	Vector pos = this->getPosition();
	if (this->hasDriver()) {
		this->driver->setPosition(pos.x - 10, pos.y + 0, pos.z + vert);
	}
	this->yaw = 180 - (this->Degs(this->getLookDirection().y) + angleAround);
}

void WOdriving::update() {
	for (std::set<SDL_Keycode>::iterator it = this->keysPressed.begin(); it != this->keysPressed.end(); ++it) {
		if (*it == SDLK_UP) {
			this->move(this->speed);
		}
		if (*it == SDLK_LEFT) {
			this->orca->rotateAboutRelZ(0.1f);
		}
		if (*it == SDLK_DOWN) {
			this->back(this->speed);
		}
		if (*it == SDLK_RIGHT) {
			this->orca->rotateAboutRelZ(-0.1f);
		}
	}
	//this->driver->attachCameraToWO(this->orca, this->orca->getPosition() + Vector(0, 0, 15));
}

void WOdriving::move(float distance) {
	for (int i = 0; i < distance; ++i) {
		this->moveRelative(this->getLookDirection());
	}
}

void WOdriving::back(float distance) {
	for (int i = 0; i < distance; ++i) {
		this->moveRelative(this->getLookDirection() * -1);
	}
}

bool WOdriving::isMovementKey(SDL_Keycode key) {
	return (key == SDLK_UP || key == SDLK_LEFT || key == SDLK_DOWN || key == SDLK_RIGHT ||
		key == SDLK_w || key == SDLK_a || key == SDLK_s || key == SDLK_d);
}

bool WOdriving::isMoving() {
	return this->keysPressed.find(SDLK_UP) != this->keysPressed.end()
		|| this->keysPressed.find(SDLK_w) != this->keysPressed.end()
		|| this->keysPressed.find(SDLK_DOWN) != this->keysPressed.end()
		|| this->keysPressed.find(SDLK_s) != this->keysPressed.end();
}

float WOdriving::Rads(float deg) {
	return std::tan((deg * Aftr::PI) / 180);
}
float WOdriving::Degs(float rad) {
	return rad * (180 / Aftr::PI);
}

#endif
