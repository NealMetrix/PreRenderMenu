#pragma once
#include <iostream>
#include <GL/glew.h>

/*Designed so we can see the code of our shader on the console if we are in debug mode*/
#if _DEBUG
#define printActiveTrue(type) std::cout << "Now adding shader code to " << type << std::endl
#define printActiveFalse() std::cout << "Shader type name not found... Parser Deactivated" << std::endl
#define printShaderLine(x) std::cout<<x<<std::endl
#define ASSERT(x) if(!(x)) __debugbreak()
#define GLcheckError(x) glClearErrors();x;ASSERT(glLog(#x,__FILE__,__LINE__))

#else
#define printShaderLine(x)
#define printActiveTrue(type)
#define printActiveFalse()
#define GLcheckError(x) x

#endif
#if _DEBUG
static void glClearErrors()
{
	while (glGetError() != GL_NO_ERROR){}/*A while loop that just cycles through all gl flags until they are gone*/
}
static bool glLog(const char* function, const char* file, int line)
{

	while (GLenum error = glGetError())
	{
		std::cout << "OpenGL ERROR (" << error << "): " << file << " <- " << function << ":" << line << std::endl;
		return false;
	}
	return true;
}
#endif