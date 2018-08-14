#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/vec3.hpp>

struct Camera {

    Camera(std::string const& name, double fox_x);
    Camera(std::string const& name, double fox_x, glm::vec3 const& eye, glm::vec3 const& dir, glm::vec3 const& up);

    std::string name_;
    double fox_x_;
    glm::vec3 eyePos_;
    glm::vec3 direction_;
    glm::vec3 upVector_;
    

};
#endif