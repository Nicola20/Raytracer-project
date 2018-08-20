#ifndef HIT_HPP
#define HIT_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>
#include <memory>

class Shape;

struct Hit {

    Hit():
        hit_{false},
        distance_{INFINITY},
        normal_{},
        intersection_{},
        closest_shape_{nullptr} {}

    Hit(bool hit, float distance, glm::vec3 const& normalvec, glm::vec3 const& intersect, Shape* const& clos):
        hit_{hit},
        distance_{distance},
        normal_{normalvec},
        intersection_{intersect},
        closest_shape_{clos} {}

    Hit(Hit const& tmp):
        hit_{tmp.hit_},
        distance_{tmp.distance_},
        normal_{tmp.normal_},
        intersection_{tmp.intersection_},
        closest_shape_{tmp.closest_shape_} {}


    bool hit_;
    float distance_;
    glm::vec3 normal_;
    glm::vec3 intersection_;
    Shape* closest_shape_;


};
#endif
