#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "material.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp>
#include <math.h>
#include "glm/gtc/matrix_transform.hpp"

class Shape {

    public:
    //virtual double area() const = 0;  //calculates the surface
    //virtual double volume() const = 0;  //calculates the volume
	Shape(std::string const& name, std::shared_ptr<Material> const& mat);
    Shape ();
    virtual std::ostream& print(std::ostream& os) const;
    std::string getName() const;
    std::shared_ptr<Material> getMaterial() const;
    virtual ~Shape();
    //~Shape();
    virtual Hit intersect (Ray const& inray) = 0;
    
    virtual void translate(glm::vec3 const& vec);
    virtual void scale(glm::vec3 const& vec);
    virtual void rotate(float phi, glm::vec3 const& vec);
    bool isTransformed();

    /* //not needed 
    virtual void rotateX(float phi);
    virtual void rotateY(float phi);
    virtual void rotateZ(float phi);
    */


    protected:
    std::string name_;
    std::shared_ptr<Material> material_;
    
    glm::mat4 world_transformation_;
    glm::mat4 world_transformation_inv_;
    bool transformed_;
    glm::mat4 translate_;
    glm::mat4 scale_;
    glm::mat4 rotate_; 
};

std::ostream& operator<< (std::ostream& os, Shape const& s);

#endif // SHAPE_HPP
