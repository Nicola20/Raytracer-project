#ifndef AMBIENT_HPP
#define AMBIENT_HPP

#include <memory>

struct Ambient {

    Ambient (float red, float green, float blue): 
    r_{red}, 
    g_{green}, 
    b_{blue} {}

    float r_;
    float g_;
    float b_;
};
#endif