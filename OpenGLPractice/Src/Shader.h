#pragma once
#include <glad/glad.h>

#include <fstream>
#include <string>
#include <sstream>

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void Use();
	void Delete();

	void SetFloat(const std::string& name, float& value) const;

private:
	void CheckError(const std::string& name, const unsigned int& type) const;
};