#ifndef SDFLOADER_HPP
#define SDFLOADER_HPP

#include "scene.hpp"
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

class SDFLoader {
   //nothing to put here
   public: 
   Scene loadFile(std::string const& fileIn); 
};

//std::shared_ptr<Material> materialMapSearch (std::string name, Scene& scene);

#endif
