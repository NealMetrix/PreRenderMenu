#include "shaderClass.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/glew.h>

#include "Debug.h"

shader::shader(std::string filePath)
	:m_filePath(filePath)
{
	m_sRender = glCreateProgram();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexSource = parse("Vertex");
	std::string fragmentSource = parse("Fragment");

	const char* vSrcPtr = &vertexSource[0];
	const char* fSrcPtr = &fragmentSource[0];

	glShaderSource(vertexShader, 1, &vSrcPtr, NULL);
	glShaderSource(fragmentShader, 1, &fSrcPtr, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	glAttachShader(m_sRender, vertexShader);
	glAttachShader(m_sRender, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glLinkProgram(m_sRender);
	glValidateProgram(m_sRender);
}
shader::~shader()
{
	glDeleteProgram(m_sRender);
}

std::string shader::parse(std::string shaderTypeName)
{
	std::ifstream shaderFile(m_filePath);

	std::string line;
	std::stringstream sourceCode;
	bool active = false;
	while (getline(shaderFile,line))
	{
		if (line.find("#Shader") != std::string::npos)
		{
			if (line.find(shaderTypeName) != std::string::npos)
			{
				active = true;
				printActiveTrue(shaderTypeName);
			}
			/*I think that you can't have more than 2 statements in an else condition.
			It depends on the semicolon not the enter line. Proabably is the same for if statements too*/
			else
			{
				active = false;
				printActiveFalse();
			}
		}
		else if (active)
		{
			sourceCode << line << std::endl;
			printShaderLine(line);
		}
	}
	if (sourceCode.str() == "")
		std::cout << "Warning!!! Shader Code Seems To Be Empty. Was active ever true" << std::endl;

	return sourceCode.str();
}

void shader::bind()const
{
	glUseProgram(m_sRender);
}
void shader::unbind()const
{
	glUseProgram(0);
}