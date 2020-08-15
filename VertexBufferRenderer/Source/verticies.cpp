#include "verticies.h"
#include "shaderClass.h"
#include "Debug.h"/*Debug includes iostream and glew*/

/*Dad wants me to just use vectors and not have data that I am trying to turn into a gl buffer be described as an array.
But if I can't do vector math with vectors I don't know how OpenGL is going to do vector math with them. So how do I even know if
OpenGL can even use vectors???*/

/* Nevermind here is how you use vectors https://community.khronos.org/t/creating-a-vbo-with-std-vector/74867 */

/*But actually it was also my stubornness of not using vectors that made me learn better how vector math works
so I actually don't know how to feel about this.*/

verticyBuffer::verticyBuffer()
{
	colorBuf[0] = 1.0f;
	colorBuf[1] = 1.0f;
	colorBuf[2] = 1.0f;
	colorBuf[3] = 1.0f;
	colorPoint = &colorBuf[0];
}

/*Verticy Methods and Constructors*/
verticyBuffer::verticyBuffer(vertex *vertBuffconverter, unsigned int size)
{
	/*Initializer list*/
	colorBuf[0] = 1.0f;
	colorBuf[1] = 1.0f;
	colorBuf[2] = 1.0f;
	colorBuf[3] = 1.0f;
	colorPoint = &colorBuf[0];

	/*Preping for vector pushing*/
	if (size % sizeof(vertex) != 0)/*Why can't I put my array into my vector*/
		std::cout << "WARNING: Incompleted Vertex remainder-> " << sizeof(*vertBuffconverter)%sizeof(vertex) << std::endl;
	/*Instead of a warning here I should probably put an assert*/

	for (unsigned int i = 0; i < size / sizeof(vertex); i += 2)
	{
		verticies.push_back({ vertBuffconverter[i].xCoordinate,vertBuffconverter[i].yCoordinate });
		verticies.push_back({ vertBuffconverter[i + 1].xCoordinate, vertBuffconverter[i + 1].yCoordinate });
		verticies.at(i).printCoordinates();
		verticies.at(i + 1).printCoordinates();
	}
}
void verticyBuffer::addVertex(float x, float y)
{
	vertex genericVerticy;
	genericVerticy.xCoordinate = x;
	genericVerticy.yCoordinate = y;

	verticies.push_back(genericVerticy);
}
void verticyBuffer::displayVerticies()const
{
	for (unsigned int i = 0; i < verticies.size(); i++)
		std::cout << "Verticy " << i+1 << ": @ " << "(" << verticies[i].xCoordinate << ", " << verticies[i].yCoordinate << ")" << std::endl;
}
void verticyBuffer::deleteVertex()
{
	verticies.pop_back();
}
void verticyBuffer::deleteVertex(int positionV)
{
	verticies.erase(verticies.begin()+positionV);
}

/*Order Methods*/
void verticyBuffer::drawOrder()const
{
	for (unsigned int i = 0; i < order.size(); i++)
		std::cout << "Vertex " << order[i] + 1 << ": @ "
		<< "(" << verticies[order[i]].xCoordinate << ", "
		<< verticies[order[i]].yCoordinate << ")" << std::endl;
}
void verticyBuffer::clearOrder()
{
	order.clear();
}

/*Getters*/
std::vector<vertex> verticyBuffer::getVerticies()const { return verticies; }
std::vector<unsigned int> verticyBuffer::getIndices()const { return order; }
float verticyBuffer::getColorBuffer()const { return colorBuf[0]; }/*Returns the first element of the color buffer*/