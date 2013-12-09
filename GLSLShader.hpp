//A simple class for handling GLSL shader compilation
//Auhtor: Movania Muhammad Mobeen
#pragma once
// #include <GL/glew.h>
#include <map>
#include <string>
#include "glheader.hpp"

using namespace std;

class GLSLShader
{
public:
	GLSLShader(void);
	~GLSLShader(void);	
	void LoadFromString(GLenum whichShader, const string& source);
	void LoadFromFile(GLenum whichShader, const string& filename);
	void CreateAndLinkProgram();
	void Use();
	void UnUse();
	void AddAttribute(const string& attribute);
	void AddUniform(const string& uniform);
	GLuint GetProgram() const;
	//An indexer that returns the location of the attribute/uniform
	GLuint operator[](const string& attribute);
	GLuint operator()(const string& uniform);
	//Program deletion

	void DeleteProgram() {glDeleteProgram(_program);_program=-1;}

  GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
private:
	enum ShaderType {VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER};
	GLuint	_program;
	int _totalShaders;
	GLuint _shaders[3];//0->vertexshader, 1->fragmentshader, 2->geometryshader
	map<string,GLuint> _attributeList;
	map<string,GLuint> _uniformLocationList;
};	
