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
/*
//calculates the surface
double Sphere::area() const{
    return ((4/3.0f)*M_PI*pow(radius_,3));
}

//calculates the volume
double Sphere::volume() const {
    return (4*M_PI*pow(radius_,2));
}*/

std::ostream& Sphere::print(std::ostream& os) const {
    Shape::print(os);
    os << "Radius: " << radius_ << ",\nCenter point: (" << center_.x << "," << center_.y << "," << center_.z << ") \n \n";
    return os;
} 

Hit Sphere::intersect(Ray const& ray) {
 
    Hit hit;
    float t = 0.0f;

    if (glm::intersectRaySphere(ray.origin_, glm::normalize(ray.direction_), center_, radius_*radius_, t)) {//wird hier automatisch das kleinste t genommen?
        hit.hit_ = true;
        hit.intersection_ = (ray.origin_ + t*glm::normalize(ray.direction_)); //muss irgendwo direction noch normalisiert werden?
        hit.distance_ = t; 
        hit.closest_shape_ = this;
        hit.normal_ = glm::normalize(hit.intersection_ - center_); 

    }
    return hit;

} 
