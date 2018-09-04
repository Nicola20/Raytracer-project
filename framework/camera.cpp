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
    transform_{},
    transformInv_{glm::inverse(transform_)}  {}

Camera::Camera(std::string const& name, float fov_x, glm::vec3 const& eye, glm::vec3 const& dir, glm::vec3 const& up):
    name_{name},
    fov_x_{fov_x},
    eyePos_{eye},
    direction_{dir},
    upVector_{up},
    transform_{},
    transformInv_{glm::inverse(transform_)} {}


Ray Camera::calculateCamRay(int x, int y, unsigned int width, unsigned int height) const {
    
    glm::vec3 direction{ ((float(x)/(float(width))) - 0.5) , 
                         ((float(y)/(float(height)))- 0.5) , 
                        (-1.0f*(0.5f/tan(fov_x_/2)))};

    direction = glm::normalize(direction);
    Ray camRay {eyePos_,direction};
    return camRay; //hier möglicherweise Änderungen vornehmen
}

void Camera::translate(glm::vec3 const& vec){
    glm::mat4 translationMat;
	translationMat[0] = glm::vec4{ 1.0f, 0.0f, 0.0f, 0.0f };
	translationMat[1] = glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f };
	translationMat[2] = glm::vec4{ 0.0f, 0.0f, 1.0f, 0.0f };
	translationMat[3] = glm::vec4{ vec, 1.0f };
	camTranslate_ = translationMat;

	glm::mat4 trInverse;
	trInverse[0] = glm::vec4{ 1.0f, 0.0f, 0.0f, 0.0f };
	trInverse[1] = glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f };
	trInverse[2] = glm::vec4{ 0.0f, 0.0f, 1.0f, 0.0f };
	trInverse[3] = glm::vec4{ -vec, 1.0f };

	transform_ = camTranslate_*camRotate_; //das hier muss noch angepasst werden in richtiger Reihenfolge mit translate etc.
	transformInv_ = transformInv_*trInverse;
	//transformed_ = true;

}

void Camera::rotate(float phi, glm::vec3 const& vec) {
    float rad = glm::radians(phi);
	camRotate_ = glm::rotate(glm::mat4(1.0), rad, vec);
	transform_ = camTranslate_*camRotate_;
	transformInv_ = transformInv_*(glm::rotate(glm::mat4(1.0),-rad, vec));
	//transformed_ = true;

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
