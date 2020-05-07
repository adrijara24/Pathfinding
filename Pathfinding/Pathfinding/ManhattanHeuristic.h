#pragma once
#include "Heuristic.h"
// C * (dx + dy)
class ManhattanHeuristic : public Heuristic
{
	virtual float CalculateDistanceToEnd(Node* actualNode, Node* checkingNode, Node* endNode) override;
};

