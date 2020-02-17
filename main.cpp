#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

#include "tetrahedron.h"
#include "hexahedron.h"
#include "octahedron.h"
#include "dodecahedron.h"
#include "icosahedron.h"
#include "uv_sphere.h"

#include "face.h"

// hello world

void key_callback(GLFWwindow*, int, int, int, int);
void mouse_callback(GLFWwindow*, double, double);
void init_glfw();
void init_opengl();
void init_ground();
void draw();
void draw_solid(Solid*);
void draw_lamp();
void do_movement();
void update_rotation(int);
void draw_ground();
void calculate_ground_vertices();
void updateCamera();
void animation1();
void animation2();
void animation3();
void animation4();
void animation5();
void animation6();
void animation7();
void animation8();
void animation9();
void animation10();
void animation11();
void animation12();
void animation13();
void animation14();
void animation15();
void animation16();
void animation17();

void printDetails();


void draw_face();

GLFWwindow* window;

int width;
int height;

Shader* solid_shader;
Shader* ground_shader;
Shader* lamp_shader;

glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

glm::vec3 default_lamp_pos{0.0, -1.6, 0.0};
// glm::vec3 default_lamp_pos{0.754999,1.00001,-1.51};

glm::vec3 lamp_pos = default_lamp_pos;
bool rotation = false;
unsigned int ground_vao;
unsigned int ground_vbo;
unsigned int sphere_vao;
unsigned int sphere_vbo;
float degrees = 0.0f;
bool keys[1024];
float last_x;
float last_y;
bool first_mouse = true;
int animationNum = 1;

// Camera camera(glm::vec3(0.0, 0.0, 4.0));

float cameraDistance {50.0f};
float azimuth = 0.0f;
float altitude = 10.0f;

// float azimuth = 130.002;
// float cameraDistance = 6.95048;
// float altitude = 11.9401;

glm::vec3 cameraPos {0.0f, 0.0f, cameraDistance};



float start_time{0.0f};
float last_time{0.0f};
float delta_time{0.0f};
float wait_time{0.0f};

int light_type = 2;
bool fill = true;
// bool face = false;
bool avg_normals = false;

float square_size = 0.25f;

struct GroundVertex{
  glm::vec3 pos;
  glm::vec3 color;
};


std::vector<glm::vec3> square_vertices{
	{ -square_size, 0.0, -square_size },
	{ -square_size, 0.0,  square_size },
	{  square_size, 0.0,  square_size },
	{  square_size, 0.0,  square_size },
	{  square_size, 0.0, -square_size },
	{ -square_size, 0.0, -square_size }
};

std::vector<GroundVertex> ground;

Tetrahedron* tetrahedron;
Hexahedron* hexahedron;
Octahedron* octahedron;
Dodecahedron* dodecahedron;
Icosahedron* icosahedron;
Icosahedron* lamp;
//UVSphere* uv_sphere;

Face* face;

enum class SolidType { Tetrahedron, Hexahedron, Octahedron, Dodecahedron, Icosahedron, UVSphere, Face, None };

SolidType solid_type = SolidType::None;



