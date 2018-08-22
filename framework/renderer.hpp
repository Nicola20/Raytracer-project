// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "camera.hpp"
#include "lightsource.hpp"
#include "shape.hpp"
#include "scene.hpp"
#include "composite.hpp"
#include "ppmwriter.hpp"
#include "ray.hpp"
#include "sdfloader.hpp"
#include <string>
#include <glm/glm.hpp>

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);
  Renderer (Scene const& scene);
  Color raytrace(Ray const& ray);
  Color pointLight(Color const& col, std::shared_ptr<Lightsource> light, Ray const& ray, Hit const& hit);
  Color diffuse(Color & clr, Hit const& hit, std::shared_ptr<Lightsource> light, glm::vec3 const& vecLight);
  Color spekular(Color & clr, Hit const& hit, std::shared_ptr<Lightsource> light, glm::vec3 const& vecLight);

  void render();
  void write(Pixel const& p);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  //unsigned width_;
  //unsigned height_;
  Scene scene_;
  std::vector<Color> color_buffer_;
  //std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
