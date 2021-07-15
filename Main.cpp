#define _CRT_SECURE_NO_WARNINGS
#include "Vertex.h"
#include "Graph.h"
#include<fstream>
#include<ctime>
#include<iomanip>
#include<iostream>
#include<vector>
#include<time.h>
#include<queue>

using namespace std;

#define V 1000

typedef struct {
	int distance;
	bool isVisited;
}node;

typedef struct {
	double probability;
	double result;
}graphStat;

Graph build_random_graph(int v, double probability);
float get_random();
bool Is_Isolated(const Graph& G);
node* BFS(const Graph& G, int = 0);
void test();
int diameter(const Graph& G);
bool connectivity(const Graph& G);
void createFiles(graphStat* arg1, graphStat* arg2, graphStat* arg3);

int main()
{

	test();


	system("pause");


	return 0;
}

float get_random() {						 // pick random number between 0.0 to 100.0
	float x = (rand() % 100); // get integer between 0-99
	x += (((rand()) % 101) / 100.0); // get remainder between 0.00 to 1.00 --> (rand()%101/100) allow to get 1.00  

	return  x;
}

Graph build_random_graph(int v, double probability) {
	Graph tempGraph(v);
	float vertexP; //was double
	for (int i = 0; i < v; i++) { // adding edge between two vertices
		for (int j = i + 1; j < v; j++) {
			vertexP = get_random();
			if (vertexP <= probability * 100) {   //set random edges
				tempGraph.numOfEdges++;
				tempGraph.vertices.at(i).addEdge(&tempGraph.vertices.at(j));
				tempGraph.vertices.at(j).addEdge(&tempGraph.vertices.at(i));
			}
		}
	}

	return tempGraph;
}

bool Is_Isolated(const Graph& G) {
	for (int i = 0; i < G.vertices.size(); i++) {
		if (G.vertices.at(i).deg == 0) {
			return true;
		}
	}

	return false;
}

node* BFS(const Graph& G, int index)
{
	node* bfs = new node[V]; 
	queue<Vertex> que;

	for (int i = 0; i < G.vertices.size(); i++) {
		bfs[i].distance = -1;
		bfs[i].isVisited = false;
	}
	que.push(G.vertices.at(index));
	bfs[index] = { {0},{true} };
	while (!que.empty()) {
		Vertex curVertex = que.front();
		for (int i = 0; i < curVertex.deg; i++) {
			if (!bfs[curVertex.neighbors.at(i)->index].isVisited) {
				que.push(G.vertices.at(curVertex.neighbors.at(i)->index));
				bfs[curVertex.neighbors.at(i)->index] = { {bfs[curVertex.index].distance + 1}, {true} };

			}
		}
		que.pop();
	}
	return bfs;
}

bool connectivity(const Graph &G) {

	node* resultBFS;
	if ((G.vertices.size() - 1 > G.numOfEdges) || (Is_Isolated(G) == true)) {
		return false;
	}
	resultBFS = BFS(G);
	for (int i = 0; i < G.vertices.size(); i++) {
		if (resultBFS[i].distance == -1) {
			delete resultBFS;
			return false;

		}
	}
	delete resultBFS;

	return true;
}


