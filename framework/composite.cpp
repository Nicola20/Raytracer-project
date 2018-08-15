#include "composite.hpp"
#include <algorithm>

Composite::Composite():
    Shape::Shape{},
    shapes_{} {}

Composite::Composite(std::string const& name):
    Shape::Shape{name,{}},
    shapes_{} {}

void Composite::addShape(std::shared_ptr<Shape> const& shape) {
    shapes_.push_back(shape);
}



//brauchen hier noch ne intersect Methode, weiß aber noch nicht so recht warum und wie