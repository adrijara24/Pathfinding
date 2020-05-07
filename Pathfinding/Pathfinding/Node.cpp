#include "Node.h"

Node::Node(char sprite, int x, int y, ENodeType nodeType, float distance)
{
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	this->nodeState = ENodeState::UNVISITED;
	this->nodeType = nodeType;
	this->distanceToStart = distance;
	this->distanceToEnd = distance;
	
}

int Node::GetX() const
{
	return x;
}

int Node::GetY() const
{
	return y;
}

char Node::GetSprite() const
{
	return sprite;
}

float Node::GetDistance() const
{
	return distanceToStart + distanceToEnd;
}

float Node::GetToStartDistance() const
{
	return distanceToStart;
}

float Node::GetToEndDistance() const
{
	return distanceToEnd;
}

ENodeType Node::GetNodeType() const
{
	return nodeType;
}

ENodeState Node::GetNodeState() const
{
	return nodeState;
}

Node* Node::GetParentNode() const
{
	return parentNode;
}

void Node::SetSprite(char const sprite)
{
	this->sprite = sprite;
}

void Node::SetParentNode(Node* const node)
{
	parentNode = node;
}

void Node::SetNodeState(ENodeState const nodeState)
{
	this->nodeState = nodeState;
}

void Node::SetToStartDistance(float distance)
{
	distanceToStart = distance;
}

void Node::SetToEndDistance(float distance)
{
	distanceToStart = distance;
}

bool Node::SetDistances(float toStartDist, float toEndDist, Node* parentNode)
{
	if ((toStartDist + toEndDist) < GetDistance())
	{
		distanceToStart = toStartDist;
		distanceToEnd = toEndDist;
		this->parentNode = parentNode;
		nodeState = ENodeState::UNVISITED;
		return true;
	}
	return false;
}

bool Node::operator==(Node nodeToCompare)
{
	//Check if x, y and nodeType are equal.
	if (x != nodeToCompare.x)
		return false;
	if (y != nodeToCompare.y)
		return false;
	if (nodeType != nodeToCompare.nodeType)
		return false;
	return true;
}

bool Node::operator==(Node* nodeToCompare)
{
	return operator==(*nodeToCompare);
}
