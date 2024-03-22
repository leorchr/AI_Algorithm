#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "Node.h"
#include "raylib.h"

#define inf std::numeric_limits<float>::max()

class AStar
{
public:

	AStar(std::vector<std::vector<float>> pWorldMap) :
		worldMap(pWorldMap),
		currentNode(new Node(Vector2{ 0, 0 })) {
		map = std::vector<std::vector<Node*>>(pWorldMap.size(), std::vector<Node*>(pWorldMap.size(), new Node(Vector2{0, 0})));
		InitMap();
	}

	~AStar();
	void InitMap();
	void Pathfinding(Node* startNode, Node* endNode);
	int GetMinimumF(std::vector<Node*> openNodes);
	std::vector<Node*> GetChildrens(Node& node);
	float GetDistance(Node origin, Node destination);
	void ShowPath(Node* end);
	Node getEndNode();
	void setEndNode(Node* pEndNode);

private:

	Node startNode;
	Node endNode;
	Node* currentNode;
	std::vector<std::vector<float>> worldMap;
	std::vector<std::vector<Node*>> map;
};
