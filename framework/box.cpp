#include "box.hpp"
#include <math.h>
#include <algorithm>
#include <catch.hpp>
#include <glm/ext.hpp>

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
/*
Hit Box::intersect (Ray const& inray) {

    Hit hit;
    Ray ray;

    if (isTransformed()) {
        ray = transformRay(world_transformation_inv_,inray);
    } else {
        ray = inray;
    }
    ray.direction_ = glm::normalize(ray.direction_);
    glm::vec3 inverse{1.0f/ray.direction_.x, 1.0f/ray.direction_.y, 1.0f/ray.direction_.z};


    float tx1 = (min_.x - ray.origin_.x)/inverse.x;
    float tx2 = (max_.x - ray.origin_.x)/inverse.x;
    //float tmin = std::min(tx1, tx2);
    //float tmax = std::max(tmin,std::min(ty1, ty2));

    float ty1 = (min_.y - ray.origin_.y)/inverse.y;
    float ty2 = (max_.y - ray.origin_.y)/inverse.y;


    float tz1 = (min_.z - ray.origin_.z)/inverse.z;
    float tz2 = (max_.z - ray.origin_.z)/inverse.z;
    //tmin = std::max(tmin, std::min(tz1, tz2));
    //tmax = std::min(tmax, std::max(tz1, tz2));

    float tmin = std::max(std::max(std::min(tx1, tx2), std::min(ty1, ty2)), std::min(tz1, tz2));
    float tmax = std::min(std::min(std::max(tx1, tx2), std::max(ty1, ty2)),std::max(tz1, tz2));

    if (tmax > std::max(0.0f, tmin)) {

        hit.hit_ = true;
        hit.distance_ = tmin;
        
        hit.distance_ = sqrt(tmin*tmin*(
                      ray.direction_.x*ray.direction_.x +
                      ray.direction_.y*ray.direction_.y +
                     ray.direction_.z*ray.direction_.z )); //oder doch eher Abstand zwischen 2 Vektoren?

        //hab ich so in nem Paper gefunden
        hit.intersection_ = glm::vec3 (ray.origin_.x + ray.direction_.x*tmin,ray.origin_.y + 
                                        ray.direction_.y*tmin, ray.origin_.z + ray.direction_.z*tmin); 

        hit.closest_shape_ = this;

        //berechnung der normalisierten Vektoren
        if (hit.intersection_.x == Approx(min_.x)) {
            hit.normal_ =glm::normalize(glm::vec3(-1.0f, 0.0f, 0.0f)); //why though?
        } 
        if (hit.intersection_.x == Approx(max_.x)) {
            hit.normal_ =glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)); 
        }
        if (hit.intersection_.y == Approx(min_.y)) {
            hit.normal_ =glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)); //why though?
        }
        if (hit.intersection_.y == Approx(max_.y)) {
            hit.normal_ =glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)); //why though?
        }
        if (hit.intersection_.z == Approx(min_.z)) {
            hit.normal_ =glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)); //why though?
        }
        if (hit.intersection_.z == Approx(max_.z)) {
            hit.normal_ =glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)); //why though?
        }

        if (isTransformed()) {
            hit.normal_ = glm::vec3(glm::mat3(glm::transpose(world_transformation_inv_))*hit.normal_); 
        }
    }


    return hit;
}*/ 


Hit Box::intersect(Ray const& inray) {

	Ray ray;
	if (isTransformed()) {
		ray = transformRay(world_transformation_inv_, inray);
	}
	else {
		ray = inray;
	}
	if (min_.x > max_.x)std::swap(min_.x, max_.x);
	if (min_.y > max_.y)std::swap(min_.y, max_.y);
	if (min_.z > max_.z)std::swap(min_.z, max_.z);

	Hit hit[6];
	hit[0] = surfacehit(ray,glm::vec3{ max_.x,max_.y,max_.z }, glm::vec3{ max_.x,min_.y,max_.z }, glm::vec3{ min_.x,min_.y,max_.z }, glm::vec3{ min_.x,max_.y,max_.z });
	//back:
	hit[1] = surfacehit(ray,glm::vec3{ min_.x,min_.y,min_.z }, glm::vec3{ max_.x,min_.y,min_.z }, glm::vec3{ max_.x,max_.y,min_.z }, glm::vec3{ min_.x,max_.y,min_.z });
	//right
	hit[2] = surfacehit(ray, glm::vec3{ max_.x,max_.y,max_.z }, glm::vec3{ max_.x,max_.y,min_.z }, glm::vec3{ max_.x,min_.y,min_.z }, glm::vec3{ max_.x,min_.y,max_.z });
	//left
	hit[3] = surfacehit(ray, glm::vec3{ min_.x,min_.y,min_.z }, glm::vec3{ min_.x,max_.y,min_.z }, glm::vec3{ min_.x,max_.y,max_.z }, glm::vec3{ min_.x,min_.y,max_.z });
	//top
	hit[4] = surfacehit(ray, glm::vec3{ max_.x,max_.y,max_.z }, glm::vec3{ min_.x,max_.y,max_.z }, glm::vec3{ min_.x,max_.y,min_.z }, glm::vec3{ max_.x,max_.y,min_.z });
	//bottom
	hit[5] = surfacehit(ray, glm::vec3{ min_.x,min_.y,min_.z }, glm::vec3{ min_.x,min_.y,max_.z }, glm::vec3{ max_.x,min_.y,max_.z }, glm::vec3{ max_.x,min_.y,min_.z });
	//front 
	Hit nearest;


	for (int i = 0; i < 6; i++) {
		if (hit[i].hit_ && 0.0001 < hit[i].distance_ && hit[i].distance_ < nearest.distance_) {
			nearest = hit[i];
		}
	}
	if (nearest.hit_) {
		nearest.closest_shape_ = this;
		if (isTransformed()) {
			nearest.normal_ = glm::vec3(glm::mat3(glm::transpose(world_transformation_inv_))*nearest.normal_);
		}
		return nearest;
	}
	else
	{
		return Hit{};
	}
}

Hit Box::surfacehit(Ray const& ray, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4)const {
	Hit hit;
	glm::vec3 norm{ glm::normalize(glm::cross(p4 - p1,p2 - p1)) };
	float denominator = glm::dot(norm, ray.direction_);
	if (denominator != 0) {
		float distance = (-(norm.x*(ray.origin_.x - p1.x)) - (norm.y*(ray.origin_.y - p1.y))
			- (norm.z*(ray.origin_.z - p1.z))) / denominator;//ebenenintersect

		if (distance > 0.001)
		{
			glm::vec3 object_position = ray.origin_ + (distance * ray.direction_);

			glm::vec3 world_position{ world_transformation_ * glm::vec4{ object_position,1 } };
			glm::vec4 world_normal{ world_transformation_inv_* glm::vec4{ norm  ,0 } };

			hit.intersection_ = object_position;
			{
				if (glm::dot(p4 - p1, p1 - hit.intersection_) <= 0 && glm::dot(p1 - p2, p2 - hit.intersection_) <= 0 && glm::dot(p2 - p3, p3 - hit.intersection_) <= 0 && glm::dot(p3 - p4, p4 - hit.intersection_) <= 0)
				{//fl�chenbegrenzung
					hit.intersection_ = world_position;
					hit.hit_ = true;
					hit.normal_ = glm::vec3{ world_normal.x,world_normal.y,world_normal.z };
					hit.distance_ = distance;
				}
			}
		}
	}
	if (hit.hit_) {
		return hit;
	}
	else { return Hit{}; }
}

