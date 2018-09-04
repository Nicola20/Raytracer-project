#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include "ray.hpp"
#include <glm/vec3.hpp>
#include <memory>
#include <cmath>

class Box: public Shape {

    public:
    Box (glm::vec3 const& min, glm::vec3 const& max,std::string const& name, std::shared_ptr<Material> const& mat);
    Box ();
    //double area() const override;  //calculates the surface
    //double volume() const override;  //calculates the volume
    glm::vec3 getMax() const;
    glm::vec3 getMin() const;
    std::ostream& print(std::ostream& os) const override;
     ~Box() override;
     //~Box();
     Hit intersect(Ray const& inray) override;
	 Hit surfacehit(Ray const& ray, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4)const;
	// inline glm::vec3 cross(glm::vec3 const& v1, glm::vec3 const& v2)const;
	// float skalar(glm::vec3 const& a, glm::vec3 const& b) const;
	 
	 
    private:
    glm::vec3 max_;
    glm::vec3 min_;

};
#endif // BOX_HPP

