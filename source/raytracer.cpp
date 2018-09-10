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

  unsigned const image_width = 1280;
  unsigned const image_height = 720;

  SDFLoader load;
	Scene scn = load.loadFile("C:/Users/Gabriel/Desktop/ray5/Raytracer-project/source/scene1.sdf");


  std::shared_ptr<Scene> scene = std::make_shared<Scene>();

	for (int frames = 1; frames > 120; ++frames) {
		//normie.position - frames;
	}

  std::string const filename = "./checkerboard.ppm";

  Renderer renderer(image_width, image_height, filename);

  renderer.render(scn);

  //create separate thread to see updates of pixels while rendering
 //std::thread thr([&renderer]() { renderer.render(); });

  Window window(glm::ivec2(image_width, image_height));


  std::vector<Color> color_buffer(image_width*image_height);
  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
    //window.show(color_buffer);
  }

  //thr.join();

  return 0;
}
