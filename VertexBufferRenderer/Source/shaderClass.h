#pragma once
#include<string>
#include"verticies.h"

class shader
{
private:
	unsigned int m_sRender;
	std::string m_filePath;
public:
	shader(std::string filePath);
	~shader();

	void bind()const;
	void unbind()const;

	int uniformPrep();
	void setUniformWithVerticy(verticyBuffer* vert, int location);

	std::string parse(std::string shaderTypeName);
};