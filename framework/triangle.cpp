#include "triangle.hpp"


Triangle::Triangle(glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3, std::string const& name,std::shared_ptr<Material> const& mat) :
	Shape::Shape{name, mat},
	p1_{p1},
	p2_{p2},
	p3_{p3},
	normal_ {}
{normal_ = glm::cross(p3_ - p1_, p2_ - p1_); }

//Triangle::Triangle(): {}

std::ostream& Triangle::print(std::ostream& os) const
{
	Shape::print(os);
	os << "e1: ("
		<< p1_.x << ", "
		<< p1_.y << ", "
		<< p1_.z << ") , e2: ("
		<< p2_.x << ", "
		<< p2_.y << ", "
		<< p2_.z << ") , e3: ("
		<< p3_.x << ", "
		<< p3_.y << ", "
		<< p3_.z << ")" << std::endl;
        return os;
}
/*
Hit Triangle::intersect(Ray const& inray) {
	Hit hit;
	Ray ray;
	if (transformed_) {
		ray = transformRay(world_transformation_inv_, inray);
	}
	else {
		ray = inray;
	}

	float denominator = glm::dot(normal_, ray.direction_);
	if (denominator != 0) {
		float distance = (-(normal_.x*(ray.origin_.x - p1_.x)) - (normal_.y* (ray.origin_.y - p1_.y)) -
			(normal_.z*(ray.origin_.z - p1_.z)));

		if (distance > 0) {
			glm::vec3 object_position = ray.origin_ + (distance * ray.direction_);
			
			glm::vec3 world_position{ world_transformation_ *glm::vec4{object_position, 1} };
			glm::vec4 world_normal{ world_transformation_inv_ * glm::vec4{normal_, 0} };

			hit.intersection_ = object_position;

			if (glm::dot(p3_ - p1_, p1_ - hit.intersection_) <= glm::dot(p3_ - p1_, p2_ - p1_) 
                && glm::dot(p1_ - p2_, p2_ - hit.intersection_) <= glm::dot(p1_ - p2_, p3_ - p2_) 
                && glm::dot(p2_ - p3_, p3_ - hit.intersection_) <= glm::dot(p2_ - p3_, p1_ - p3_))
			{
				hit.intersection_ = world_position;
				hit.hit_ = true;
				hit.normal_ = normal_;
				hit.closest_shape_ = this;
				hit.distance_ = distance;
			}
		}
	}
		if (transformed_) {
		hit.normal_ = glm::vec3(glm::mat3(glm::transpose(world_transformation_inv_))*hit.normal_);
	}
	return hit;
}
*/


Hit Triangle::intersect(Ray const& inray)
{
	Hit triangle_hit;

	Ray ray {inray.origin_, glm::normalize(inray.direction_)};

		glm::vec3 a_b = p2_ - p1_;
		glm::vec3 a_c = p3_ - p1_;
		glm::vec3 normal = glm::cross(a_b, a_c);

		float NdotRayDirection = glm::dot(normal, ray.direction_);

	if (fabs(NdotRayDirection) == 0)
	{return triangle_hit;}
		
		float d = glm::dot(normal, p1_);
		float t = (glm::dot(normal, ray.origin_) + d) / NdotRayDirection;

	if (t < 0)
	{return triangle_hit;}
	
		glm::vec3 p = ray.origin_ + t * ray.direction_;
		glm::vec3 c;
		glm::vec3 edge_0 = p2_ - p1_;
		glm::vec3 vp0 = p - p1_;
		c = glm::cross(edge_0, vp0);

	if (glm::dot(normal, c) < 0)
	{return triangle_hit;}
		
		glm::vec3 edge_1 = p3_ - p2_;
		glm::vec3 vp1 = p - p2_;
		c = glm::cross(edge_1, vp1);

	if (glm::dot(normal, c) < 0)
	{return triangle_hit;}


		glm::vec3 edge_2 = p1_ - p3_;
		glm::vec3 vp2 = p - p3_;
		c = glm::cross(edge_2, vp2);

	if (glm::dot(normal, c) < 0)
	{return triangle_hit;}
		
	


	triangle_hit.distance_ = t;
	triangle_hit.hit_ = true;
	triangle_hit.closest_shape_ = this;
	triangle_hit.normal_ = glm::normalize(normal);
	triangle_hit.intersection_ = ray.origin_ + ray.direction_ * t;

	return triangle_hit;
}