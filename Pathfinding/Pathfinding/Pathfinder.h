#pragma once

#include "Node.h"
#include "Heuristic.h"
#include <vector>
#include "GlobalConstants.h"

//Search for the optimal path
std::vector<Node> Search(std::vector<Node> nodes, Node startingNode, Node endNode, bool diagonalMovement, Heuristic* heuristic, char map[SIZE_Y][SIZE_X]);

//Process the node calculating the distance using the heurístic.
bool ProcessNode(Node* actualNode, Node* checkingNode, Node* endNode, std::vector<Node*> &toCheckNodes, Heuristic* heuristic);

//Reverts the path from the end to obtain a vector with the full correct path.
std::vector<Node> CheckFullPath(Node* checkingNode, Node* startingNode, std::vector<Node> nodes);

//Return the node wich coordinates match, if it exists.
Node* GetNodeAt(int x, int y, std::vector<Node>& nodes);

//Return the node with lowest distance(F(n))
Node* GetLowestDistanceNode(std::vector<Node*>& nodes);
