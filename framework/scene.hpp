#ifndef SCENE_HPP
#define SCENE_HPP

#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "color.hpp"
#include "composite.hpp"
#include "lightsource.hpp"
#include "camera.hpp"
#include <string>
#include <vector>
#include <map>


struct Scene {
   
    Color ia_; //Ambient
    std::map<std::string, std::shared_ptr<Material>> map_mat;
    float width_;
    float heigth_;
    std::shared_ptr<Composite> composite_;
    std::vector<Lightsource> light_;
    Camera cam_;


};
#endif