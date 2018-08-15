#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include "shape.hpp"
#include "ray.hpp"
#include <vector>
#include <string>

class Composite : public Shape {

    public:
    Composite();
    Composite (std::string const& name);
    //double area() const override;
    //double volume() const override;
    void addShape(std::shared_ptr<Shape> const& shape);
    //std::ostream& print(std::ostream& os) const override;
    // bool intersect (Ray const& ray) override; // need this but with optimal hit instead of bool

    private:
    //std::string compositeName_;  //braucht man nicht, da shapes schon n namen besitzt.So wie bei Box etc.
    std::vector<std::shared_ptr<Shape>> shapes_;

};

#endif