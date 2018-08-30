#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "box.hpp"
#include "sphere.hpp"
#include "shape.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "sdfloader.hpp"
#include "lightsource.hpp"
#include "composite.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>


/*
TEST_CASE ("sphere_default_constructor","[default]")
{
  std::cout << "--------------------------------------------- \n";
  Sphere s1 {};
  REQUIRE (s1.getCenter().x == 0);
  REQUIRE (s1.getCenter().y == 0);
  REQUIRE (s1.getCenter().z == 0);
  REQUIRE (s1.getRadius() == 1);
  std::cout << "--------------------------------------------- \n";
}

TEST_CASE ("box_default_constructor","[default]")
{
  std::cout << "--------------------------------------------- \n";
  Box b1 {};
  REQUIRE (b1.getMax().x == 0);
  REQUIRE (b1.getMax().y == 0);
  REQUIRE (b1.getMax().z == 0);
  REQUIRE (b1.getMin().x == 0);
  REQUIRE (b1.getMin().y == 0);
  REQUIRE (b1.getMin().z == 0);
  std::cout << "--------------------------------------------- \n";
}*/
/* 
TEST_CASE ("box_constructor","[custom_constructor]")
{
  std::cout << "--------------------------------------------- \n";
  Color color{1.0f, 1.0f, 1.0f}; 
  std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);
  Box b1 {glm::vec3{1,1,1}, glm::vec3{3,8,-3}, "francine", m1};
  REQUIRE (b1.getMax().x == 3);
  REQUIRE (b1.getMax().y == 8);
  REQUIRE (b1.getMax().z == -3);
  REQUIRE (b1.getMin().x == 1);
  REQUIRE (b1.getMin().y == 1);
  REQUIRE (b1.getMin().z == 1);
  std::cout << "--------------------------------------------- \n";
}

TEST_CASE ("sphere_constructor","[sphere_constructor]")
{
  std::cout << "--------------------------------------------- \n";
  Color color{1.0f, 1.0f, 1.0f}; 
  std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);
  Sphere s1 {glm::vec3{1,1,1}, 4.0, "karl", m1};
  REQUIRE (s1.getCenter().x == 1);
  REQUIRE (s1.getCenter().y == 1);
  REQUIRE (s1.getCenter().z == 1);
  REQUIRE (s1.getRadius() == 4.0);
  std::cout << "--------------------------------------------- \n";
}*/
/*
TEST_CASE ("sphere_area","[area]")
{ 
  std::cout << "--------------------------------------------- \n";
  Color color{1.0f, 1.0f, 1.0f}; 
  std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);
  Sphere s1 {glm::vec3{1,1,1}, 4.0,"karl", m1};
  REQUIRE (s1.area() == Approx(268.0825731063));
  std::cout << "--------------------------------------------- \n";
}

TEST_CASE ("sphere_volume","[volume]")
{ 
  std::cout << "--------------------------------------------- \n";
  Color color{1.0f, 1.0f, 1.0f}; 
  std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);
  Sphere s1 {glm::vec3{1,1,1}, 4.0,"karl", m1};
  REQUIRE (s1.volume() == Approx(201.0619298297));
  std::cout << "--------------------------------------------- \n";
} 


TEST_CASE ("box_area","[area]")
{ 
  std::cout << "--------------------------------------------- \n";
  Color color{1.0f, 1.0f, 1.0f}; 
  std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);
  Box b1 {glm::vec3{1,1,1}, glm::vec3{3,8,3}, "francine", m1};
  REQUIRE (b1.area() == 28);
  std::cout << "--------------------------------------------- \n";
}

TEST_CASE ("box_volume","[volume]")
{ 
  std::cout << "--------------------------------------------- \n";
  Color color{1.0f, 1.0f, 1.0f}; 
  std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);
  Box b1 {glm::vec3{1,1,1}, glm::vec3{3,8,3}, "francine", m1};
  REQUIRE (b1.volume() == 64);
  std::cout << "--------------------------------------------- \n";
}*/ 
/*
TEST_CASE ("sphere_getter_shape","[shape_getter]")
{ 
  std::cout << "--------------------------------------------- \n";
  Sphere shapie {glm::vec3{1,1,1}, 4.0,"francine", Color{1.0f, 1.0f, 1.0f}};
  Sphere s2 {};
  REQUIRE (shapie.getName() == "francine");
  REQUIRE (shapie.getColor().r == 1.0f);
  REQUIRE (shapie.getColor().g == 1.0f);
  REQUIRE (shapie.getColor().b == 1.0f);
  REQUIRE (s2.getName() == "DefaultShape");
  REQUIRE (s2.getColor().r == 0.0f);
  REQUIRE (s2.getColor().g == 0.0f);
  REQUIRE (s2.getColor().b == 0.0f);
  std::cout << "--------------------------------------------- \n";
}  

TEST_CASE ("box_getter_shape","[shape_getter]")
{ 
  std::cout << "--------------------------------------------- \n";
  Box boxie {glm::vec3{1,1,1}, glm::vec3{2,5,7},"francine", Color{1.0f, 1.0f, 1.0f}};
  Box b2{};
  REQUIRE (boxie.getName() == "francine");
  REQUIRE (boxie.getColor().r == 1.0f);
  REQUIRE (boxie.getColor().g == 1.0f);
  REQUIRE (boxie.getColor().b == 1.0f);
  REQUIRE (b2.getName() == "DefaultShape");
  REQUIRE (b2.getColor().r == 0.0f);
  REQUIRE (b2.getColor().g == 0.0f);
  REQUIRE (b2.getColor().b == 0.0f);
  std::cout << "--------------------------------------------- \n";
} */

