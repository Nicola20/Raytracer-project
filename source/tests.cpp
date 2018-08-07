#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "box.hpp"
#include "sphere.hpp"
#include "shape.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "scene.hpp"
#include "lightsource.hpp"
#include "ambient.hpp"
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
}

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
} */ 
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
} 
*/
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
} 

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
}  

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
}

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


}

TEST_CASE("Scene test") {
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	SDFFileLoader("/home/nicola/Dokumente/Programmiersprachen/ProPra Abgabe 6/programmiersprachen-raytracer/source/example.sdf",*scene);
	std::cout<<"Search result:"<<*materialMapSearch("red",*scene)<<"\n";
	REQUIRE(materialMapSearch("black",*scene) == nullptr);
}*/ 

//Tests für den Raytracer
/*
TEST_CASE ("light_print","[print]")
{ 
  std::cout << "--------------------------------------------- \n";
  Color color{1.0f, 1.0f, 1.0f};
  std::shared_ptr<Ambient> a1 = std::make_shared<Ambient>(color);
  Lightsource lighty {"lighty", glm::vec3{1,1,1}, color, a1};
  std::cout << lighty;
  std::cout << "--------------------------------------------- \n";
} */ 

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
