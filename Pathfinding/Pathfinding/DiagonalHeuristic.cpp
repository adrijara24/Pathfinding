#include "DiagonalHeuristic.h"

DiagonalHeuristic::DiagonalHeuristic()
{
	cost2 = sqrtf(cost2Base);
}



float DiagonalHeuristic::CalculateDistanceToEnd(Node* actualNode, Node* checkingNode, Node* endNode)
{
	float dx, dy;
	dx = abs(endNode->GetX() - checkingNode->GetX());
	dy = abs(endNode->GetY() - checkingNode->GetY());
	return cost * (dx + dy) + (cost2 - 2 * cost) * fminf(dx, dy);
	//Alternative version, they are equivalent.
	//return (dx > dy) ? (cost * (dx - dy) + cost2 * dy) : (cost * (dy - dx) + cost2 * dx);
}
