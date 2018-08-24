#include "renderer.hpp"
#include "sdfloader.hpp"
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include <fensterchen.hpp>

int main(int argc, char* argv[])
{
	
	Scene scene = loadFile("/home/Nicola/Schreibtisch/Raytracer-project/source/example.sdf");
/*
  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const filename = "./checkerboard.ppm";*/

  Renderer renderer(scene);

  //renderer.render(scene);
  //create separate thread to see updates of pixels while rendering
 // std::thread render_thread([&renderer]() {renderer.render(scene);}); 
 std::thread thr([&renderer]() { renderer.render(); });

  Window window(glm::ivec2(scene.width_, scene.height_));

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
  // glDrawPixels(width, height, GL_RGB, GL_FLOAT
    glDrawPixels(scene.width_, scene.height_, GL_RGB, GL_FLOAT
                ,renderer.color_buffer().data());

    window.update();
  }

  thr.join();

  return 0;
}
