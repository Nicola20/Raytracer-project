// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>


Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}


//#define USE_RAY_DIRECTION_VIS

void Renderer::render(Scene const& scene)
{
  scene_ = scene;
  //std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y) {  
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      Ray pixelRay = scene_.cam_.calculateCamRay(x, y, width_, height_);
  /*    
      #if USE_RAY_DIRECTION_VIS
        // color = Color( ((pixelRay.x + 1) / 2.0) * 255, ...);
      #endif
      
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }
  */    
      Color tmp = raytrace(pixelRay);  //hier zu tmpcollor = raytrace und dann p.color mit tonemappingformel berechnen

      p.color = tonemapping(tmp);

      write(p);
    }
  }
  ppm_.save(scene_.fileOut_);
}



Color Renderer::raytrace(Ray const& ray) {

  Hit closest = scene_.composite_ -> intersect(ray); //muss hier dann jetzt mal gucken; bei composite stimmt was nicht
  Color clr;

  if (closest.hit_) {
    ambientLight(clr, closest.closest_shape_->getMaterial() -> ka_);

    for (auto & l: scene_.light_){
        pointLight(clr, l, ray, closest);
    }
    
  } else {
     clr = Color {0.0f, 0.0f, 0.4f}; //Hier Farbwert für Hintergrund setzen: dunkelblau
  }

  return clr; //Farbberechnung, die sich durch die Funktionen aufaddiert hat
}


void Renderer::ambientLight(Color & clr, Color const& ka){

   clr +=(scene_.ambient_)*ka;
}



void Renderer::pointLight(Color & clr, std::shared_ptr<Lightsource> const& light, Ray const& ray, Hit const& hit){
  bool lightHit = true;
  glm::vec3 vecToLight = glm::normalize(light->position_ - hit.intersection_); //vector zur Lichtquelle

  Ray rayToLight {hit.intersection_*0.001f, vecToLight}; //neuer Ray zur Punktichtquelle; Frage warum mit 0,001 verrechnen?
  Hit newHit = scene_.composite_ ->intersect(rayToLight); //hit mit geringster Distanz wir zurückgegeben

  float distance = glm::length(hit.intersection_ - light->position_);

  if(newHit.distance_ > distance) { //distance nur dann größer, wenn vorher kein Objekt getroffen wurde
    //Berechnung von diffus und spekular
    diffuse(clr, hit, light, vecToLight);
    spekular(clr,hit, light, vecToLight);
  }

}



void Renderer::diffuse(Color & clr, Hit const& hit, std::shared_ptr<Lightsource> const& light, glm::vec3 const& vecLight){

  Color ip = (light -> lightcol_ * float(light -> ip_));
  Color kd = hit.closest_shape_->getMaterial()->kd_;
  float vecPro = glm::dot(hit.normal_, vecLight);

	clr += ip*kd*vecPro; //auch mit rayToLight.direction möglich
}


void Renderer::spekular(Color & clr, Hit const& hit, std::shared_ptr<Lightsource> const& light, glm::vec3 const& vecLight) {
	//Cs = ks * Ie * Os *cos(R, A)
	//return clr += (light.ip_)*(hit.closest_shape_.getMaterial() -> ks_)*
	float m = hit.closest_shape_->getMaterial()->m_;
	glm::vec3 v = glm::normalize(scene_.cam_.eyePos_ - hit.intersection_);
	glm::vec3 r = glm::normalize(glm::dot(hit.normal_, vecLight)*2.0f*hit.normal_-vecLight);
	float cos = pow(glm::dot(v, r), m);
	Color ip = light->lightcol_ * float(light->ip_);        //steht so auf dem Aufgabenblatt
	//float m_pi = (m + 2) / (2 * M_PI);
	Color ks = hit.closest_shape_->getMaterial()->ks_;

	clr += ip * cos * /*m_pi * */ks;
	
}



Color Renderer::tonemapping(Color const& clr) {

  float gamma = 0.99f;
  float a = 1.0f;
  Color final;
  final.r = a*pow(clr.r, gamma);
  final.g = a*pow(clr.g, gamma);
  final.b = a*pow(clr.b, gamma);

  return final;
}



void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
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
