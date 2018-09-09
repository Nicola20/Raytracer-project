#define _USE_MATH_DEFINES
#include "camera.hpp"
#include <glm/vec4.hpp>


Camera::Camera ():
    name_{"default camera"},
    fov_x_{45.0},
    eyePos_{0.0f, 0.0f, 0.0f},
    direction_{0.0f, 0.0f, -1.0f},
    upVector_{0.0f, 1.0f, 0.0f} {}



Camera::Camera (std::string const& name, float fov_x):
    name_{name},
    fov_x_{fov_x},
    eyePos_{0.0f, 0.0f, 0.0f},
    direction_{0.0f, 0.0f, -1.0f},
    upVector_{0.0f, 1.0f, 0.0f},
    transform_{glm::mat4(1.0)},
    transformInv_{glm::mat4(1.0)},
    isTransformed_{false}  {}

Camera::Camera(std::string const& name, float fov_x, glm::vec3 const& eye, glm::vec3 const& dir, glm::vec3 const& up):
    name_{name},
    fov_x_{fov_x},
    eyePos_{eye},
    direction_{dir},
    upVector_{up},
    transform_{glm::mat4(1.0)},
    transformInv_{glm::mat4(1.0)},
    isTransformed_{false} {}


Ray Camera::calculateCamRay(int x, int y, unsigned int width, unsigned int height) const {
	double d = (width/ 2) / tan(fov_x_ / 2 * M_PI / 180);
   /* glm::vec3 direction{ ((float(x)/(float(width))) - 0.5) , 
                         ((float(y)/(float(height)))- 0.5) , 
                        (-1.0f*(0.5f/tan(fov_x_/2)))}; *///wenn hier radians, dann zoomt das Bild
	glm::vec3 direction{ x - (0.5 * width),y - (0.5 * height),-d };
    direction = glm::normalize(direction);
    Ray camRay {eyePos_,direction};

    if (isTransformed_){
        /*
        camRay.origin_ = glm::vec3(transformInv_ * glm::vec4(0, 0, 0, 1));
        camRay.direction_ = glm::vec3(transformInv_ * (glm::vec4(pos_x, pos_y, -distance, 0)));*/
        Ray ray = transformRay(transformInv_,camRay);
        return ray;
    } else {
    return camRay; //hier möglicherweise Änderungen vornehmen
    }
}

void Camera::translate(glm::vec3 const& vec){
    glm::mat4 translationMat;
	translationMat[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
	translationMat[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
	translationMat[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
	translationMat[3] = glm::vec4{vec.x, vec.y, vec.z, 1.0f};
	camTranslate_ = translationMat;
/*
	glm::mat4 trInverse;
	trInverse[0] = glm::vec4{ 1.0f, 0.0f, 0.0f, 0.0f };
	trInverse[1] = glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f };
	trInverse[2] = glm::vec4{ 0.0f, 0.0f, 1.0f, 0.0f };
	trInverse[3] = glm::vec4{ -vec, 1.0f };
*/
	transform_ = camTranslate_*camRotate_; //das hier muss noch angepasst werden in richtiger Reihenfolge mit translate etc.
	transformInv_ = transformInv_*glm::inverse(transform_);
	isTransformed_ = true;

}

void Camera::rotate(float phi, glm::vec3 const& vec) {
    float rad = glm::radians(phi);
	camRotate_ = glm::rotate(glm::mat4(1.0), rad, vec);
	transform_ = camTranslate_*camRotate_;
	transformInv_ = transformInv_*glm::inverse(transform_);
	isTransformed_ = true;

}

 std::ostream& Camera::print(std::ostream& os) const {
    os << "Camera: " << name_<<"\n" 
        "fox_x: " << fov_x_ << 
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