int main(){
	init_glfw();
	init_opengl();
	init_ground();

	model = glm::mat4();

	tetrahedron = new Tetrahedron();
	hexahedron = new Hexahedron();
	octahedron = new Octahedron();
	dodecahedron = new Dodecahedron();
	icosahedron = new Icosahedron(0);
	//uv_sphere = new UVSphere(4);
	face = new Face(0);

	solid_shader = new Shader("shaders/solid.vs", "shaders/solid.fs");
	ground_shader = new Shader("shaders/ground.vs", "shaders/ground.fs");
	lamp_shader = new Shader("shaders/lamp.vs", "shaders/lamp.fs");

	lamp = new Icosahedron(4);

	while(!glfwWindowShouldClose(window)){
		start_time = glfwGetTime();
		delta_time = start_time - last_time;
		last_time = start_time;

		glfwPollEvents();
		do_movement();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		draw();

		switch(solid_type){
			case SolidType::Tetrahedron :
				draw_solid(tetrahedron);
				update_rotation(100);
				break;
			case SolidType::Hexahedron :
				draw_solid(hexahedron);
				update_rotation(100);
				break;
			case SolidType::Octahedron :
				draw_solid(octahedron);
				update_rotation(100);
				break;
			case SolidType::Dodecahedron :
				draw_solid(dodecahedron);
				update_rotation(100);
				break;
			case SolidType::Icosahedron :
				draw_solid(icosahedron);
				update_rotation(100);
				break;
			//case SolidType::UVSphere :
			//	draw_solid(uv_sphere);
			//	update_rotation(100);
			//	break;
			case SolidType::Face :
				draw_solid(face);
				// draw_face();
				// update_rotation(100);
				break;

			case SolidType::None :
				break;
		}

		switch(animationNum) {
			case 1:
				animation1();
				break;
			case 2:
				animation2();
				break;
			case 3:
				animation3();
				break;
			case 4:
				animation4();
				break;
			case 5:
				animation5();
				break;
			case 6:
				animation6();
				break;
			case 7:
				animation7();
				break;
			case 8:
				animation8();
				break;
			case 9:
				animation9();
				break;
			case 10:
				animation10();
				break;
			case 11:
				animation11();
				break;
			case 12:
				animation12();
				break;
			case 13:
				animation13();
				break;
			case 14:
				animation14();
				break;
			case 15:
				animation15();
				break;
			case 16:
				animation16();
				break;
			case 17:
				animation17();
				break;
		}

		glfwSwapBuffers(window);
	}

	delete tetrahedron;
	delete hexahedron;
	delete octahedron;
	delete dodecahedron;
	delete icosahedron;
	//delete uv_sphere;

	glfwTerminate();
}

void init_glfw()
{
	glfwInit();

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	width = mode->width;
	height = mode->height;

	//window = glfwCreateWindow(width, height, "Platonic Solids", nullptr, nullptr);
	window = glfwCreateWindow(width, height, "Platonic Solids", glfwGetPrimaryMonitor(), NULL);
	glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }

	glfwSetInputMode(window, GLFW_STICKY_KEYS, 2);
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, key_callback);
	// glfwSetCursorPosCallback(window, mouse_callback);

	last_x = width / 2;
	last_y = height / 2;

	glViewport(0, 0, width, height);
}

void init_opengl(){
	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT_AND_BACK);
	// glFrontFace(GL_CCW);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// animation
	// view = camera.GetViewMatrix();
	// animation

	// animation
  view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	// animation

	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}

void init_ground(){
	calculate_ground_vertices();

	glGenVertexArrays(1, &ground_vao);
	glGenBuffers(1, &ground_vbo);
	glBindVertexArray(ground_vao);
	glBindBuffer(GL_ARRAY_BUFFER, ground_vbo);
	glBufferData(GL_ARRAY_BUFFER, ground.size()*sizeof(GroundVertex), ground.data(), GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GroundVertex), 0);
	glEnableVertexAttribArray(0);

	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GroundVertex), (void*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void calculate_ground_vertices(){
	int ground_size{4};
	glm::vec3 red{1.0f, 0.0f, 0.0f};
	glm::vec3 white{1.0f, 1.0f, 1.0f};

	for(int row = -ground_size; row < ground_size; row++){
		for(int col = -ground_size; col < ground_size; col++){
			GroundVertex vertex;
			model = glm::mat4();
			model = glm::translate(model, glm::vec3(row*square_size*2, 0.0f, col*square_size*2));
			if(row % 2 == 0){
				if(col % 2 == 0){
					for(auto v : square_vertices){
						vertex.pos = model * v;
						vertex.color = white;
						ground.push_back(vertex);
					}
				}
				else{
					for(auto v : square_vertices){
						vertex.pos = model * v;
						vertex.color = red;
						ground.push_back(vertex);
					}
				}
			} else {
				if(col % 2 != 0){
					for(auto v : square_vertices){
						vertex.pos = model * v;
						vertex.color = white;
						ground.push_back(vertex);
					}
				}
				else{
					for(auto v : square_vertices){
						vertex.pos = model * v;
						vertex.color = red;
						ground.push_back(vertex);
					}
				}
			}
		}
	}
}

void draw(){
	if(fill){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	draw_ground();
	draw_lamp();
}

void draw_ground(){
	// animation
	// view = camera.GetViewMatrix();
	// animation

	// animation
	view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	// animation

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(0.0, -1.5, 0.0));
	ground_shader->use();

	ground_shader->setMat4("model", model);
	ground_shader->setMat4("view", view);
	ground_shader->setMat4("projection", projection);

	ground_shader->setVec3("light_pos", lamp_pos.x, lamp_pos.y, lamp_pos.z);
	ground_shader->setInt("light_type", light_type);
	// animation
	// ground_shader->setVec3("view_pos", camera.Position);
	// animation

	// animation
	ground_shader->setVec3("view_pos", cameraPos);

	glBindVertexArray(ground_vao);
	glDrawArrays(GL_TRIANGLES, 0, ground.size());
	glBindVertexArray(0);
}

void draw_lamp(){
	model = glm::mat4();
	model = glm::translate(model, lamp_pos);
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));

	lamp_shader->use();

	lamp_shader->setMat4("model", model);
	lamp_shader->setMat4("view", view);
	lamp_shader->setMat4("projection", projection);

	lamp->draw();
}

