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

Hit Sphere::intersect(Ray const& inray) {
 
    Hit hit;
    Ray ray;
    float t = 0.0f;

   if (transformed_) {
        ray = transformRay(world_transformation_inv_,inray);
    } else {
        ray = inray;
    }

    if (glm::intersectRaySphere(ray.origin_, glm::normalize(ray.direction_), center_, radius_*radius_, t)) {//wird hier automatisch das kleinste t genommen?
        hit.hit_ = true;
        hit.intersection_ = (ray.origin_ + t*glm::normalize(ray.direction_)); //muss irgendwo direction noch normalisiert werden?
        hit.distance_ = t; 
        hit.closest_shape_ = this;
        hit.normal_ = glm::normalize(hit.intersection_ - center_);
    }

    if (transformed_) {
        hit.normal_ = glm::vec3(glm::mat3(glm::transpose(world_transformation_inv_))*hit.normal_); 
    }

    return hit;

} 

/*Hit Sphere::intersect(Ray const& inray) 
{	
	Hit sphereHit;
	Ray ray;
    if (isTransformed()) {
        ray = transformRay(world_transformation_inv_,inray);
    } else {
        ray = inray;
    }
	
	glm::vec3 l = ray.direction_;
	glm::vec3 o = ray.origin_;
	glm::vec3 c = center_;
	float	  r = radius_;
	float underroot = ( skalar(l , (o - c)) * skalar(l , (o - c))) - ((glm::length(o - c) * glm::length(o - c))) + (r*r); //=der bums unter der wurzel
	if( underroot > 0 )
	{
		float root = std::min(sqrt(underroot),-sqrt(underroot));
		float t = (- skalar(l , (o - c))) + root;
		if(t > 0) //strahl schneidet in positiver richtung
		{
			glm::vec3 object_position = o + t * l;
			glm::vec3 normal = glm::normalize(object_position - center_);
            
			glm::vec3 world_position{world_transformation_  * glm::vec4{object_position,1} };
			glm::vec4 world_normal{world_transformation_inv_ * glm::vec4{normal  ,0} };

			sphereHit.intersection_ = object_position;

            //Hit sphereHit;
			sphereHit.hit_ = true;
            sphereHit.closest_shape_ = this;
			sphereHit.intersection_ = world_position; //glm::vec3{world_position.x, world_position.y, world_position.z};
			sphereHit.normal_ =glm::vec3{world_normal.x  , world_normal.y  , world_normal.z  };
			sphereHit.distance_ =t;
		    if (isTransformed()) {
                sphereHit.normal_ = glm::vec3(glm::mat3(glm::transpose(world_transformation_inv_))*sphereHit.normal_); 
            }
        
		    //sphereHit.transformHit(world_transformation, world_transformation_inv);
		    return sphereHit;
		}
	}

	return Hit{};
}

inline float Sphere::skalar(glm::vec3 const& a,glm::vec3 const& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
*/