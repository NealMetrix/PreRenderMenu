#pragma once
#include <iostream>

/*Designed so we can see the code of our shader on the console if we are in debug mode*/
#if _DEBUG
#define printActiveTrue(type) std::cout << "Now adding shader code to " << type << std::endl
#define printActiveFalse() std::cout << "Shader type name not found... Parser Deactivated" << std::endl
#define printShaderLine(x) std::cout<<x<<std::endl

#else
#define printShaderLine(x)
#define printActiveTrue(type)
#define printActiveFalse()

#endif