void draw_solid(Solid* solid){
	model = glm::mat4();
	model = glm::rotate(model, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
	solid_shader->use();

	solid_shader->setMat4("model", model);
	solid_shader->setMat4("view", view);
	solid_shader->setMat4("projection", projection);

	solid_shader->setVec3("light_pos", lamp_pos);
	solid_shader->setVec3("view_pos", cameraPos);

	solid_shader->setInt("light_type", light_type);

	solid->draw();
}

void draw_face(){
	model = glm::mat4();
	model = glm::rotate(model, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	solid_shader->use();

	solid_shader->setMat4("model", model);
	solid_shader->setMat4("view", view);
	solid_shader->setMat4("projection", projection);

	solid_shader->setVec3("light_pos", lamp_pos);
	solid_shader->setVec3("view_pos", cameraPos);

	solid_shader->setInt("light_type", light_type);

	face->draw();
}

void update_rotation(int speed){
	if(rotation){
		degrees += delta_time * speed;

		if(degrees > 360.0f || degrees < -360.0f){
			degrees = 0.0f;
		}
	}
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if(key >= 0 && key < 1024){
		if(action == GLFW_PRESS){
			keys[key] = true;
		} else if(action == GLFW_RELEASE){
			keys[key] = false;
		}
	}

	if(key == GLFW_KEY_1 && action == GLFW_PRESS){
		solid_type = SolidType::Tetrahedron;
	}
	if(key == GLFW_KEY_2 && action == GLFW_PRESS){
		solid_type = SolidType::Hexahedron;
	}
	if(key == GLFW_KEY_3 && action == GLFW_PRESS){
		solid_type = SolidType::Octahedron;
	}
	if(key == GLFW_KEY_4 && action == GLFW_PRESS){
		solid_type = SolidType::Dodecahedron;
	}
	if(key == GLFW_KEY_5 && action == GLFW_PRESS){
		solid_type = SolidType::Icosahedron;
	}
	if(key == GLFW_KEY_6 && action == GLFW_PRESS){
		solid_type = SolidType::UVSphere;
	}

	if(solid_type == SolidType::Icosahedron){
		if(key == GLFW_KEY_0 && action == GLFW_PRESS){
			// face = !face;
			// icosahedron->set_face(face);
		}
		if(key == GLFW_KEY_UP && action == GLFW_PRESS){
			icosahedron->increase_recursion();
		}
		if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
			icosahedron->decrease_recursion();
		}
	}

	if(key == GLFW_KEY_F && action == GLFW_PRESS){
		fill = !fill;
	}
	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		rotation = !rotation;
	}
	if(key == GLFW_KEY_L && action == GLFW_PRESS){
		light_type++;
		if(light_type == 3){
			light_type = 0;
		}
	}

	if(key == GLFW_KEY_Q && action == GLFW_PRESS){
		degrees = 0.0f;
		lamp_pos = default_lamp_pos;
	}

	//if(solid_type == SolidType::UVSphere){
	//	if(key == GLFW_KEY_KP_ADD && action == GLFW_PRESS){
	//		uv_sphere->increase();
	//	}
	//	if(key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS){
	//		uv_sphere->decrease();
	//	}
	//}

	if(solid_type == SolidType::Face){
		if(key == GLFW_KEY_KP_ADD && action == GLFW_PRESS){
			face->increase_recursion();
		}
		if(key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS){
			face->decrease_recursion();
		}
	}
}



