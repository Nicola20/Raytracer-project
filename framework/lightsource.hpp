#ifndef LIGHTSOURCE_HPP
#define LIGHTSOURCE_HPP

#include <glm/vec3.hpp>
#include <string>
#include "color.hpp"
//#include "ambient.hpp"
#include <memory>
#include <iostream>

struct Lightsource {

Lightsource(std::string const& name, glm::vec3 const& pos, Color const& col, int ip):
    name_{name},
    position_{pos},
    lightcol_{col},
    ip_{ip}  {}


friend std::ostream& operator<< (std::ostream& os, Lightsource const& light) {
    os << "Name: " << light.name_ << "\n"
  << "Position: " << "(" << light.position_.x << ", "
  << light.position_.y << ", "<< light.position_.z << ") \n"
  << "Lichtfarbe: ( " << light.lightcol_.r << ", " << light. lightcol_.g 
  << ", " << light.lightcol_.b <<" )" << "\n"
  << "Diffuse Light (Point Light): " << light.ip_ << "\n";  
  //<< "Ambient Light: " << *ia_ << "\n";
  return os;
}


std::string name_;
glm::vec3 position_;
Color lightcol_;
int ip_;  //Helligkeit
//std::shared_ptr<Ambient> ia_; //vllt. besser dies extra als struct zu definieren um als shared_ptr zu dienen, da es pro Scene nur ein Mal existiert

};
#endif
