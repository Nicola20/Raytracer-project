#ifndef SDFFILELOADER_HPP
#define SDFFILELOADER_HPP

#include "scene.hpp"
#include <string>
#include <algorithm>
#include <fstream>

struct SDFLoader {
    
    void loadfile(std::string const& fileIn, Scene& scene);
};
#endif
