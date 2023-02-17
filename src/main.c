#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}";
const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}";
const char *fragmentShaderSource2 = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
	"}";

unsigned int VBOs[3], VAOs[3];
unsigned int EBO;


unsigned int shaderProgramOrange;
unsigned int shaderProgramYellow;

/* Loads the content of a GLSL Shader file into a char* variable */

void init()
{
	sg_setup(&(sg_desc){
		.context = sapp_sgcontext()
	});

  // vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER); // orange color
	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER); // yellow color
	shaderProgramOrange = glCreateProgram();
	shaderProgramYellow = glCreateProgram(); // the second shader program
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderOrange);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShaderYellow);
	// link shaders
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);
	// second triangle
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

  // set up vertex data (and buffer(s)) and configure vertex attributes
	float orangeTriangle[] = {
			0.5f,  0.5f, 0.0f, // left  
			0.0f,  0.5f, 0.0f, // right 
			0.25f, 0.1f, 0.0f, // top  
	};
	float yellowTriangle[] = {
			0.5f, -0.5f, 0.0f, // left  
			0.0f, -0.5f, 0.0f, // right 
			0.25f,-0.1f, 0.0f  // top  
	};

  float vertices[] = {
  	-0.1f,  0.5f, 0.0f,  // top right
	  -0.1f, -0.5f, 0.0f,  // bottom right
	  -0.5f, -0.5f, 0.0f,  // bottom left
	  -0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	glGenVertexArrays(3, VAOs); 
	glGenBuffers(3, VBOs); 
  glGenBuffers(1, &EBO);
	// first triangle setup
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);  
	glBufferData(GL_ARRAY_BUFFER, sizeof(orangeTriangle), orangeTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 
	// second triangle setup
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);  
	glBufferData(GL_ARRAY_BUFFER, sizeof(yellowTriangle), yellowTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0); 
	// rectangle
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// screen color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void render()
{
	glUseProgram(shaderProgramOrange);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(VAOs[2]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glUseProgram(shaderProgramYellow);
	glBindVertexArray(VAOs[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

sapp_desc sokol_main(int argc, char *argv[])
{ 
	return (sapp_desc){
		.width = 840,
		.height = 600,
		.init_cb = init,
		.frame_cb = render,
	};
}