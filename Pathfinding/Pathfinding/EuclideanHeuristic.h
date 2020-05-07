#pragma once
#include "Heuristic.h"
//C * sqrt(dx * dx + dy * dy)
class EuclideanHeuristic : public Heuristic
{
	virtual float CalculateDistanceToEnd(Node* actualNode, Node* checkingNode, Node* endNode) override;
};

