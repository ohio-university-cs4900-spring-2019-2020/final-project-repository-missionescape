#pragma once

#include "WO.h"
#include "Model.h"
#include <irrKlang.h>

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr {
	class WOdriving { //: public WO {
	public:
		static WOdriving* New(
			//default looking in +x direction
			const std::string modelFileName = "../mm/models/orca.dae",
			Vector scale = Vector(30, 30, 30),
			MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstSMOOTH,
			std::string label = "Orca",
			Vector pos = Vector(-1440, 580, 100)
		);
		~WOdriving();

		//keyboard inputs
		void onKeyDown(const SDL_KeyboardEvent& key);
		void onKeyUp(const SDL_KeyboardEvent& key);
		void onMouseWheelScroll(const SDL_MouseWheelEvent& e);
		void onMouseDown(const SDL_MouseButtonEvent& e);
		void onMouseUp(const SDL_MouseButtonEvent& e);
		void onMouseMove(const SDL_MouseMotionEvent& e);

		void setSpeed(float newSpeed) { this->speed = newSpeed; }
		float getSpeed() { return this->speed; }

		Vector getPosition() { return orca->getPosition(); }
		Vector getLookDirection() { return orca->getLookDirection(); }
		Vector getNormalDirection() { return orca->getNormalDirection(); }
		void setPosition(const Vector& newXYZ) { orca->setPosition(newXYZ); }
		void setPosition(float x, float y, float z) { orca->setPosition(Vector(x, y, z)); }
		void setLookDirection(const Vector& lookDirection) { orca->getModel()->setLookDirection(lookDirection); }
		void setNormalDirection(const Vector& normalDirection) { orca->getModel()->setNormalDirection(normalDirection); }
		void moveRelative(const Vector& dxdydz) { orca->moveRelative(dxdydz); }

		void move(float distance = 0.1f);
		void back(float distance = 0.1f);

		void update();
		bool hasDriver() { return driver != nullptr; }
		void setDriver(Camera* newDriver);
		Camera* getDriver() { return driver; }
		WO* getorcaWO() { return orca; }

		bool isMoving();
		float lookAngle = 0;
		float yaw = 0;

		float Rads(float deg);
		float Degs(float rad);


	protected:
		WO* orca;
		Camera* driver;
		std::set<SDL_Keycode> keysPressed;
		float speed, roll;
		float distanceFromorca = 32.28f;
		float angleAround = 0;
		float pitch = 16.1892f;
		void calcZoom(const SDL_MouseWheelEvent& e);
		float calcHori();
		float calcVert();
		void calcCamPos(float hori, float vert);

		WOdriving(
			const std::string modelFileName = "../mm/models/orca.dae",
			Vector scale = Vector(1, 1, 1),
			MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstSMOOTH,
			std::string label = "orca",
			Vector pos = Vector(-495, 325, 8)
		);
	private:
		bool isMovementKey(SDL_Keycode key);
	};
}
#endif
