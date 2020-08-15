#pragma once
#include<iostream>
#include<vector>

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
	float* colorPoint;
	std::vector <unsigned int>order = {};

private:
	std::vector <vertex>verticies = {};
	float colorBuf[4] = { 1.0,1.0,1.0,1.0 };

public:
	verticyBuffer();

	verticyBuffer(vertex *vertBuffConverter, unsigned int size);
	void addVertex(float x, float y);
	void deleteVertex();
	void deleteVertex(int positionV);
	void displayVerticies()const;

	void drawOrder()const;
	void clearOrder();

	std::vector<vertex> getVerticies()const;
	std::vector<unsigned int> getIndices()const;
	float getColorBuffer()const;
};