#ifndef SCENE_HPP
#define SCENE_HPP

#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "triangle.hpp"
#include "color.hpp"
#include "composite.hpp"
#include "lightsource.hpp"
#include "camera.hpp"
#include "material.hpp"
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>


struct Scene {

std::ostream& print (std::ostream& os) const{
        os << "Ambient: (" << ambient_.r<< ", "<< ambient_.g<< ", "<<ambient_.b<<" ) \n"
        <<"Frame: (" << width_ << " x "<< height_ <<") \n"
        <<"Camera: " << cam_.name_ << "\n"
        <<"File: " << fileOut_ <<"\n";
    return os;
} 

 friend std::ostream& operator<<(std::ostream& os, Scene const& s){
    return s.print(os);
}

   
    Color ambient_; //Ambient
    std::map<std::string, std::shared_ptr<Material>> map_mat;
    float width_;
    float height_;
    std::shared_ptr<Composite> composite_;
    //std::map<std::string, std::shared_ptr<Shape>> sceneshapes;
    std::vector<std::shared_ptr<Lightsource>> light_;
    Camera cam_;
    std::string fileOut_;

};
#endif
