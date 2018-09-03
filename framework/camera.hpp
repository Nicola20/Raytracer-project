#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ray.hpp"
#include <string>
#include <glm/vec3.hpp>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <math.h>
#include "glm/gtc/matrix_transform.hpp"

struct Camera {

    Camera();
    Camera(std::string const& name, float fov_x);
    Camera(std::string const& name, float fov_x, glm::vec3 const& eye, glm::vec3 const& dir, glm::vec3 const& up);
    std::ostream& print (std::ostream& os) const;
    Ray calculateCamRay(int x, int y, unsigned int width, unsigned int height) const;


    std::string name_;
    float fov_x_;
    glm::vec3 eyePos_;
    glm::vec3 direction_;
    glm::vec3 upVector_;
    glm::mat4 transform_;
    glm::mat4 transformInv_;

    

};

std::ostream& operator<<(std::ostream& os, Camera const& cam);
#endif
