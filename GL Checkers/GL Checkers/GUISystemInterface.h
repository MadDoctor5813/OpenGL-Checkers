#pragma once

#include <Rocket\Core\SystemInterface.h>
class GUISystemInterface : Rocket::Core::SystemInterface {
public:
	GUISystemInterface();
	~GUISystemInterface();

	float GetElapsedTime();
};

