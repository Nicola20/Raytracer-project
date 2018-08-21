#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "material.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <string>
#include <memory>

class Shape {

    public:
    //virtual double area() const = 0;  //calculates the surface
    //virtual double volume() const = 0;  //calculates the volume
    Shape(std::string const& name,std::shared_ptr<Material> const& mat);
    Shape ();
    virtual std::ostream& print(std::ostream& os) const;
    std::string getName() const;
    std::shared_ptr<Material> getMaterial() const;
    virtual ~Shape();
    //~Shape();
    virtual Hit intersect (Ray const& ray) = 0;

    protected:
    std::string name_;
    std::shared_ptr<Material> material_;
};

std::ostream& operator<< (std::ostream& os, Shape const& s);

#endif // SHAPE_HPP