void do_movement(){
	float speed = 0.1f;

	if(keys[GLFW_KEY_KP_8]){
		lamp_pos.y += 0.1f * speed;
	}
	if(keys[GLFW_KEY_KP_2]){
		lamp_pos.y -= 0.1f * speed;
	}
	if(keys[GLFW_KEY_KP_4]){
		lamp_pos.x -= 0.1f * speed;
	}
	if(keys[GLFW_KEY_KP_6]){
		lamp_pos.x += 0.1f * speed;
	}
	if(keys[GLFW_KEY_KP_DIVIDE]){
		lamp_pos.z += 0.1f * speed;
	}
	if(keys[GLFW_KEY_KP_MULTIPLY]){
		lamp_pos.z -= 0.1f * speed;
	}

	if(keys[GLFW_KEY_W]){
		// camera.ProcessKeyboard(FORWARD, delta_time);
		cameraDistance -= 0.5f * speed;
	}
	if(keys[GLFW_KEY_S]){
		cameraDistance += 0.5f * speed;
	}
	if(keys[GLFW_KEY_A]){
		// camera.ProcessKeyboard(LEFT, delta_time);
	}
	if(keys[GLFW_KEY_D]){
		// camera.ProcessKeyboard(RIGHT, delta_time);
	}

	if(keys[GLFW_KEY_R]){
		degrees += 1.0f;
	}
	if(keys[GLFW_KEY_T]){
		degrees -= 1.0f;
	}

	if(keys[GLFW_KEY_LEFT]) {
		azimuth -= 1.0f;

		if(azimuth < -359.9f) {
		  azimuth = 0.0f;
		}
	}

	if(keys[GLFW_KEY_RIGHT]) {
		azimuth += 1.0f;

    if(azimuth > 360.0f) {
      azimuth = 0.0f;
    }
	}

	if(keys[GLFW_KEY_UP]) {
		if(altitude < 89.0f) {
		  altitude += 1.0f;
		}
	}

	if(keys[GLFW_KEY_DOWN]) {
		if(altitude > 0.0f) {
		  altitude -= 1.0f;
		}
	}

	updateCamera();

}

void updateCamera() {
	cameraPos.x = cos(glm::radians(altitude)) * sin(glm::radians(azimuth)) * cameraDistance;
	cameraPos.y = sin(glm::radians(altitude)) * cameraDistance;
	cameraPos.z = cos(glm::radians(altitude)) * cos(glm::radians(azimuth)) * cameraDistance;

}


void animation1() {
	if(cameraDistance > 7.0f) {
		azimuth += 0.5f;
		cameraDistance -= 0.05f;

		if(azimuth > 359.0f){
			azimuth = 0.0f;
		}
	} else {
		animationNum = 2;
	}

}

void animation2() {
	if(lamp_pos.y < -1.35f) {
		lamp_pos.y += 0.001f;
	} else {
		wait_time += delta_time;
	}

	if(wait_time > 0.5f) {
		wait_time = 0.0f;
		animationNum = 3;
	}
}

void animation3() {
	if(lamp_pos.z > -1.5f) {
		lamp_pos.z -= 0.01f;
		lamp_pos.x += 0.005f;
	} else {
		animationNum = 4;
	}
}

void animation4() {
	wait_time += delta_time;

	if(wait_time > 1.0f) {
		animationNum = 5;
	}
}

void animation5() {
	solid_type = SolidType::Tetrahedron;
	wait_time += delta_time;

	if(azimuth < 90.0) {
		azimuth += 0.1f;
	} else {
		animationNum = 6;
		wait_time = 0.0f;
	}

	if(wait_time > 2.0f) {
		rotation = true;
	}
}

void animation6() {
	solid_type = SolidType::Tetrahedron;

	if(altitude > 0.0f) {
		altitude -= 0.1f;
	} else {
		animationNum = 7;
	}
}

void animation7() {
	solid_type = SolidType::Tetrahedron;

	if(lamp_pos.y < 1.0) {
		lamp_pos.y += 0.01f;
	} else {
		animationNum = 8;
	}
}

