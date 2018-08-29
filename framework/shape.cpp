#include "shape.hpp"


Shape::Shape(std::string const& name, std::shared_ptr<Material> const& mat):
    name_{name},
    material_{mat}{
        std::cout << "ctor of base class shape \n";
    }

Shape::Shape():
    name_{"Default Shape"},
    material_{} {}


Shape::~Shape(){                  //dtor = destructor
    std::cout << "dtor of base class Shape \n";
}


std::string Shape::getName() const {
    return name_;
}

std::shared_ptr<Material> Shape::getMaterial() const {
    return material_;
}
/*
void Shape::translate(glm::vec3 const& v) {
    glm::mat4 translationMat;
    translationMat[0] =glm::vec4 {1.0f, 0.0f, 0.0f, 0.0f};
    translationMat[1] =glm::vec4 {0.0f, 1.0f, 0.0f, 0.0f};
    translationMat[2] =glm::vec4 {0.0f, 0.0f, 1.0f, 0.0f};
    translationMat[3] =glm::vec4 {v, 1.0f};
    world_transformation_ = world_transformation*translationMat;
  	world_transformation_inv_ = glm::inverse(world_transformation_);
    transformed_ = true;

}

void Shape::scale(glm::vec3 const& s) {
    glm::mat4 scaleMat;
    scaleMat[0] =glm::vec4 {s.x, 0.0f, 0.0f, 0.0f};
    scaleMat[1] =glm::vec4 {0.0f, s.y, 0.0f, 0.0f};
    scaleMat[2] =glm::vec4 {0.0f, 0.0f, s.z, 0.0f};
    scaleMat[3] =glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};
    world_transformation_ = world_transformation*scaleMat;
  	world_transformation_inv_ = glm::inverse(world_transformation_);
    transformed_ = true;
}*/
/*
void Shape::rotateX(float phi) {
    glm::mat4 rotationMatX;
    rotationMatX[0] =glm::vec4 {1.0f, 0.0f, 0.0f, 0.0f};
    rotationMatX[1] =glm::vec4 {0.0f, cos(phi), -sin(phi), 0.0f};
    rotationMatX[2] =glm::vec4 {0.0f, sin(phi), cos(phi), 0.0f};
    rotationMatX[3] =glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};
    //hier noch was mit world_transformation machen aber noch nicht so ganz sicher was
    transformed_ = true;

}

void Shape::rotateY(float phi) {
    glm::mat4 rotationMatY;
    rotationMatY[0] =glm::vec4 {cos(phi), 0.0f, -sin(phi), 0.0f};
    rotationMatY[1] =glm::vec4 {0.0f, 1.0f, 0.0f, 0.0f};
    rotationMatY[2] =glm::vec4 {sin(phi), 0.0f, cos(phi), 0.0f};
    rotationMatY[3] =glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};
    //hier noch was mit world_transformation machen aber noch nicht so ganz sicher was
    transformed_ = true;
}

void Shape::rotateZ(float phi) {  //was ist mit Umrechnung in rad? sin rechnet mit double
    glm::mat4 rotationMatZ;
    rotationMatZ[0] =glm::vec4 {cos(phi), sin(phi), 0.0f, 0.0f};
    rotationMatZ[1] =glm::vec4 {-sin(phi), cos(phi), 0.0f, 0.0f};
    rotationMatZ[2] =glm::vec4 {0.0f, 0.0f, 1.0f, 0.0f};
    rotationMatZ[3] =glm::vec4 {0.0f, 0.0f, 0.0f, 1.0f};
    //hier noch was mit world_transformation machen aber noch nicht so ganz sicher was
    transformed_ = true;
}*/
/*
void Shape::rotate(float phi, glm::vec3 const& vec){
	float rad = glm::radians(phi);
	glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0), rad, vec);
	world_transformation_ = world_transformation*rotationMat;
  	world_transformation_inv_ = glm::inverse(world_transformation_);
    transformed_ = true;
}

bool Shape::isTransformed() {
    return transformed_;
}*/


 std::ostream& Shape::print(std::ostream& os) const{
    os << "Name: " << name_ << ", \n" << "Material: " << *material_<< "\n";
    return os;
}

std::ostream& operator<< (std::ostream& os, Shape const& s){
    return s.print(os);
}