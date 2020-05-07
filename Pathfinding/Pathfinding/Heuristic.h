#pragma once
#include "Node.h"
#include <math.h>
#include <vector>

extern const int UNINIT_DISTANCE;

class Heuristic
{

public:
	//Calculate distances to checkingNode from actualNode and heuristic from actualNode to endNode.
	virtual bool CalculateHeuristic(Node* actualNode, Node* checkingNode, Node* endNode);

protected:
	virtual float CalculateDistanceFromStart(Node* actualNode, Node* checkingNode);
	virtual float CalculateDistanceToEnd(Node* actualNode, Node* checkingNode, Node* endNode) = 0;
	virtual float GetCost(Node* actualNode, Node* checkingNode);
	virtual float GetCost(int x1, int y1, int x2, int y2);
};

