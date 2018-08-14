#include "camera.hpp"

Camera::Camera (std::string const& name, double fox_x) :
    upVector_{0.0f, 1.0f, 0.0f},
    direction_{0.0f, 0.0f, -1.0f},
    eyePos_{0.0f, 0.0f, 0.0f},
    fox_x_{fox_x},
    name_{name} {}
