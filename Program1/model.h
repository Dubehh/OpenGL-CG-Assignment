#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h> 
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "objectloader.hpp"
#include "texture.hpp"

using namespace std;
using namespace glm;

struct Material {
	Material(vec3 diffuse, vec3 amb, vec3 spec, float pow) : 
		diffuse(diffuse),
		ambient(amb),
		specular(spec),
		pow(pow){ }

	Material() :
		diffuse(vec3(0.0, 0.0, 0.0)),
		ambient(vec3(0.0, 0.0, 0.0)),
		specular(vec3(.1f)),
		pow(10) {
	}

	vec3 diffuse, ambient, specular;
	float pow;
};


class Model {
private:
	Material mat;
	char * filePath, * texturePath;
	vector<vec3> vertices, normals;
	vector<vec2> uvs;
	mat4 mv;
	GLuint uniform_mv, vao, texture, 
		vbo_vertices, 
		vbo_normals, 
		vbo_uvs;
	bool hasComponents();
public:
	mat4 model;
	vec3 position;
	bool isLoaded = false;
	Model(char* filePath = NULL, char* texturePath = NULL);
	Model* move(vec3);
	Model * rotate(float deg, vec3 axis);
	void setMaterial(Material);
	void load();
	void loadBuffer(GLuint, const mat4&);
	void draw(const mat4&, const mat4&, GLuint);
};

