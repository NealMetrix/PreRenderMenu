#include "verticies.h"

void verticyBuffer::addVertex(float x, float y)
{
	vertex genericVerticy;
	genericVerticy.xCoordinate = x;
	genericVerticy.yCoordinate = y;

	verticies.push_back(genericVerticy);
}
void verticyBuffer::displayVerticies()const
{
	for (short i = 0; i < verticies.size(); i++)
		std::cout << "Verticy " << i+1 << ": @ " << "(" << verticies[i].xCoordinate << ", " << verticies[i].yCoordinate << ")" << std::endl;
}
void verticyBuffer::clearOrder()
{
	order.clear();
}
void verticyBuffer::deleteVertex()
{
	verticies.pop_back();
}
void verticyBuffer::deleteVertex(int positionV)
{
	verticies.erase(verticies.begin()+positionV);
}
void verticyBuffer::drawOrder()const
{
	for (short i = 0; i < order.size(); i++)
		std::cout << "Vertex " << order[i] + 1 << ": @ "
		<< "(" << verticies[order[i]].xCoordinate << ", "
		<< verticies[order[i]].yCoordinate << ")" << std::endl;
}
unsigned int verticyBuffer::getVerticiesSize()const { return verticies.size(); }

std::vector<vertex> verticyBuffer::getVerticies()const { return verticies; }
std::vector<unsigned int> verticyBuffer::getIndices()const { return order; }