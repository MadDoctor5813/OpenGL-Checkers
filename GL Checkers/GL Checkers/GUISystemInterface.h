#pragma once

#include <Rocket\Core\SystemInterface.h>
class GUISystemInterface : public Rocket::Core::SystemInterface {
public:
	GUISystemInterface();
	~GUISystemInterface();

	float GetElapsedTime();
};

