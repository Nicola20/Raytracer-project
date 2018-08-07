#ifndef SCENE_HPP
#define SCENE_HPP

#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

struct Scene {
    std::vector<std::shared_ptr<Material>> vec_mat;
    std::set<std::shared_ptr<Material>> set_mat;
    std::map<std::string, std::shared_ptr<Material>> map_mat;


};
 void SDFFileLoader(std::string const& fileIn, Scene& scene) {  //Frage: wie genau increase ich die linien und lese von genau dieser Linie etwas?

     std::ifstream file;
     std::string line;
     file.open(fileIn);

     if (file.is_open()){
            while(std::getline(file,line)){     //while file has lines
            std::stringstream ss;
            std::string keyword;

            ss<<line;               //add stringobject first line
            ss>>keyword;            //read ffirst word

            if(keyword == "define"){
                ss>>keyword;        //read next word

                if(keyword == "material"){

                    Material mat;

                    ss>>mat.name;

                    ss>> mat.ka_.r;
                    ss>> mat.ka_.g;
                    ss>> mat.ka_.b;
                    ss>> mat.kd_.r;
                    ss>> mat.kd_.g;
                    ss>> mat.kd_.b;
                    ss>> mat.ks_.r;
                    ss>> mat.ks_.g;
                    ss>> mat.ks_.b;

                    ss>> mat.m_;
                    std::shared_ptr<Material> matPoint = std::make_shared<Material>(mat);
                    scene.vec_mat.push_back(matPoint);
                    scene.map_mat.insert(std::pair<std::string,std::shared_ptr<Material>>(matPoint->name,matPoint));
                    scene.set_mat.insert(matPoint);
                }
                /*
                if(keyword == "shape"){
                    //ss<<line;     
                    ss>>keyword;
                    if(keyword == "box"){
                        std::string bname;
                        glm::vec3 bmin;
                        glm::vec3 bmax;
                        Material mat;
                        ss>> bname;
                        ss>> bmin.x;
                        ss>> bmin.y;
                        ss>> bmin.z;
                        ss>> bmax.x;
                        ss>> bmax.y;
                        ss>> bmax.z;
                        ss>>mat;
                        Box b {bmin, bmax, bname, mat};
                    }
                    if(keyword == "sphere"){
                        std::string sname;
                        glm::vec3 scenter;
                        float sradius;
                        Material mat;
                        ss>> sname;
                        ss>> scenter.x; 
                        ss>> scenter.y; 
                        ss>> scenter.z;
                        ss>> sradius;
                        ss>> mat;
                        Sphere s {scenter, sradius, sname, mat}; 
                    }
                    
                }*/
            }
        file.close(); 
       }
     }
     //return vec_mat;
 }

 std::shared_ptr<Material> materialMapSearch (std::string name, Scene& scene) {
	
	auto i = scene.map_mat.find(name);
	if(i != scene.map_mat.end()){
		return scene.map_mat.find(name)->second;
	} else {
		return nullptr;
	  }
}
/*
std::shared_ptr<Material> materialVecSearch (std::string name, Scene& scene) {
 
    //std::vector<std::shared_ptr<Material>>::iterator it;
    auto it = find(scene.vec_mat.begin(), scene.vec_mat.end(), name);
    if(it != scene.vec_mat.end()){
        return *it;
    } else {
         return nullptr;
      }
}*/
/*
std::shared_ptr<Material> materialVecSearch (std::string name, Scene& scene){  //Material braucht hierfür einen Vergleichsoperator

auto it = std::find_if(scene.vec_mat.begin(), scene.vec_mat.end(), [&](std::shared_ptr<Material> const& p) {
    return *p == name; // assumes MyType has operator==
});

if (it != v.end()) { return scene.vec_mat.*p -> name;}
}*/
#endif