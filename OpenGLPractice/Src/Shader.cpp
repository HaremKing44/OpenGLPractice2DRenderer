#include "Shader.h"

#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER::FAILED_TO_READ_FROM_FILE!" << std::endl;
	}

	const char* vShaderSource = vertexCode.c_str();
	const char* fShaderSource = fragmentCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderSource, NULL);
	glCompileShader(vertexShader);
	CheckError("VERTEX", vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
	glCompileShader(fragmentShader);
	CheckError("FRAGMENT", fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	CheckError("PROGRAM", ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::CheckError(const std::string& name, const unsigned int& type) const
{
	int success;
	char infoLog[512];

	if (name == "VERTEX" || name == "FRAGMENT")
	{
		glGetShaderiv(type, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(type, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << name << "::COMPILATION_FAILED!\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(type, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(type, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << name << "::LINKING_FAILED!\n" << infoLog << std::endl;
		}
	}
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::SetFloat(const std::string& name, float& value) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value, value, value, 1.f);
}