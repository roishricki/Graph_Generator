#pragma once
#include "Vertex.h"
class Graph
{
public:
	Graph(int numOfVertices);

public:
	vector<Vertex> vertices;
	int numOfEdges;
};
