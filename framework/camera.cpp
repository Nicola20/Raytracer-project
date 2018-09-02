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


Ray Camera::calculateCamRay(int x, int y, unsigned int width, unsigned int height) const {
    
    glm::vec3 direction{ ((float(x)/(float(width))) - 0.5) , 
                         ((float(y)/(float(height)))- 0.5) , 
                        (-1.0f*(0.5f/tan(fox_x_/2)))};

    direction = glm::normalize(direction);
    Ray camRay {eyePos_,direction};
    return camRay;
    /*
    float imageAspectRatio = width / float(height); // assuming width > height
    float px = (2 * ((x + 0.5) / width) - 1) * tan(fox_x_ / 2 * M_PI / 180) * imageAspectRatio;
    float py = (1 - 2 * ((y + 0.5) / height) * tan(fox_x_ / 2 * M_PI / 180));

    glm::vec3 pixelvec{px, py, -1.0f};

    glm::vec3 raydirection = pixelvec-eyePos_;

    Ray camRay {eyePos_, glm::normalize(raydirection)};
    return camRay;*/
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
