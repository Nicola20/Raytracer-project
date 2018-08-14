#include "shape.hpp"


Shape::Shape(std::string const& name, std::shared_ptr<Material> const& mat):
    name_{name},
    material_{mat}{
        std::cout << "ctor of base class shape \n";
    }

Shape::Shape():
    name_{"Default Shape"},
    material_{} {}


Shape::~Shape(){                  //dtor = destructor
    std::cout << "dtor of base class Shape \n";
}


std::string Shape::getName() const {
    return name_;
}


 std::ostream& Shape::print(std::ostream& os) const{
    os << "Name: " << name_ << ", \n" << "Material: " << *material_<< "\n";
    return os;
}

std::ostream& operator<< (std::ostream& os, Shape const& s){
    return s.print(os);
}