#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include <string>
#include <iostream>
#include <memory>

struct Material {

Material():
    name{"DefaultMaterial"},
    ks_{0.0f, 0.0f, 0.0f},
    kd_{0.0f, 0.0f, 0.0f},
    ka_{0.0f, 0.0f, 0.0f},
    m_{1.0f},
	reflection_{false} {}

Material (std::string name, Color const& ks, Color const& kd, Color const& ka, float m, bool reflection):
    name{name},
    ks_{ks},
    kd_{kd},
    ka_{ka},
    m_{m},
	reflection_{reflection} {}

 friend std::ostream& operator<<(std::ostream& os, Material const& m){
	 os << "Material: " << m.name << "\n"
		 "ka: " << m.ka_ <<
		 "kd: " << m.kd_ <<
		 "ks: " << m.ks_ <<
		 "Spekularreflexionsexponent: " << m.m_ <<"\n"<<
		 "Reflektionsgrad:" << m.reflection_ << "\n";
    return os;
}
   

std::string name;
Color ks_;
Color kd_;
Color ka_;
float m_;
bool reflection_;

};
#endif