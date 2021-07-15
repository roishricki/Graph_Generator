#pragma once
#include <vector>

using namespace std;
class Vertex
{
public:
	Vertex();
	~Vertex();
	void addEdge(Vertex* aNeighbor);
	static void resetIndex();


public:
	int index;
	int deg;
	vector<Vertex*> neighbors;

};