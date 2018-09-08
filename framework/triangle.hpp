#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <glm/vec3.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <cmath>

class Triangle: public Shape {

public:
	//Triangle();
	Triangle(glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3, std::string const& name, std::shared_ptr<Material> const& mat);

	std::ostream& print(std::ostream& os) const override;
	Hit intersect(Ray const& inray) override;

private:
	glm::vec3 p1_;
	glm::vec3 p2_;
	glm::vec3 p3_;
	glm::vec3 normal_;


};
#endif 