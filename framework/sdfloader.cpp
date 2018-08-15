#include "sdfloader.hpp"
#include <map>
#include <memory>


/*Verbesserungsmöglichkeit: Einfach wie bei Material etwas erstellen und dann einlesen; geht aber nur mit Default-Konstruktor*/
 Scene loadFile(std::string const& fileIn) {  

     std::ifstream file;
     Scene scene;
     std::map<std::string, std::shared_ptr<Shape>> sceneshapes;
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
                    scene.map_mat.insert(std::pair<std::string,std::shared_ptr<Material>>(matPoint->name,matPoint));

                }
                
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

                        //Box b {bmin, bmax, bname, mat};
                        //hier noch die Box in einen Container verfrachten und material als shared_ptr woanders abspeichern
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
                        //Sphere s {scenter, sradius, sname, mat};   //das gleiche wie mit box und dem material
                    }

                    if (keyword == "composite") {
                        std::string compositeName;
                        std::string newShape;

                        ss<<compositeName;

                        scene.composite_ = std::make_shared<Composite>(compositeName);

                        while(!ss.eof()) {  //solange das File noch nicht zu Ende ist lies shapenamen ein
                            ss<<newShape;
                             auto existingShape = sceneshapes.find(newShape); //schaue ob es das shape bereits existiert

                             if(existingShape != sceneshape.end()){

                                 std::shared_ptr<Shape> tmpshape = existingShape->second;
                                 scene.composite_ -> addShape(tmpshape);
                             } 

                        }
                    }
                    
                } //shape geschlossen

                if (keyword == "light") {

                }

                if (keyword == "camera") {
                    std::string cname;
                    double fox_x;
                    glm::vec3 pos;
                    glm::vec3 dir;
                    glm::vec3 up;

                    ss<<cname;
                    ss<<fox_x;
                    ss<<pos.x;
                    ss<<pos.y;
                    ss<<pos.z;
                    ss<<dir.x;
                    ss<<dir.y;
                    ss<<dir.z;
                    ss<<up.x;
                    ss<<up.y;
                    ss<<up.z;

                    scene.cam_ = Camera {cname, fox_x, pos, dir, up};

                }
            } //define geschlossen

            if (keyword == "ambient") {
                Color ambient;

                ss<<ambient.r;
                ss<<ambient.g;
                ss<<ambient.b;

                scene.ia_ = ambient;

            }
        file.close(); 
       }
     }
     //return vec_mat;
 }



/*
 std::shared_ptr<Material> materialMapSearch (std::string name, Scene& scene) {
	
	auto i = scene.map_mat.find(name);
	if(i != scene.map_mat.end()){
		return scene.map_mat.find(name)->second;
	} else {
		return nullptr;
	  }
}*/