void animation8() {
	solid_type = SolidType::Tetrahedron;

	if(azimuth < 100.0f) {
		azimuth += 0.05f;
		altitude += 0.03f;
	} else {
		animationNum = 9;
	}
}

void animation9() {
	solid_type = SolidType::Hexahedron;

	if(azimuth < 110.0f) {
		azimuth += 0.05f;
		altitude += 0.01f;
	} else {
		animationNum = 10;
	}
}

void animation10() {
	solid_type = SolidType::Octahedron;

	if(azimuth < 120.0f) {
		azimuth += 0.05f;
		altitude += 0.01f;
	} else {
		animationNum = 11;
	}
}

void animation11() {
	solid_type = SolidType::Dodecahedron;

	if(azimuth < 130.0f) {
		azimuth += 0.05f;
		altitude += 0.01f;
	} else {
		animationNum = 12;
	}
}

void animation12() {
	solid_type = SolidType::None;
	rotation = false;
	animationNum = 13;
	degrees = 0.0f;
}

void animation13() {
	wait_time += delta_time;

	if(wait_time > 1.0f) {
		solid_type = SolidType::Face;
	}

	if(wait_time > 2.0f) {
		azimuth += 1.0f;
	}

	if(azimuth > 195.0f) {
		wait_time = 0.0f;
		animationNum = 14;
	}
}

void animation14() {
	wait_time += delta_time;

	if(wait_time > 1.0f) {
		face->set_recursion_level(1);
	}

	if(wait_time > 1.5f) {
		azimuth -= 0.5f;
	}

	if(lamp_pos.y > 0.15f) {
		lamp_pos.y -= 0.005f;
	}

	if(wait_time > 3.5f) {
		face->set_recursion_level(2);
	}

	if(wait_time > 5.0f) {
		face->set_recursion_level(3);
	}

	if(wait_time > 6.5f) {
		face->set_recursion_level(4);
	}

	if(azimuth < 0.0f) {
		animationNum = 15;
		wait_time = 0.0f;
	}
}

void animation15(){
	solid_type = SolidType::None;

	if(lamp_pos.y < 1.0f){
		lamp_pos.y += 0.01;
	} else {
		wait_time += delta_time;
	}

	if(azimuth < 90.0f) {
		azimuth += 1.0f;
	}

	if(wait_time > 0.5f) {
		solid_type = SolidType::Icosahedron;
	}

	if(wait_time > 1.5f) {
		rotation = true;
		wait_time = 0.0f;
		animationNum = 16;
	}
}

void animation16(){
	wait_time += delta_time;

	if(wait_time > 1.0f) {
		azimuth += 0.1f;
	}

	if(wait_time > 1.5f) {
		lamp_pos.y -= 0.0025f;
	}


	if(wait_time > 2.0f) {
		icosahedron->set_recursion_level(1);
	}

	if(wait_time > 4.0f) {
		icosahedron->set_recursion_level(2);
	}

	if(wait_time > 6.0f) {
		icosahedron->set_recursion_level(3);
	}

	if(wait_time > 8.0f) {
		icosahedron->set_recursion_level(4);
	}

	if (wait_time > 12.0f) {
		//rotation = false;
		animationNum = 17;
	}


	//if(wait_time > 14.0f) {
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);
	//}
}

void animation17() {
	rotation = false;
}


void printDetails() {
	std::cout << "glm::vec3 default_lamp_pos{" << lamp_pos.x << ',' << lamp_pos.y << ',' << lamp_pos.z << "};" << std::endl;
	// std::cout << "lamp_pos.z: " << lamp_pos.z << std::endl;
	std::cout << "float azimuth = " << azimuth << ';' << std::endl;
	std::cout << "float cameraDistance = " << cameraDistance << ';' << std::endl;
	std::cout << "float altitude = " << altitude << ';' << std::endl;
	std::cout << "float degrees = " << degrees << ';' << std::endl;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
		if(first_mouse)
		{
			last_x = xpos;
			last_y = ypos;
			first_mouse = false;
		}

		float xoffset = xpos - last_x;
		float yoffset = last_y - ypos;  // Reversed since y-coordinates go from bottom to left

		last_x = xpos;
		last_y = ypos;

		// camera.ProcessMouseMovement(xoffset, yoffset);
}
