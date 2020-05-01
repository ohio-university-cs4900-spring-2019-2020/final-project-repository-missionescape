#include "NetMsgOrca.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include <iostream>
#include <sstream>
#include <string>
#include "AftrManagers.h"
#include "Vector.h"
#include "WO.h"
#include "GLView.h"
#include "WorldContainer.h"
#include "Model.h"
#include "WOLight.h"
#include "GLViewNewModule.h"
#include "WOdriving.h"

using namespace Aftr;
using namespace std;

NetMsgMacroDefinition(NetMsgOrca);

NetMsgOrca::NetMsgOrca(const Vector& pos, const Vector& dir) {
	this->position = pos;
	this->direction = dir;
}

NetMsgOrca::~NetMsgOrca() {}

bool NetMsgOrca::toStream(NetMessengerStreamBuffer& os) const {
	os << this->position.x << this->position.y << this->position.z;
	os << this->direction.x << this->direction.y << this->direction.z;
	return true;
}

bool NetMsgOrca::fromStream(NetMessengerStreamBuffer& is) {
	is >> this->position.x >> this->position.y >> this->position.z;
	is >> this->direction.x >> this->direction.y >> this->direction.z;
	return true;
}

void NetMsgOrca::onMessageArrived() {
	//((GLViewNewModule*)ManagerGLView::getGLView())->orca->setPosition(this->position);
	cout << this->toString() << endl;
}

string NetMsgOrca::toString() const {
	stringstream stream;
	stream << NetMsg::toString();
	stream << "position: " << this->position << "..." << endl;
	stream << "direction: " << this->direction << "..." << endl;
	return stream.str();
}

#endif