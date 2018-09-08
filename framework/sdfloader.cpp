#include "sdfloader.hpp"
#include <map>
#include <memory>


 Scene SDFLoader::loadFile(std::string const& fileIn) {  

     std::ifstream file;
     std::string line;
     file.open(fileIn);
     Scene scene;
     std::map<std::string, std::shared_ptr<Shape>> sceneshapes;

     if (file.is_open()){
         std::cout<<"File is open"<<std::endl;
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

					ss >> mat.reflection_;
                    
                    std::shared_ptr<Material> matPoint = std::make_shared<Material>(mat);
                    //scene.map_mat.insert(std::pair<std::string,std::shared_ptr<Material>>(matPoint->name,matPoint));

                    scene.map_mat[mat.name] = matPoint;
                    std::cout<<"Material found! "<<*scene.map_mat.find(mat.name)->second<<std::endl;
                }
                //ss>>keyword;
                
                if(keyword == "shape"){
                    //ss<<line;     
                    ss>>keyword;
                    std::cout<<"shape found"<<std::endl;

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


                        std::shared_ptr<Material> boxMat = scene.map_mat.find(mat)->second; //Fehler könnte hier bei find liegen 

                        auto box = std::make_shared<Box>(bmin, bmax, bname, boxMat);
                        sceneshapes[bname] = box; //add to container so that you can find it afterwards for composite
                        std::cout<<"Box found! "<<std::endl;
                    }

                    if(keyword == "sphere"){ 
                        std::cout<<"sphere found!"<<std::endl;                        
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
                        
                        std::shared_ptr<Material> sphereMat = scene.map_mat.find(mat)->second; 

                        auto sphere = std::make_shared<Sphere>(scenter, sradius, sname, sphereMat);
                        sceneshapes[sname] = sphere;
                    }
					if (keyword == "triangle") {
						std::cout << "triangle found!" << std::endl;
						std::string tname;
						std::string mat;
						glm::vec3 tp1;
						glm::vec3 tp2;
						glm::vec3 tp3;

						ss >> tname;
						ss >> tp1.x;
						ss >> tp1.y;
						ss >> tp1.z;
						ss >> tp2.x;
						ss >> tp2.y;
						ss >> tp2.z;
						ss >> tp3.x;
						ss >> tp3.y;
						ss >> tp3.z;

						ss >> mat;

						std::shared_ptr<Material> triangleMat = scene.map_mat.find(mat)->second;
						auto triangle = std::make_shared<Triangle>(tp1, tp2, tp3, tname, triangleMat);

					}

                    if (keyword == "composite") {
                        std::cout<<"composite found"<<std::endl;
                        std::string compositeName;
                        std::string newShape;

                        ss>>compositeName;

                        scene.composite_ = std::make_shared<Composite>(compositeName);

                        while(!ss.eof()) {  //solange das File noch nicht zu Ende ist lies shapenamen ein
                            ss>>newShape;
                             auto existingShape = sceneshapes.find(newShape); //schaue ob es das shape bereits existiert

                             if(existingShape != sceneshapes.end()){

                                 std::shared_ptr<Shape> tmpshape = existingShape->second;
                                 scene.composite_ -> addShape(tmpshape);
                             } 

                        }
                    }
                    
                }  //shape geschlossen
                
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
                    std::cout<<"light found"<<std::endl;

                }

               if (keyword == "camera") {
                    std::string cname;
                    float fov_x;
                    glm::vec3 pos;
                    glm::vec3 dir;
                    glm::vec3 up;

                    ss>>cname;
                    ss>>fov_x;
                    ss>>pos.x;
                    ss>>pos.y;
                    ss>>pos.z;
                    ss>>dir.x;
                    ss>>dir.y;
                    ss>>dir.z;
                    ss>>up.x;
                    ss>>up.y;
                    ss>>up.z;

                    Camera cam{cname, fov_x, pos, dir, up};

                    scene.cam_ = cam;
                    std::cout<<"cam found"<<std::endl;


                }
            } //define geschlossen

            if (keyword == "ambient") {
                Color ambient;

                ss>>ambient.r;
                ss>>ambient.g;
                ss>>ambient.b;

                scene.ambient_ = ambient;
                std::cout<<"ambient found: "<< scene.ambient_<<std::endl;

            }
    
            if (keyword == "render") {

                std::string camName;
                ss >> camName;

                // checks whether camera exists so the frame can be rendered 
                 if (camName == scene.cam_.name_) {

                     ss>>scene.fileOut_;
                     ss>>scene.width_;
                     ss>>scene.height_;

                std::cout<<"Camera: "<< scene.cam_.name_ << "\n" << "FileOut: " << scene.fileOut_ << "\n"
                        << "Picture: " << scene.width_ << " x " << scene.height_<<"\n";
                } else {
                    std::cout<< "Error occured. Camera could not be found"<<std::endl;
                }

            }

            if (keyword == "transform") {
                std::cout<<"transformation found"<<std::endl;
                std::string shapename;
                ss>>shapename;
                //ss<<keyword;

                auto transform = sceneshapes.find(shapename); 
                if (transform != sceneshapes.end()) { 
                    ss>>keyword;
                    std::cout<<"hello there general Kenobi"<<std::endl;

                    if (keyword == "translate") { 
                        std::cout<<"translation found"<<std::endl;
                        glm::vec3 v;
                        ss>>v.x;
                        ss>>v.y;
                        ss>>v.z;

                        (transform->second)->translate(v);

                    }

                    if (keyword == "rotate") {
                        std::cout<<"rotation found"<<std::endl;
                        float phi;
                        glm::vec3 vec;
                        ss>>phi;
                        ss>>vec.x;
                        ss>>vec.y;
                        ss>>vec.z;

                        (transform->second)->rotate(phi, vec);

                    }

                    if (keyword == "scale") {
                        std::cout<<"scale found"<<std::endl;
                        glm::vec3 s;
                        ss>>s.x;
                        ss>>s.y;
                        ss>>s.z;

                        (transform->second)->scale(s);

                    } 
                }  else if (shapename == scene.cam_.name_) { //ab hier noch if falls shapename = cameraname
                    std::cout<<"Camera Transformation found"<<std::endl;
                    ss>>keyword;
                    if (keyword == "translate") {
                        glm::vec3 camtransvec;

                        ss>>camtransvec.x;
                        ss>>camtransvec.y;
                        ss>>camtransvec.z;

                        scene.cam_.translate(camtransvec);
                        std::cout<<"camera translation found"<<std::endl;
                    }

                    if (keyword == "rotate") {
                        float phi;
                        glm::vec3 camrotvec;

                        ss>>phi;
                        ss>>camrotvec.x;
                        ss>>camrotvec.y;
                        ss>>camrotvec.z;

                        scene.cam_.rotate(phi, camrotvec);
                        std::cout<<"camera rotation found: "<<"\n"<<
                        "Winkel:" <<phi<<"\n"<< 
                        "Rotationsvektor: "<<camrotvec.x <<", "<< camrotvec.y<<", "<< camrotvec.z<< std::endl;
                    }

                }
            }

       }

       file.close();
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