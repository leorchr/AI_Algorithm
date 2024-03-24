#include "raylib.h"
#include "AStar.h"
#include "Node.h"
#include <iostream>

using namespace std;

void Update();
void Draw();
void DrawMap();
void DrawPath();
void DrawGrid();

std::vector<std::vector<float>> worldMap = {
{1,1,1,1,1,1,1,1,1,1},
{1,1,2,1,1,1,1,1,1,1},
{1,1,2,1,1,1,1,1,1,1},
{1,1,2,1,1,1,1,1,1,1},
{1,1,2,1,1.5,1,1,1,1,1},
{1,1,1.5,1,1.5,1,1,1,1,1},
{1,1,inf,1,1.5,1,1,2,1,1},
{1,1,inf,1,1.5,1,2,2,1,1},
{1,1,inf,1,1.5,1,1,2,1,1},
{1,1,inf,1,1,1,1,1,1,1}};

Vector2 startPos = Vector2{ 0, 0 };
Node startNode = Node(startPos);
AStar star = AStar(worldMap);

const int screenWidth = 800;
const int screenHeight = 800;
float tileSize = screenHeight / worldMap.size();

int main() {
    InitWindow(screenWidth, screenHeight, "A Starrrrrrrrrrrrr");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }

    CloseWindow();
    return 0;
}

void Update() {
    Vector2 goal = { 0,0 };
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        star = AStar(worldMap);
        goal = GetMousePosition();
        float positionX = int(goal.y/tileSize);
        float positionY = int(goal.x/tileSize);
        Node endNode = Node(Vector2{ positionX, positionY });
        cout << positionX << "  " << positionY << endl;
        star.setEndNode(&endNode);
        star.Pathfinding(&startNode, &endNode);
        startNode = Node(Vector2{ endNode.position.x,endNode.position.y });
    }
}

void Draw() {
    DrawMap();
    DrawPath();
    DrawGrid();
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
}


void DrawPath() {
    Node pathNode = star.getEndNode();
    while (pathNode.parent != nullptr) {
        DrawCircle(tileSize * pathNode.position.y + tileSize / 2, tileSize * pathNode.position.x + tileSize / 2, tileSize/4,{ 240,124,255,255 });
        pathNode = *pathNode.parent; {
        }
    }
    DrawCircle(tileSize * pathNode.position.y + tileSize / 2, tileSize * pathNode.position.x + tileSize / 2, tileSize / 2, { 240, 124, 255, 255 });
}

void DrawMap() {
    for (int i = 0; i < worldMap.size(); i++)
    {
        for (int j = 0; j < worldMap[i].size(); j++)
        {
            Color color;
            if (worldMap[i][j] == inf) color = { 0 , 30 , 240 , 240 };
            if (worldMap[i][j] == 1) color = { 164 , 240 , 95 , 240 };
            if (worldMap[i][j] == 1.5f) color = { 140 , 70 , 60 , 150 };
            if (worldMap[i][j] == 2) color = { 240 , 140 , 10 , 240 };
            DrawRectangle(tileSize * j, tileSize * i, tileSize, tileSize, color);
        }
    }
}

void DrawGrid() {
    for (int i = 0; i < tileSize + 1; i++) {
        DrawLine(tileSize * i, 0, tileSize * i, screenHeight, WHITE);
    }
    for (int i = 0; i < tileSize + 1; i++) {
        DrawLine(0, tileSize * i, screenWidth, tileSize * i, WHITE);
    }
}