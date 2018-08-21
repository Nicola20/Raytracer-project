#include "camera.hpp"
#include <glm/vec4.hpp>

Camera::Camera ():
    name_{"default camera"},
    fox_x_{45.0},
    eyePos_{0.0f, 0.0f, 0.0f},
    direction_{0.0f, 0.0f, -1.0f},
    upVector_{0.0f, 1.0f, 0.0f} {}



Camera::Camera (std::string const& name, float fox_x):
    name_{name},
    fox_x_{fox_x},
    eyePos_{0.0f, 0.0f, 0.0f},
    direction_{0.0f, 0.0f, -1.0f},
    upVector_{0.0f, 1.0f, 0.0f}  {}

Camera::Camera(std::string const& name, float fox_x, glm::vec3 const& eye, glm::vec3 const& dir, glm::vec3 const& up):
    name_{name},
    fox_x_{fox_x},
    eyePos_{eye},
    direction_{dir},
    upVector_{up} {}


Ray Camera::calculateCamRay(int x, int y, unsigned int width, unsigned int height) {
    glm::vec3 viewpoint{(float(x)/(float(width)))-0.5f, (float(y)/(float(height)))- 0.5f, (-1.0f*(0.5f/tan(fox_x_/2)))};
    Ray camRay {eyePos_,viewpoint};
    return camRay;
}

 std::ostream& Camera::print(std::ostream& os) const {
    os << "Camera: " << name_<<"\n" 
        "fox_x: " << fox_x_ << 
        "eyePosition: ( " << eyePos_.x << ", " <<
        eyePos_.y << ", " << eyePos_.z << ") \n"
        "Blickrichtung: (" << direction_.x << ", " <<
        direction_.y << ", " << direction_.z << " ) \n"
        "UpVector: () " << upVector_.x << ", " <<
        upVector_.y << ", " << upVector_.z << " )" << "\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, Camera const& cam) {
    return cam.print(os);
}
