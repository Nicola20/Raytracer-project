#ifndef LIGHTSOURCE_HPP
#define LIGHTSOURCE_HPP

#include <glm/vec3.hpp>
#include <string>
#include "color.hpp"
#include "ambient.hpp"
#include <memory>
#include <iostream>

struct Lightsource {

Lightsource(std::string const& name, glm::vec3 const& pos, Color const& ip, std::shared_ptr<Ambient> const& ia):
    name_{name},
    position_{pos},
    ip_{ip},
    ia_{ia} {}


std::ostream& printLight(std::ostream& os) const {
  os << "Name: " << name_ << "\n"
  << "Position: " << "(" << position_.x << ", "
  << position_.y << ", "<< position_.z << ") \n"
  << "Diffuse Light (Point Light): " << ip_ << "\n"  
  << "Ambient Light: " << *ia_ << "\n";
  return os;
}

std::ostream& operator<< (std::ostream& os, Lightsource const& light){
    return light.printLight(os);
}


std::string name_;
glm::vec3 position_;
Color ip_;  //Helligkeit
std::shared_ptr<Ambient> ia_; //vllt. besser dies extra als struct zu definieren um als shared_ptr zu dienen, da es pro Scene nur ein Mal existiert

};
#endif
