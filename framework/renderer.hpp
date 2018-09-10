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
#include "composite.hpp"
#include "ppmwriter.hpp"
#include "ray.hpp"
//#include "sdfloader.hpp"
#include "scene.hpp"
#include "hit.hpp"
#include <string>
#include <glm/glm.hpp>
#include <memory>

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);
  Color raytrace(Ray const& ray);
  /*
  void ambientLight(Color & clr, Color const& ka);
  void pointLight(Color & clr, std::shared_ptr<Lightsource> const& light, Ray const& ray, Hit const& hit);
  void diffuse(Color & clr, Hit const& hit, std::shared_ptr<Lightsource> const& light, glm::vec3 const& vecLight);
  void spekular(Color & clr, Hit const& hit, std::shared_ptr<Lightsource> const& light, glm::vec3 const& vecLight);*/
  Color calculateColor(Hit const& hit, Ray const& ray, int step);
  Color ambientLight(Color const& ka);
  Color pointLight(Hit const& hit, Ray const& ray, float delta);
  Color diffuseLight(Hit const& hit,glm::vec3 const& vecToLight, std::shared_ptr<Lightsource> const & light);
  Color spekularLight(Hit const& hit, std::shared_ptr<Lightsource> const& light, glm::vec3 const& vecToLight, Ray const& ray);
  Color tonemapping(Color const& clr);
  Color calculateReflection(Hit const& hit, Ray const& ray, Scene const& scene, int step);
  //Color antialias(Pixel & p, Scene const& scene);
  Color antialias(Ray const& ray, float factor);

  void render(Scene const& scene);
  void write(Pixel const& p);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  Scene scene_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
