#include <iostream>
#include <string>
#include <limits>

using namespace std;
#define inf std::numeric_limits<int>::max()

struct Vertex {
	std::string name;
	int dist;		// distance from origin
	Vertex* prev;	//what is the previous vertex
	bool open;		// if the vertex is still open
};

Vertex Q[7]; //Array that contains all vertices

const int V = 7; //Size of array

int graph[V][V] = {
0, 10, 15, inf, 30, inf, inf,
inf, 0, inf, inf, inf, 57, inf,
15, inf, 0, 16, inf, inf, 52,
inf, inf, 13, 0, inf, inf, inf,
30, inf, inf, inf, 0, 11, 34,
inf, 49, inf, inf, 12, 0, inf,
inf, inf, 63, inf, 35, inf, 0 };



int minDist(Vertex Q[]);
void Dijkstra(int graph[V][V], int source);
int GetSizeOfQ(Vertex Q[]);


void main2()
{
	Dijkstra(graph,0);
}


void Dijkstra(int graph[V][V], int source) {
	for (int i = 0; i < V; i++)
	{
		Q[i].dist = inf;
		Q[i].name = (char)('A'+i);
		Q[i].prev = nullptr;
		Q[i].open = true;
	}
	Q[source].dist = 0;

	while (GetSizeOfQ(Q) > 0)
	{
		int u = minDist(Q);
		Q[u].open = false;
		

		for (int v = 0; v < V; v++)
		{
			if (!Q[v].open || graph[u][v] == inf) continue;
			int temp = Q[u].dist + graph[u][v];
			if (temp < Q[v].dist) {
				Q[v].dist = temp;
				Q[v].prev = &Q[u];
			} 
		}
	}

	cout << "Vertex \t Distance from Source" << endl;
	for (int v = 0; v < V; v++)
		cout << Q[v].name << " \t\t" << Q[v].dist << endl;
}

int minDist(Vertex Q[])
{
	int index = 0;
	int minimum = inf;

	for (int i = 0; i < sizeof(Q); i++)
	{
		if (Q[i].open != false && Q[i].dist <= minimum)
		{
			minimum = Q[i].dist;
			index = i;
		}
	}
	return index;
}

int GetSizeOfQ(Vertex Q[]) {
	int size = 0;
	for (int v = 0; v < V; v++)
	{
		if (Q[v].open) size++;
	}
	return size;
}