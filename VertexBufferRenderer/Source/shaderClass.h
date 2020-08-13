#pragma once
#include<string>

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

	std::string parse(std::string shaderTypeName);
};