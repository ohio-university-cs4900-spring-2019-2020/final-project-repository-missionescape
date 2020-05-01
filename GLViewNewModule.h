#pragma once

#include "GLView.h"
#include <irrKlang.h>
#include "NetMessengerClient.h"
#include "../cwin64/WOdriving.h"
#include "WO.h"

using namespace irrklang;
namespace Aftr
{
   class Camera;

/**
   \class GLViewNewModule
   \author Scott Nykl 
   \brief A child of an abstract GLView. This class is the top-most manager of the module.

   Read \see GLView for important constructor and init information.

   \see GLView

    \{
*/

class GLViewNewModule : public GLView
{
public:

	//Initialization of game objects and strings
	WO* open;
	WO* slide;
	WO* lift;
	WO* end;
	WO* key;
	WO* card;
	WO* remote;
	WO* car;
	WO* usb;
	WO* gas;

	int keyo = 0;
	int cards = 0;
	int remotel = 0;
	int escape_items = 0;

   WOdriving* orca;
   static GLViewNewModule* New( const std::vector< std::string >& outArgs );
   virtual ~GLViewNewModule();
   virtual void updateWorld(); ///< Called once per frame
   virtual void loadMap(); ///< Called once at startup to build this module's scene
   virtual void createNewModuleWayPoints();
   virtual void onResizeWindow( GLsizei width, GLsizei height );
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
   virtual void onKeyUp( const SDL_KeyboardEvent& key );
   float move = 0;
   void adjust(const Vector& x) { orca->moveRelative(x); };
   Vector getLookDirection() { return orca->getLookDirection(); };

protected:
   GLViewNewModule( const std::vector< std::string >& args );
   virtual void onCreate();   
   ISoundEngine* Engine = nullptr; 
   
 
private:
	bool isMoving();
	NetMessengerClient* net;
};

/** \} */

} //namespace Aftr