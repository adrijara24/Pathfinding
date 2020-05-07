#pragma once
#include "Heuristic.h"
class DijkstraHeuristic : public Heuristic
{
	virtual float CalculateDistanceToEnd(Node* actualNode, Node* checkingNode, Node* endNode) override;

};

