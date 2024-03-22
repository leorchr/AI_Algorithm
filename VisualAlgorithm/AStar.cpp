#include "AStar.h"

using namespace std;

AStar::~AStar(){}

void AStar::InitMap()
{
	for (int i = 0; i < worldMap.size(); i++)
	{
		for (int j = 0; j < worldMap[i].size(); j++)
		{
			map[i][j] = new Node(Vector2{(float)i, (float)j }, worldMap[i][j]);
			map[i][j]->h = GetDistance(*map[i][j], endNode);
		}
	}
}

void AStar::Pathfinding(Node* startNode, Node* pEndNode)
{
	setEndNode(pEndNode);
	vector<Node*> openNodes;
	vector<Node*> closedNodes;
	openNodes.push_back(startNode);

	while (openNodes.size() > 0) {

		int nodeIndex = GetMinimumF(openNodes);

		currentNode = openNodes[nodeIndex];

		openNodes.erase(openNodes.begin() + nodeIndex);
		closedNodes.push_back(currentNode);

		if (currentNode->position.x == endNode.position.x && currentNode->position.y == endNode.position.y) {
			endNode = *currentNode;
			ShowPath(currentNode);
			return;
		}
		vector<Node*> childrenNodes = GetChildrens(*currentNode);
		for (int i = 0; i < childrenNodes.size(); i++)
		{
			Node* child = childrenNodes[i];
			if (find(closedNodes.begin(), closedNodes.end(), child) != closedNodes.end()) {
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

int AStar::GetMinimumF(vector<Node*> openNodes)
{
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

vector<Node*> AStar::GetChildrens(Node& node)
{
	vector<Node*> childrens;
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

float AStar::GetDistance(Node origin, Node destination)
{
	Vector2 direction = Vector2{ destination.position.x - origin.position.x, destination.position.y - origin.position.y };
	return(pow(direction.x, 2) + pow(direction.y, 2));
}

void AStar::ShowPath(Node* end)
{
	/*Node* current = end;
	while (current->parent != nullptr) {
		cout << "X : " << current->position.x << "\tY : " << current->position.y << endl;
		current = current->parent;
	}*/
}

Node AStar::getEndNode()
{
	return endNode;
}

void AStar::setEndNode(Node *pEndNode)
{
	endNode = *pEndNode;
	for (int i = 0; i < worldMap.size(); i++)
	{
		for (int j = 0; j < worldMap[i].size(); j++)
		{
			map[i][j]->h = GetDistance(*map[i][j], endNode);
		}
	}
}


