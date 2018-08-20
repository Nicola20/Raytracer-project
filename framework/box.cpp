#include "box.hpp"
#include <math.h>
#include <algorithm>
#include <catch.hpp>

Box::Box (glm::vec3 const& min, glm::vec3 const& max,std::string const& name, std::shared_ptr<Material> const& mat):
    Shape::Shape(name, mat),
    min_{min},
    max_{max} {
        std::cout << "ctor of derived class Box \n";
    }

Box::Box():
    Shape::Shape{},
    min_{0.0f, 0.0f, 0.0f},
    max_{1.0f, 1.0f, 1.0f} { }
    

Box::~Box(){
    std::cout << "dtor of derived class Box \n";
}

glm::vec3 Box::getMin() const{
    return min_;
}

glm::vec3 Box::getMax() const {
    return max_;
}
/*
//calculates the surface
double Box::area() const {
    double a = max_.z - min_.z;  //diference on z-axsis; + because max_ has a negative value
    double b = max_.y - min_.y;  //diference on y axsis
    double c = max_.x - min_.x;  //diference on x axis

    return a*b*c;

}

//calculates the volume
double Box::volume() const {
    double a = max_.z - min_.z;  //diference on z-axsis; + because max_ has a negative value
    double b = max_.y - min_.y;  //diference on y axsis
    double c = max_.x - min_.x;  //diference on x axis

    return 2*(a*b + b*c + a*c);

} */

std::ostream& Box::print(std::ostream& os) const {
    Shape::print(os);
    os << "Vector max_: (" << max_.x << "," << max_.y << "," << max_.z << "), \n" << "Vector min_: (" << min_.x << "," << min_.y << "," << min_.z << ") \n \n";
    return os;
}

Hit Box::intersect (Ray const& ray) {

    Hit hit;
    //Ray ray = rayn; //anders wenn transformation eintrifft

    float tx1 = (min_.x - ray.origin_.x)/ray.direction_.x;
    float tx2 = (max_.x - ray.origin_.x)/ray.direction_.x;
    //float tmin = std::min(tx1, tx2);
    //float tmax = std::max(tx1, tx2);

    float ty1 = (min_.y - ray.origin_.y)/ray.direction_.y;
    float ty2 = (max_.y - ray.origin_.y)/ray.direction_.y;
    //tmin = std::max(tmin,std::min(ty1, ty2));
    //tmax = std::min(tmax, std::max(ty1, ty2));

    float tz1 = (min_.z - ray.origin_.z)/ray.direction_.z;
    float tz2 = (max_.z - ray.origin_.z)/ray.direction_.z;
    //tmin = std::max(tmin, std::min(tz1, tz2));
    //tmax = std::min(tmax, std::max(tz1, tz2));

    float tmin = std::max(std::max(std::min(tx1, tx2), std::min(ty1, ty2)), std::min(tz1, tz2));
    float tmax = std::min(std::min(std::max(tx1, tx2), std::max(ty1, ty2)),std::max(tz1, tz2));
/*
// if tmax < 0, ray is intersecting, but the whole thing is behind us
if (tmax < 0)
{
    return false;
}

// if tmin > tmax, ray doesn't intersect 
if (tmin > tmax)
{
    return false;
}

 t = std::abs(tmin);
return true; */
    if (tmax > std::max(0.0f, tmin)) {

        hit.hit_ = true;
        hit.distance_ = std::abs(tmin); //really not quite sure if this is true or if the ddistance between vectors has to be here

        //hab ich so in nem Paper gefunden
        hit.intersection_ = glm::vec3 (ray.origin_.x + ray.direction_.x*tmin,ray.origin_.y + 
                                        ray.direction_.y*tmin, ray.origin_.z + ray.direction_.z*tmin); 

        hit.closest_shape_ = this;

        //berechnung der normalisierten Vektoren
        if (hit.intersection_.x == Approx(min_.x)) {
            hit.normal_ =glm::vec3(-1.0f, 0.0f, 0.0f); //why though?
        } 
        if (hit.intersection_.x == Approx(max_.x)) {
            hit.normal_ =glm::vec3(1.0f, 0.0f, 0.0f); 
        }
        if (hit.intersection_.y == Approx(min_.y)) {
            hit.normal_ =glm::vec3(0.0f, -1.0f, 0.0f); //why though?
        }
        if (hit.intersection_.y == Approx(max_.y)) {
            hit.normal_ =glm::vec3(0.0f, 1.0f, 0.0f); //why though?
        }
        if (hit.intersection_.z == Approx(min_.z)) {
            hit.normal_ =glm::vec3(0.0f, 0.0f, -1.0f); //why though?
        }
        if (hit.intersection_.z == Approx(max_.z)) {
            hit.normal_ =glm::vec3(0.0f, 0.0f, 1.0f); //why though?
        }
    }

    return hit;
} 
