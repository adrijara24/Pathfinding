#include "EuclideanHeuristic.h"

float EuclideanHeuristic::CalculateDistanceToEnd(Node* actualNode, Node* checkingNode, Node* endNode)
{
	float dx, dy;
	dx = fabsf(endNode->GetX() - checkingNode->GetX());
	dy = fabsf(endNode->GetY() - checkingNode->GetY());
	return GetCost(actualNode, checkingNode) * sqrtf(dx * dx + dy * dy);
}


