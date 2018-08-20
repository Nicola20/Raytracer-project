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

std::ostream& Composite::print(std::ostream& os) const {
  for (auto const& shape : shapes_) {
    shape -> print(os); 
    os << "\n";
  }
  return os;
}

Hit Composite::intersect (Ray const& ray) {

    Hit closestHit;
    Hit currentHit;

    for (auto const& s : shapes_) {
       currentHit = s -> intersect(ray);
       if (currentHit.distance_ < closestHit.distance_){ //check if currentHit is nearer if so then it is the closest
           closestHit = currentHit;
       }
    }
    return closestHit;
}