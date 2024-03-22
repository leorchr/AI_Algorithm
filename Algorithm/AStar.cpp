#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;
#define inf std::numeric_limits<float>::max()

struct Vector2 {
	int x, y;
	Vector2(int pX, int pY) : x(pX), y(pY) {}
	float Norm() { return pow(x, 2) + pow(y, 2); }
};

struct Node {
	float g, h, f;
	Vector2 position;
	Node* parent;
	float cost;
	Node(Vector2 pPosition, Node* pParent, float pCost = 1) :
		g(0),
		h(0),
		f(inf),
		position(pPosition),
		cost(pCost),
		parent(nullptr) {}
};

Node startNode = Node(Vector2(4, 1), nullptr);
Node endNode = Node(Vector2(4, 3), nullptr);
Node* currentNode = new Node(Vector2(0, 0), nullptr);

std::vector<std::vector<Node*>> map (5, std::vector<Node*>(5, new Node(Vector2(0,0),nullptr)));
std::vector<std::vector<float>> floatMap = {
{1,1,1,1,1},
{1,2,2,1,1},
{1,1,inf,1,1.5},
{1,1,inf,1,1.5},
{1,1,inf,1,1}};

void InitMap();
void Pathfinding(std::vector<std::vector<Node*>> map, Node* startNode);
int GetMinimumF(std::vector<Node*> openNodes);
std::vector<Node*> GetChildrens(Node& node);
float GetDistance(Node origin, Node destination);
void ShowPath(Node* end);


int main()
{
	InitMap();
	Pathfinding(map, &startNode);
}

void Pathfinding(std::vector<std::vector<Node*>> map, Node* startNode) {
	std::vector<Node*> openNodes;
	std::vector<Node*> closedNodes;
	openNodes.push_back(startNode);

	while (openNodes.size() > 0) {

		int nodeIndex = GetMinimumF(openNodes);
		
		currentNode = openNodes[nodeIndex];

		openNodes.erase(openNodes.begin() + nodeIndex);
		closedNodes.push_back(currentNode);

		if (currentNode->position.x == endNode.position.x && currentNode->position.y == endNode.position.y) {
			ShowPath(currentNode);
			cout << "ohhhhhhhhhhhhhhhhh" << endl;
			return;
		}
		std::vector<Node*> childrenNodes = GetChildrens(*currentNode);
		for (int i = 0; i < childrenNodes.size(); i++)
		{
			Node* child = childrenNodes[i];
			if (std::find(closedNodes.begin(), closedNodes.end(), child) != closedNodes.end()) {
				continue;
			}
			float g = currentNode->g + GetDistance(*currentNode, *child);
			float h = child->h;
			float f = g + h;
			f *= child->cost;
			if (f < child->f) {
				child->g = g;
				child->f = f;
				child->parent = currentNode;
			}
			//

			bool childPos = false; // check if child position is in open list nodes
			bool gValue = false; // check if child.g is higher than the open list node's g
			for (int i = 0; i < openNodes.size(); i++)
			{
				if (child->position.x == openNodes[i]->position.x && child->position.y == openNodes[i]->position.y) childPos = true;
				if (child->g > openNodes[i]->g) gValue = true;
			}
			if (childPos && gValue) continue;
			openNodes.push_back(child);
		}
	}
}

int GetMinimumF(std::vector<Node*> openNodes) {
	float minimumF = openNodes[0]->f;
	int minimumIndex = 0;
	for (int i = 0; i < openNodes.size(); i++)
	{
		if (openNodes[i]->f < minimumF) {
			minimumF = openNodes[i]->f;
			minimumIndex = i;
		}
	}
	return minimumIndex;
}

void InitMap() {
	for (int i = 0; i < floatMap.size(); i++)
	{
		for (int j = 0; j < floatMap[i].size(); j++)
		{
			map[i][j] = new Node(Vector2(i, j), nullptr, floatMap[i][j]);
			map[i][j]->h = GetDistance(*map[i][j], endNode);
			cout << ((map[i][j]->cost == inf) ? "|" : (map[i][j]->cost == 1) ? "." : "*");
		}
		cout << endl;
	}
}

std::vector<Node*> GetChildrens(Node& node) {
	std::vector<Node*> childrens;
	int posX = node.position.x;
	int posY = node.position.y;

	for (int i = node.position.x - 1; i < node.position.x + 2; i++)
	{
		if (i < 0 || i >= map.size()) continue;
		for (int j = node.position.y - 1; j < node.position.y + 2; j++)
		{
			if (j < 0 || j >= map[i].size()) continue;
			if (node.position.x == map[i][j]->position.x && node.position.y == map[i][j]->position.y) continue;
			childrens.push_back(map[i][j]);
		}
	}
	return childrens;
}

float GetDistance(Node origin, Node destination) {
	return(Vector2(destination.position.x - origin.position.x, destination.position.y - origin.position.y).Norm());
}

void ShowPath(Node* end) {
	Node* current = end;
	while (current->parent != nullptr) {
		cout << "X : " << current->position.x << "\tY : " << current->position.y << endl;
		current = current->parent;
	}
};
