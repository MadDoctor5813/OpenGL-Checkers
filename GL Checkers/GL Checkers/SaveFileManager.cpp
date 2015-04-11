#include "SaveFileManager.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <cereal\cereal.hpp>
#include <cereal\archives\binary.hpp>

namespace fs = std::tr2::sys;

