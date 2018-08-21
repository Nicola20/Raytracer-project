// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
/*
Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}*/

Renderer::Renderer(Scene const& scene):
  scene_{scene},
  color_buffer_{scene.width_*scene.height_, Color(0.0, 0.0, 0.0)},
  ppm_{scene.width_, scene.height_} {}


void Renderer::render()
{
  //std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < scene_.height_; ++y) {  //schmaybe hier scene_. anwenden
    for (unsigned x = 0; x < scene_.width_; ++x) {
      Pixel p(x,y);
      Ray pixelRay = scene_.cam_.calculateCamRay(x, y, scene_.width_, scene_.height_);
      /*
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }*/
      p.color = raytrace(pixelRay);  //hier zu tmpcollor = raytrace und dann p.color mit tonemappingformel berechnen

      write(p);
    }
  }
  ppm_.save(scene_.fileOut_);
}

Color Renderer::raytrace(Ray const& ray) {

  Hit closest = scene_.composite_ -> intersect(ray);

  if (closest.hit_) {
    Color clr;

    ambientLight(clr, closest.shape_.material() -> ka_);

    for (auto& l: scene_.light_){
       pointLight(clr, l, ray, closest);
    }



  }

}

Color Renderer::ambientLight(Color & clr, Color const& ka){

   return clr +=(scene_.ambient_)*ka;
}

Color Renderer::pointLight(Color const& col, std::shared_ptr<Light> light, Ray const& ray, Hit const& hit){
  bool lightHit = true;
  glm::vec3 vecToLight = glm::normalize(light.position_ - hit.intersection_); //vector zur Lichtquelle

}

Color Renderer::diffuse(){

}

Color Renderer::spekular(){


}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (scene_.width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
