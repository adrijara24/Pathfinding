#include "Heuristic.h"
#include <math.h>

bool Heuristic::CalculateHeuristic(Node* actualNode, Node* checkingNode, Node* endNode)
{
	float tSDist = CalculateDistanceFromStart(actualNode, checkingNode);
	float tEDist = CalculateDistanceToEnd(actualNode, checkingNode, endNode);
	return checkingNode->SetDistances(tSDist, tEDist, actualNode);		//True -> Modified value, False -> unmodified
}

float Heuristic::CalculateDistanceFromStart(Node* actualNode, Node* checkingNode)
{
	//ActualDistance + movingCost
	return actualNode->GetToStartDistance() + GetCost(actualNode, checkingNode);
}


float Heuristic::GetCost(Node* actualNode, Node* checkingNode)
{
	
	return GetCost(checkingNode->GetX(), checkingNode->GetY(), actualNode->GetX(), actualNode->GetY());
}

float Heuristic::GetCost(int x1, int y1, int x2, int y2)
{
	//Cost of moving from (x1,y1) to (x2,y2)
	float dx, dy;
	dx = x2 - x1;
	dx *= dx;
	dy = y2 - y1;
	dy *= dy;
	float dist = sqrtf((dx + dy));
	return dist;
}


