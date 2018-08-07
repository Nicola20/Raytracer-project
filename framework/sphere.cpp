#include "sphere.hpp"
#include <math.h>

Sphere::Sphere (glm::vec3 const& c, double r,std::string const& name, std::shared_ptr<Material> const& mat):
    Shape::Shape(name, mat),
    center_{c},
    radius_{r} {
        std::cout << "ctor of derived class Sphere \n";
    }

Sphere::~Sphere(){
    std::cout << "dtor of derived class Sphere \n";
}

glm::vec3 Sphere::getCenter() const{
    return center_;
}

double Sphere::getRadius() const {
    return radius_;
}

//calculates the surface
double Sphere::area() const{
    return ((4/3.0f)*M_PI*pow(radius_,3));
}

//calculates the volume
double Sphere::volume() const {
    return (4*M_PI*pow(radius_,2));
}

std::ostream& Sphere::print(std::ostream& os) const {
    Shape::print(os);
    os << "Radius: " << radius_ << ",\nCenter point: (" << center_.x << "," << center_.y << "," << center_.z << ") \n \n";
    return os;
} 

bool Sphere::intersect(Ray const& ray, float& t) {
    return (glm::intersectRaySphere(ray.origin_, ray.direction_, center_, radius_*radius_, t));
} 