#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/vec3.hpp>

struct Camera {

    Camera(std::string const& name, double fox_x);

    glm::vec3 upVector_;
    glm::vec3 direction_;
    glm::vec3 eyePos_;
    double fox_x_;
    std::string name_;


};
#endif