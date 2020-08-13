#pragma once
#include<vector>

#include "Debug.h"/*Debug includes Iostream*/

struct vertex
{
	float xCoordinate;
	float yCoordinate;

	void printCoordinates()
	{
		std::cout << "X: " << xCoordinate << " Y: " << yCoordinate << std::endl;
	}
};

class verticyBuffer
{
public:
	std::vector <unsigned int>order = {};
private:
	std::vector <vertex>verticies = {};

public:
	void addVertex(float x, float y);
	void deleteVertex();
	void clearOrder();
	void deleteVertex(int positionV);
	void displayVerticies()const;
	void drawOrder()const;
	unsigned int getVerticiesSize()const;
	std::vector<vertex> getVerticies()const;
	std::vector<unsigned int> getIndices()const;
};

/*I tried to template the last 2 functions but couldn't figure out how to do it.
Should probably try some other practice examples to practice templates

I can't figure out why this won't work. It's something about pointer.*/
/*
static vertex* verticyGeneratedBuffer(verticyBuffer& vert)
{
	std::cout << "Loading Vertex" << std::endl;
	const int vertexArraySize = vert.getVerticiesSize() / sizeof(vertex);
	vertex* vertexdrawBuffer = new vertex[vertexArraySize];

	for (int i = 0; i < sizeof(vert.getVerticiesSize()); i++)
		std::cout<< vert.getVerticies().begin + i <<std::endl;

	return vertexdrawBuffer;
}

static unsigned int* indicyGeneratedBuffer(verticyBuffer& vert)
{
	std::cout << "Setting Draw Order" << std::endl;
	const int orderSize = vert.getIndices().size()/sizeof(unsigned int);
	unsigned int* indices = new unsigned int[orderSize];

	for (int i = 0; i < sizeof(vert.getIndices()); i++)
		std::cout << vert.getIndices().begin + i << std::endl;

	return indices;
}
*/
