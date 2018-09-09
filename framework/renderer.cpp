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
  */  Color tmp;  
      //tmp = raytrace(pixelRay);  //hier zu tmpcollor = raytrace und dann p.color mit tonemappingformel berechnen
	  tmp = antialias(p, scene_);
      p.color = tonemapping(tmp);
      

      write(p);
    }
  }
  ppm_.save(scene_.fileOut_);
}



Color Renderer::raytrace(Ray const& ray) {

	Hit closest = scene_.composite_->intersect(ray); //muss hier dann jetzt mal gucken; bei composite stimmt was nicht
  Color clr;
  int step = 2;

	if (closest.hit_) {
		/*
		ambientLight(clr, closest.closest_shape_->getMaterial() -> ka_);

		for (auto & l: scene_.light_){
			pointLight(clr, l, ray, closest);
		}*/

		
	clr = calculateColor(closest, ray, step); 

  } else {
		clr = Color{ 0.0f, 0.0f, 0.4f }; //Hier Farbwert für Hintergrund setzen: dunkelblau
	}
	return clr; //Farbberechnung, die sich durch die Funktionen aufaddiert hat
	
}


Color Renderer::calculateColor(Hit const& hit, Ray const& ray, int step){
  float delta = 1;
  Color ptl;
  Color clr;
  Color amb = ambientLight(hit.closest_shape_->getMaterial()->ka_);
  //for (auto & l: scene_.light_) {
    ptl = pointLight (hit, ray, delta);
    if (hit.closest_shape_-> getMaterial() -> reflection_) {
			//int reflection = hit.closest_shape_->getMaterial()->reflection_;
			 clr = calculateReflection(hit, ray, scene_, step);
		}
		

  return amb + (ptl*delta) + clr;
}

Color Renderer::ambientLight(Color const& ka){
  //Color clr;
  return scene_.ambient_*ka;
}

Color Renderer::pointLight(Hit const& hit, Ray const& ray, float delta) {
  Color clr;
  for (auto & l: scene_.light_) {
    glm::vec3 vecToLight{l->position_ - hit.intersection_};
    vecToLight = glm::normalize(vecToLight); // I normalisiert
    Ray newLightRay{hit.intersection_+hit.normal_, vecToLight};//vecToLight eingefügt
    Hit lightHit = scene_.composite_->intersect(newLightRay);
    float distance = glm::length(hit.intersection_ - l->position_);

	
    if (lightHit.distance_ > distance) { //hier gefixt für 2 Lichtquellen und Schatten
      Color diff = diffuseLight(hit, vecToLight, l);
      Color spek = spekularLight(hit, l, vecToLight, ray);
      clr  += diff+spek;
     delta = 1;
    } else {
      delta = 0;
    }
  }
  return clr;
}

Color Renderer::diffuseLight(Hit const& hit,glm::vec3 const& vecToLight, std::shared_ptr<Lightsource> const & light) {
  Color ip = light->lightcol_*float(light->ip_);
  Color kd = hit.closest_shape_->getMaterial()->kd_;
  float vec = glm::dot(glm::normalize(hit.normal_),vecToLight);
  //Color clr;
  return  ip*kd*vec;
}

Color Renderer::spekularLight(Hit const& hit, std::shared_ptr<Lightsource> const& light, glm::vec3 const& vecToLight, Ray const& ray) {
  Color clr;
	/*float m = hit.closest_shape_->getMaterial()->m_;
	glm::vec3 v = glm::normalize(scene_.cam_.eyePos_ - hit.intersection_);
	glm::vec3 r = glm::normalize(glm::dot(hit.normal_, vecLight)*2.0f*hit.normal_-vecLight);
	float cos = pow(glm::dot(v, r), m);
	Color ip = light->lightcol_ * float(light->ip_);        //steht so auf dem Aufgabenblatt
	Color ks = hit.closest_shape_->getMaterial()->ks_;
  float m_pi = (m + 2) / (2 * M_PI);

  return ip * cos * ks* m_pi;*/
  
  glm::vec3 reflection = glm::normalize(glm::reflect(-(vecToLight),hit.normal_));
  float factor = glm::max(0.0f, glm::dot(reflection, glm::normalize(-(ray.direction_))));
  clr = (hit.closest_shape_ ->getMaterial()-> ks_)*pow(factor, hit.closest_shape_ ->getMaterial()-> m_);
  return clr;
}

Color Renderer::calculateReflection(Hit const& hit, Ray const& ray, Scene const& scene, int step) {

	glm::vec3 reflection_vec = glm::reflect(glm::normalize(ray.direction_), glm::normalize(hit.normal_));
	Ray new_ray{ hit.intersection_ + hit.normal_, glm::normalize(reflection_vec) };
	
	Hit new_hit = scene.composite_->intersect(new_ray);
	//Color objectlight = calculateColor(hit, ray, step);
	//Color maincolor = hit.closest_shape_->getMaterial()->ka_;

	if (!new_hit.hit_) {
		 Color umgebung{ 0.0f, 0.0f, 0.4f };
		
		 return umgebung; //+ maincolor * 0.2f + objectlight * 0.4f;
	}
	else {
		if (step > 0) {
      //-step;
      Color reflected_color;
      reflected_color = calculateColor(new_hit, new_ray, step-1);
			return reflected_color; //+ maincolor* 0.2f + objectlight * 0.4f ;
		}
		else { return Color{ 0.0,0.0,0.0 }; }
	}
}

/*
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

	clr += ip * cos * ks  *m_pi;
	
} */



Color Renderer::tonemapping(Color const& clr) {

  float gamma = 0.99f;
  float a = 1.0f;
  Color final;
  final.r = a*pow(clr.r, gamma);
  final.g = a*pow(clr.g, gamma);
  final.b = a*pow(clr.b, gamma);

  return final;
}

Color Renderer::antialias(Pixel & p, Scene const& scene) {
	float x = p.x;
	float y = p.y;
	std::vector<Ray> rays;
	rays.push_back(scene.cam_.calculateCamRay(x, y, scene.width_, scene.height_));
	rays.push_back(scene.cam_.calculateCamRay(x + 0.5, y + 0.5, scene.width_, scene.height_));
	rays.push_back(scene.cam_.calculateCamRay(x - 0.5, y - 0.5, scene.width_, scene.height_));
	rays.push_back(scene.cam_.calculateCamRay(x - 0.5, y - 0.5, scene.width_, scene.height_));
	rays.push_back(scene.cam_.calculateCamRay(x + 0.5, y + 0.5, scene.width_, scene.height_));
	Color color{ 0.0f,0.0f,0.0f };
	for (auto ray : rays) {
		color += raytrace(ray);
	}
	return color * (1.0f / rays.size());
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
