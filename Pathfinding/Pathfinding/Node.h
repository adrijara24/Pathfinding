#pragma once
enum ENodeState 
{
	UNVISITED, VISITED
};

enum ENodeType
{
	START, END, WALKABLE, WALL
};



#include "GlobalConstants.h"

class Node
{
public:
	Node(char sprite, int x, int y, ENodeType nodeType, float distance);

	int GetX() const;
	int GetY() const;

	char GetSprite() const;

	//Return the total distance(fromStartDistance + toEndDistance)
	float GetDistance() const;
	float GetToStartDistance() const;
	float GetToEndDistance() const;

	ENodeType GetNodeType() const;
	ENodeState GetNodeState() const;
	Node* GetParentNode() const;

	void SetSprite(char const sprite);

	void SetParentNode(Node* const node);
	void SetNodeState(ENodeState const nodeState);

	void SetToStartDistance(float distance);
	void SetToEndDistance(float distance);

	//Update the distance and the parentNode if the sum of both distances is less than the actual total distance.
	bool SetDistances(float toStartDist, float toEndDist, Node* parentNode);

	//Check if both nodes have the same coordinates and are of the same type.
	bool operator ==(Node nodeToCompare);
	//Check if both nodes have the same coordinates and are of the same type. (calls the other overload operator)
	bool operator==(Node* nodeToCompare);

	
private:
	int x, y;
	char sprite;

	float distanceToStart, distanceToEnd;
	ENodeState nodeState;
	ENodeType nodeType;
	Node* parentNode;

};

