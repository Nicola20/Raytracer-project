# ifndef SPHERE_HPP
# define SPHERE_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"
//#include "ray.hpp"

class Sphere: public Shape {

    public:
    Sphere (glm:: vec3 const& c, double r, std::string const& name, std::shared_ptr<Material> const& mat);
    //double area() const override;  //calculates the surface
    //double volume() const override;  //calculates the volume
    glm::vec3 getCenter() const;
    double getRadius() const;
    std::ostream& print(std::ostream& os) const override;
    Hit intersect (Ray const& inray) override;
    ~Sphere() override;
    //~Sphere();

    private:
    glm::vec3 center_;
    double radius_;

};
# endif // SPHERE_HPP
