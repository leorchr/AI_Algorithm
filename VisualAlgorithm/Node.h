#pragma once
#include "raylib.h"
#define inf std::numeric_limits<float>::max()

class Node {
public:
	float g, h, f;
	Vector2 position;
	Node* parent;
	float cost;
	Node():
		g(0),
		h(0),
		f(inf),
		position(Vector2{0,0}),
		cost(1),
		parent(nullptr) {}
	Node(Vector2 pPosition, float pCost = 1) :
		g(0),
		h(0),
		f(inf),
		position(pPosition),
		cost(pCost),
		parent(nullptr) {}
};