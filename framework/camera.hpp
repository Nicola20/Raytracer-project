#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/vec3.hpp>
#include <iostream>

struct Camera {

    Camera();
    Camera(std::string const& name, float fox_x);
    Camera(std::string const& name, float fox_x, glm::vec3 const& eye, glm::vec3 const& dir, glm::vec3 const& up);
    std::ostream& print (std::ostream& os) const;


    std::string name_;
    float fox_x_;
    glm::vec3 eyePos_;
    glm::vec3 direction_;
    glm::vec3 upVector_;
    

};

std::ostream& operator<<(std::ostream& os, Camera const& cam);
#endif
