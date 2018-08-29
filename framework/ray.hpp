#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

struct Ray {

    Ray():
        origin_{},
        direction_{} {}

    Ray(glm::vec3 const& origin, glm::vec3 const& distance):
        origin_{origin},
        direction_{glm::normalize(distance)} {}

    glm::vec3 origin_; //= {0.0f, 0.0f, 0.0f};
    glm::vec3 direction_; //= {0.0f, 0.0f, -1.0f};

	Ray transformRay(glm::mat4 const& mat, Ray const& ray) { // hier noch ray eingefügt

		glm::vec4 origin_o{ ray.origin_,1.0f };
		glm::vec4 direction_o{ ray.direction_, 0.0f };

		glm::vec4 origin_homogen = mat * origin_o;
		glm::vec4 direction_homogen = mat * direction_o;

		glm::vec3 origin_i(origin_homogen);  // warum das hier? das ist doppelt gemoppelt
		glm::vec3 direction_i(direction_homogen);

		return Ray{ origin_i, direction_i };
	}
};
# endif //RAY_HPP