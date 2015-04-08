#pragma once

#include <map>
#include <string>
#include <vector>

#include "Square.h"

class SaveFileManager { //Serializes and deserializes Square structs

public:
	SaveFileManager();
	~SaveFileManager();

	std::vector <std::vector<Square *> >& getSave(const std::string& name);
	void save(const std::string& name, std::vector <std::vector<Square *> >& data);

private:
	std::string saveDir = "Saves/";
	std::map <std::string, std::vector<Square *> >saves;


};


