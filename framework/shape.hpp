#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "material.hpp"
#include "ray.hpp"
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
    virtual ~Shape();
    //~Shape();
    virtual bool intersect (Ray const& ray, float& t) = 0;

    protected:
    std::string name_;
    std::shared_ptr<Material> material_;
};

std::ostream& operator<< (std::ostream& os, Shape const& s);

#endif // SHAPE_HPP