/*
TEST_CASE ("sphere_print","[print]")
{ 
  std::cout << "--------------------------------------------- \n";
  Color color{1.0f, 1.0f, 1.0f}; 
  std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);
  Sphere shapie {glm::vec3{1,1,1}, 4.0,"shapie", m1};
  std::cout << shapie;
  std::cout << "--------------------------------------------- \n";
}  

TEST_CASE ("box_print","[print]")
{ 
  std::cout << "--------------------------------------------- \n";
  Color color{1.0f, 1.0f, 1.0f}; 
  std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);
  Box boxie {glm::vec3{1,1,1}, glm::vec3{2,5,7},"francine", m1};
  std::cout << boxie;
  std::cout << "--------------------------------------------- \n";
} */
/*
TEST_CASE ("intersect_ray_sphere","[intersect]")  
{
    std::cout << "--------------------------------------------- \n";
    // Ray
    glm::vec3 ray_origin{0.0f,0.0f,0.0f};

    // ray direction has to be normalized !
    // you can use :
    // v = glm::normalize (some_vector)
    glm::vec3 ray_direction{0.0f,0.0f,1.0f};

    // Sphere
    glm::vec3 sphere_center{0.0f,0.0f,5.0f};
    float sphere_radius {1.0f};

    float distance = 0.0f;  //welche distanz genau ist das?
    auto result = glm::intersectRaySphere(
        ray_origin, ray_direction, sphere_center, 
        sphere_radius*sphere_radius, // squared radius !!!
        distance);

    Color color{1.0f, 1.0f, 1.0f}; 
    std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);

    Sphere s1{sphere_center, sphere_radius, "experimental", m1};
    Ray ray1 {ray_origin, ray_direction};

    REQUIRE (distance == Approx(4.0f));
    REQUIRE (s1.intersect(ray1,distance) == true);

    std::cout << "--------------------------------------------- \n";
} */ 
/*
TEST_CASE ("ctor_and_dtor", "[5.8")
{
    std::cout << "--------------------------------------------- \n";
    Color color{1.0f, 1.0f, 1.0f}; 
    std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);
    glm::vec3 position {0.0f,0.0f,0.0f};

    Sphere* s1 = new Sphere {position,1.2,"sphere0", m1};
    Shape* s2 = new Sphere {position,1.2, "sphere1", m1};

    s1 -> print (std::cout);
    s2 -> print (std::cout);

    delete s1;
    delete s2;
    std::cout << "--------------------------------------------- \n";
}*/
/*
TEST_CASE("Box_intersect", "[intersect]")
{

  glm::vec3 ray_origin{1.0 ,0.0 ,0.0};
  glm::vec3 ray_direction{-1.0 ,0.0 ,0.0};
  Ray ray{ray_origin, ray_direction};
  Color color{1.0f, 1.0f, 1.0f}; 
  std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);
  Box box{glm::vec3{-2,-2,1}, glm::vec3{2,6,5}, "Box", m1};

  glm::vec3 ray_orig{0.0, 0.0, 0.0};
  glm::vec3 ray_direc{0.0, 0.0, 1.0};
  Ray ray2 {ray_orig, ray_direc};
  float t {0.0};

  REQUIRE(box.intersect(ray, t) == false);
  REQUIRE(box.intersect(ray2, t) == true);
  
  box.intersect(ray2,t);  
  REQUIRE(t == 1.0);


}*/

