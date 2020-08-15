#include "shaderClass.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/glew.h>

#include "Debug.h"

shader::shader(std::string filePath)
	:m_filePath(filePath)
{
	GLcheckError(m_sRender = glCreateProgram());

	GLcheckError(unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER));
	GLcheckError(unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));

	std::string vertexSource = parse("Vertex");
	std::string fragmentSource = parse("Fragment");

	const char* vSrcPtr = &vertexSource[0];
	const char* fSrcPtr = &fragmentSource[0];

	GLcheckError(glShaderSource(vertexShader, 1, &vSrcPtr, NULL));
	GLcheckError(glShaderSource(fragmentShader, 1, &fSrcPtr, NULL));


	GLcheckError(glCompileShader(vertexShader));
	GLcheckError(glCompileShader(fragmentShader));

	GLcheckError(glAttachShader(m_sRender, vertexShader));
	GLcheckError(glAttachShader(m_sRender, fragmentShader));

	GLcheckError(glDeleteShader(vertexShader));
	GLcheckError(glDeleteShader(fragmentShader));
	
	GLcheckError(glLinkProgram(m_sRender));
	GLcheckError(glValidateProgram(m_sRender));	
}
shader::~shader()
{
	GLcheckError(glDeleteProgram(m_sRender));
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
	GLcheckError(glUseProgram(m_sRender));
}
void shader::unbind()const
{
	GLcheckError(glUseProgram(0));
}

int shader::uniformPrep()
{

	GLcheckError(int uniformLocation = glGetUniformLocation(m_sRender,"vertColor"));

	return uniformLocation;
}
void shader::setUniformWithVerticy(verticyBuffer* vert , int location)
{
	float* colorPtr = (vert->colorPoint);
	float vColor[4] =
	{
		*(colorPtr + 0), *(colorPtr + 1), *(colorPtr + 2), *(colorPtr + 3)
	};
	GLcheckError(glUniform4f(location,vColor[0],vColor[1],vColor[2],vColor[3]));
}
/*Maybe this function should have just had the user set the color with an action and this
was a buffer pointer instead of a *vert as this would be better optimization. It just felt like
it made sense at the time... But I should probably change how the action works.*/