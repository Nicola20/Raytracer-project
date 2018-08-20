#ifndef SDFFILELOADER_HPP
#define SDFFILELOADER_HPP

#include "scene.hpp"
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

struct SDFLoader {
    
    Scene loadFile(std::string const& fileIn);
    
};
#endif
