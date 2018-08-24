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

  SDFLoader load;
	
	Scene scene = load.loadFile("/home/nicola/Schreibtisch/Raytracer-project/source/example.sdf");

  unsigned const image_width = 800;
  unsigned const image_height = 600;
  //std::string const filename = "./checkerboard.ppm";

  Renderer renderer(scene);

  renderer.render();
  //create separate thread to see updates of pixels while rendering
 // std::thread render_thread([&renderer]() {renderer.render(scene);}); 
 //std::thread thr([&renderer]() { renderer.render(); });

  Window window(glm::ivec2(image_width, image_height));

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  //thr.join();

  return 0;
}
