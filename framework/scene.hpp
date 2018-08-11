#ifndef SCENE_HPP
#define SCENE_HPP

#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "color.hpp"
#include <string>
#include <vector>
#include <map>
#include <set>


struct Scene {
    Color ia;
    std::map<std::string, std::shared_ptr<Material>> map_mat;


};
#endif