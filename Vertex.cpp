#include "Vertex.h"

static int indexVertex = 0;


Vertex::Vertex()
{
	this->index = indexVertex++;
	this->deg = 0;
}

Vertex::~Vertex()
{

}

void Vertex::addEdge(Vertex* aNeighbor)
{
	this->deg++;
	if (this->neighbors.size() == 0) {
		this->neighbors.insert(this->neighbors.begin(), aNeighbor);
	}
	else {
		this->neighbors.insert(this->neighbors.end(), aNeighbor);
	}


}

void Vertex::resetIndex()
{
	indexVertex = 0;
}