TEST_CASE("Scene test") {
	//std::shared_ptr<Scene> scene = std::make_shared<Scene>();
  SDFLoader loader;
	Scene scene = loader.loadFile("/home/nicola/Schreibtisch/Raytracer-project/source/example.sdf");
  
	//std::cout<<"Search result:"<<*materialMapSearch("red",scene)<<"\n";
	//REQUIRE(materialMapSearch("black",scene) == nullptr);
  std::cout<< scene;
  //std::cout << scene.map_mat.find("red")->second << scene.map_mat.find("blue")->second << scene.light_[0] << scene.cam_<< /**scene.composite_.find("ssphere")->second <<*/ scene.ambient_.r;
} 



//Tests für den Raytracer
/*
TEST_CASE ("light_print","[print]")
{ 
  std::cout << "--------------------------------------------- \n";
  Color color{1.0f, 1.0f, 1.0f};
  //std::shared_ptr<Ambient> a1 = std::make_shared<Ambient>(color);
  Lightsource lighty {"lighty", glm::vec3{1,1,1}, color, 10};
  std::cout << lighty;
  std::cout << "--------------------------------------------- \n";
}

TEST_CASE ("camera_print","[print]")
{ 
  std::cout << "--------------------------------------------- \n";
  Camera cam {};
  std::cout << cam;
  std::cout << "--------------------------------------------- \n";
} 

TEST_CASE ("composite_print","[print]")
{ 
  std::cout << "--------------------------------------------- \n";
  Composite comp {};
  std::cout << comp;
  std::cout << "--------------------------------------------- \n";
}

TEST_CASE ("sphere_hitintersection","[hitintersection]")
{ 
  std::cout << "--------------------------------------------- \n";
    // Ray
    glm::vec3 ray_origin{0.0f,0.0f,0.0f};
    glm::vec3 ray_direction{0.0f,0.0f,1.0f};

    // Sphere
    glm::vec3 sphere_center{0.0f,0.0f,5.0f};
    float sphere_radius {1.0f};

    float distance = 0.0f;  

    Color color{1.0f, 1.0f, 1.0f}; 
    std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);

    Sphere s1{sphere_center, sphere_radius, "experimental", m1};
    Ray ray1 {ray_origin, ray_direction};

    
    glm::vec3 norm{0.0f, 0.0f, -1.0f};
    glm::vec3 intersect {0.0f, 0.0f, 4.0f};
    //Shape* shape = s1;
    //Hit spherehit{true, 4.0f, norm, intersect, shape}; 
    Hit hit = s1.intersect(ray1);

    //REQUIRE (distance == Approx(4.0f));
    REQUIRE (hit. hit_ == true);
    REQUIRE (hit. distance_ == Approx(4.0f));
    REQUIRE (hit. normal_ == norm);
    REQUIRE (hit. intersection_ == intersect);
    //REQUIRE (hit. closest_shape_ == s1);

  std::cout << "--------------------------------------------- \n";
}

TEST_CASE("Box_hitintersection", "[hitintersection]")
{

  glm::vec3 ray_origin{1.0 ,0.0 ,0.0};
  glm::vec3 ray_direction{-1.0 ,0.0 ,0.0};
  Ray ray{ray_origin, ray_direction};
  Color color{1.0f, 1.0f, 1.0f}; 
  std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);
  Box box{glm::vec3{-2,-2,1}, glm::vec3{2,6,5}, "Box", m1};

  glm::vec3 ray_orig{0.0, 0.0, 0.0};
  glm::vec3 ray_direc{0.0, 0.0, 1.0};
  Ray ray2 {ray_orig, ray_direc};
  float t {0.0};

  Hit hit = box.intersect(ray2);

  REQUIRE(hit.hit_ == true);
  REQUIRE(hit.distance_ == Approx(1.0f));
  //REQUIRE(hit.)

}

TEST_CASE ("composite_intersection","[intersection]")
{ 
  std::cout << "--------------------------------------------- \n";

  typedef std::shared_ptr<Shape> shape_ptr;
    Color color{1.0f, 1.0f, 1.0f}; 
    std::shared_ptr<Material> m1 = std::make_shared<Material>("default", color, color, color, 4.0f);

  shape_ptr s1 = std::make_shared<Sphere>(Sphere {{0.0f, 0.0f, -4.0f}, 5.2,"s1", m1});
  shape_ptr s2 = std::make_shared<Sphere>(Sphere {{4.0f, 0.0f, -5.0f}, 2.1, "s2", m1});
  shape_ptr s3 = std::make_shared<Sphere>(Sphere {{1.0f, 0.3f, 2.0f}, 1.9, "s3", m1});
  shape_ptr s4 = std::make_shared<Sphere>(Sphere {{0.0f, 0.0f, -3.0f}, 2.2, "s4", m1});
  shape_ptr s5 = std::make_shared<Sphere>(Sphere {{0.0f, 0.0f, -2.9f}, 2.2, "s5", m1});
  shape_ptr b1 = std::make_shared<Box>(Box {{-1.0f,-1.0f,-6.0f}, {5.0f,3.0f,-9.0f}, "Box", m1});

  Composite comp {};
  comp.addShape(s1);
  comp.addShape(s2);
  comp.addShape(s3);
  comp.addShape(s4);
  comp.addShape(b1);

  Ray ray {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}};
  Hit hit1 = s1 -> intersect(ray);
  Hit hit2 = s2 -> intersect(ray);
  Hit hit4 = s4 -> intersect(ray);
  Hit hit5 = s5 -> intersect(ray);
  Hit hitbox = b1 -> intersect(ray);
  Hit hitComp = comp.intersect(ray);

  REQUIRE(hit4.distance_ == hitComp.distance_);
  REQUIRE(hit2.hit_ != hitComp.hit_);
  REQUIRE(hit2.distance_ > hitComp.distance_);
  REQUIRE(hit1.hit_ == hitComp.hit_);
  REQUIRE(hit1.distance_ > hitComp.distance_);
  REQUIRE(hit5.distance_ < hitComp.distance_);

  REQUIRE(hitbox.distance_ == Approx(6.0f)); // hier stimmt etwas noch nicht so ganz...
  REQUIRE(hitbox.hit_ == true);
  REQUIRE(hitbox.distance_ > hitComp.distance_);
  std::cout << comp;
  std::cout << "--------------------------------------------- \n";
}*/


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
