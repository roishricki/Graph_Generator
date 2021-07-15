
#include "Graph.h"


Graph::Graph(int numOfVertices)
{
	this->numOfEdges = 0;
	Vertex::resetIndex();
	for (int i = 0; i < numOfVertices; i++) {
		this->vertices.insert(this->vertices.end(), Vertex());

	} // initialize vertices for graph

}