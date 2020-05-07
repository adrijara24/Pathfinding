#include "ManhattanHeuristic.h"


//D * (dx + dy)   -- D = cost
float ManhattanHeuristic::CalculateDistanceToEnd(Node* actualNode, Node* checkingNode, Node* endNode)
{
	float dist = 0, dx, dy;
	dx = endNode->GetX() - checkingNode->GetX();
	dy = endNode->GetY() - checkingNode->GetY();
	dx = fabsf(dx);
	dy = fabsf(dy);
	dist = GetCost(actualNode, checkingNode) * (dx + dy);
	return dist;
}
