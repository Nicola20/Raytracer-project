#include "sdfloader.hpp"
#include <map>
#include <memory>


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
                    //scene.map_mat.insert(std::pair<std::string,std::shared_ptr<Material>>(matPoint->name,matPoint));

                    scene.map_mat[mat.name] = matPoint;

                }
                
                if(keyword == "shape"){
                    //ss<<line;     
                    ss>>keyword;

                    if(keyword == "box"){
                        std::string bname;
                        glm::vec3 bmin;
                        glm::vec3 bmax;
                        std::string mat;

                        ss>> bname;
                        ss>> bmin.x;
                        ss>> bmin.y;
                        ss>> bmin.z;
                        ss>> bmax.x;
                        ss>> bmax.y;
                        ss>> bmax.z;
                        ss>>mat;


                        std::shared_ptr<Material> boxMat = (scene.map_mat.find(mat) -> second); 

                        auto box = std::make_shared<Box>(bmin, bmax, bname, boxMat);
                        sceneshapes[bname] = box; //add to container so that you can find it afterwards for composite
                    }
                    if(keyword == "sphere"){ 
                        std::string sname;
                        glm::vec3 scenter;
                        float sradius;
                        std::string mat;
                        ss>> sname;
                        ss>> scenter.x; 
                        ss>> scenter.y; 
                        ss>> scenter.z;
                        ss>> sradius;
                        ss>> mat;
                        
                        std::shared_ptr<Material> sphereMat = (scene.map_mat.find(mat) -> second); 

                        auto sphere = std::make_shared<Sphere>(scenter, sradius, sname, sphereMat);
                        sceneshapes[sname] = sphere;
                    }

                    if (keyword == "composite") {
                        std::string compositeName;
                        std::string newShape;

                        ss<<compositeName;

                        scene.composite_ = std::make_shared<Composite>(compositeName);

                        while(!ss.eof()) {  //solange das File noch nicht zu Ende ist lies shapenamen ein
                            ss<<newShape;
                             auto existingShape = sceneshapes.find(newShape); //schaue ob es das shape bereits existiert

                             if(existingShape != sceneshapes.end()){

                                 std::shared_ptr<Shape> tmpshape = existingShape->second;
                                 scene.composite_ -> addShape(tmpshape);
                             } 

                        }
                    }
                    
                } //shape geschlossen

                if (keyword == "light") {

                    unsigned int vecSize = 0;
                    std::string lightname;
                    glm::vec3 pos;
                    Color lightcol;
                    int brideness;

                    ss>>lightname;
                    ss>>pos.x;
                    ss>>pos.y;
                    ss>>pos.z;
                    ss>>lightcol.r;
                    ss>>lightcol.g;
                    ss>>lightcol.b;
                    ss>>brideness;

                    auto light = std::make_shared<Lightsource>(lightname, pos, lightcol, brideness);
                    scene.light_.push_back(light);
                    ++ vecSize;


                }

                if (keyword == "camera") {
                    std::string cname;
                    float fox_x;
                    glm::vec3 pos;
                    glm::vec3 dir;
                    glm::vec3 up;

                    ss>>cname;
                    ss>>fox_x;
                    ss>>pos.x;
                    ss>>pos.y;
                    ss>>pos.z;
                    ss>>dir.x;
                    ss>>dir.y;
                    ss>>dir.z;
                    ss>>up.x;
                    ss>>up.y;
                    ss>>up.z;

                    scene.cam_ = Camera {cname, fox_x, pos, dir, up};

                }
            } //define geschlossen

            if (keyword == "ambient") {
                Color ambient;

                ss>>ambient.r;
                ss>>ambient.g;
                ss>>ambient.b;

                scene.ambient_ = ambient;

            }
    
            if (keyword == "render") {

                std::string camName;
                ss >> camName;

                // checks whether camera exists so the frame can be rendered 
                 if (camName == scene.cam_.name_) {

                     ss>>scene.fileOut_;
                     ss>>scene.width_;
                     ss>>scene.height_;

                }

            }

        file.close(); 
       }
     }
     return scene;
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