void test() {

	srand((unsigned)time(NULL));
	int diam;
	graphStat connectivityStat[10] = { { 0.00551,0.0 }, { 0.00613,0.0 }, { 0.00654,0.0 }, { 0.00672,0.0 }, { 0.00685,0.0 }, 	 //Threshold1 = Threshold3 so they have same probability array
									 { 0.0075,0.0 }, { 0.008,0.0 }, { 0.0085,0.0 }, { 0.0092,0.0 }, { 0.012,0.0 } };
	graphStat isolatedStat[10]{ { 0.00452,0.0 }, { 0.00581,0.0 }, { 0.00621,0.0 }, { 0.00652,0.0 }, { 0.00685,0.0 }, 	 //Threshold1 = Threshold3 so they have same probability array
									 { 0.0075,0.0 }, { 0.008,0.0 }, { 0.0085,0.0 }, { 0.0095,0.0 }, { 0.012,0.0 } };
	graphStat diameterStat[10] = { {0.1061,0.0},{0.1089,0.0},{0.1121,0.0},{0.1127,0.0},{0.1144,0.0},
								   {0.11756,0.0}, {0.1184,0.0},{0.1211,0.0},{0.1273,0.0},{0.1422,0.0} };

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 500; j++) {
			Graph diameterGraph = build_random_graph(V, diameterStat[i].probability);
			Graph isolatedGraph = build_random_graph(V, isolatedStat[i].probability);
			Graph connectivityGraph = build_random_graph(V, connectivityStat[i].probability);
			if (Is_Isolated(isolatedGraph)) {
				isolatedStat[i].result++;
			}
			if (connectivity(connectivityGraph)) {
				connectivityStat[i].result++;
			}
			diam = diameter(diameterGraph);
			if ((diam <= 2) && (diam != -1)) {				 // cause -1 present infinity
				diameterStat[i].result++;
			}
		}

		isolatedStat[i].result /= 500.0;
		connectivityStat[i].result /= 500.0;
		diameterStat[i].result /= 500.0;

		//the comment below is an optional for print results
		
		/*
		cout<< "---------------------------------------------------------------"<<endl; 
		cout<< " iteration "<<i+1<<"/10"<<" loop"<<endl;
		cout << "diameter : " << diameterStat[i].result * 100 << "%" << endl;
		cout << "isolated : " << isolatedStat[i].result * 100 << "%" << endl;
		cout << "connectivity : " << connectivityStat[i].result * 100 << "%" << endl;
		cout<< "---------------------------------------------------------------"<<endl; 
		*/

	}

	createFiles(connectivityStat, diameterStat, isolatedStat);

}


int diameter(const Graph& G) {
	node* diameterG;
	int maxDiameter = -1;// -1 present infinity
		for (int i = 0; i < G.vertices.size(); i++) {
		diameterG = BFS(G, i);
			for (int j = 0; j < G.vertices.size(); j++) {

			if (diameterG[j].distance == -1) {
				delete diameterG;
				return -1;
			}
			if ((diameterG[j].distance > maxDiameter) && (i != j)) {
				maxDiameter = diameterG[j].distance;
			}
		}
		delete diameterG;
	}

	return maxDiameter;

}



void createFiles(graphStat* arg1, graphStat* arg2, graphStat* arg3) {
	ofstream connectivityFile;
	ofstream diameterFile;
	ofstream isolatedFile;
	connectivityFile.open("ConnectivityCSV.csv");
	isolatedFile.open("IsolatedCSV.csv");
	diameterFile.open("DiameterCSV.csv");
	if (!connectivityFile) {
		cout << "File is not open \n";
		exit(0);
	}
	if (!isolatedFile) {
		cout << "File is not open \n";
		exit(0);
	}
	if (!diameterFile) {
		cout << "File is not open \n";
		exit(0);
	}
	for (int i = -1; i < 10; i++) {
		if (i == -1) {
			connectivityFile << "  P  ";
			diameterFile << "  P  ";
			isolatedFile << "  P  ";
		}
		else {
			connectivityFile << ",  " << arg1[i].probability << "  ";
			diameterFile << ",  " << arg2[i].probability << "  ";
			isolatedFile << ",  " << arg3[i].probability << "  ";
		}
	}
	connectivityFile << "\n";
	diameterFile << "\n";
	isolatedFile << "\n";

	for (int j = -1; j < 10; j++) {
		if (j == -1) {
			connectivityFile << "  Connectivity  ";
			diameterFile << "  Diameter  ";
			isolatedFile << "  Isolated  ";
		}
		else {
			connectivityFile << ",  " << arg1[j].result << "  ";
			diameterFile << ",  " << arg2[j].result << "  ";
			isolatedFile << ",  " << arg3[j].result << "  ";
		}
	}

	connectivityFile.close();
	diameterFile.close();
	isolatedFile.close();
}
