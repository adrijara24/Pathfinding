#pragma once
#include "Heuristic.h"
//C * (dx + dy) + (C2 - 2 * C) * min(dx, dy)
class DiagonalHeuristic : public Heuristic
{
public:
	DiagonalHeuristic();
private:
	//Chevishev: D = D2 = 1
	//Octile: D = 1, D2 = sqrt(2) ~1.41
	virtual float CalculateDistanceToEnd(Node* actualNode, Node* checkingNode, Node* endNode) override;
	const float cost = 1, cost2Base = 2;
	float cost2;
};

