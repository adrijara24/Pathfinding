#include "Pathfinder.h"
#include <iostream>

std::vector<Node> Search(std::vector<Node> nodes, Node start, Node end, bool diagonalMovement, Heuristic* heuristic, char map[SIZE_Y][SIZE_X])
{
	//Eligible nodes to be checked
	std::vector<Node*> toCheckNodes;
	Node* startingNode = nullptr;
	Node* endNode = nullptr;
	for (auto it = nodes.begin(); it != nodes.end(); it++)
	{
		
		if ((*it) == start)
		{
			startingNode = &*it;
		}
		if ((*it) == end)
		{
			endNode = &*it;
		}
	}

	Node* actualNode = startingNode;
	Node* checkingNode = nullptr;
	do
	{
		//Check every node, not only the unvisited ones.
		//Right
		checkingNode = GetNodeAt(actualNode->GetX() + 1, actualNode->GetY(), nodes);
		if (checkingNode != nullptr)
			if (ProcessNode(actualNode, checkingNode, endNode, toCheckNodes, heuristic))
				return CheckFullPath(checkingNode, startingNode, nodes);

		//Left
		checkingNode = GetNodeAt(actualNode->GetX() - 1, actualNode->GetY(), nodes);
		if (checkingNode != nullptr)
			if (ProcessNode(actualNode, checkingNode, endNode, toCheckNodes, heuristic))
				return CheckFullPath(checkingNode, startingNode, nodes);

		//Down
		checkingNode = GetNodeAt(actualNode->GetX(), actualNode->GetY() + 1, nodes);
		if (checkingNode != nullptr)
			if (ProcessNode(actualNode, checkingNode, endNode, toCheckNodes, heuristic))
				return CheckFullPath(checkingNode, startingNode, nodes);

		//Up
		checkingNode = GetNodeAt(actualNode->GetX(), actualNode->GetY() - 1, nodes);
		if (checkingNode != nullptr)
			if (ProcessNode(actualNode, checkingNode, endNode, toCheckNodes, heuristic))
				return CheckFullPath(checkingNode, startingNode, nodes);

		if (diagonalMovement)
		{
			//Right - Down
			checkingNode = GetNodeAt(actualNode->GetX() + 1, actualNode->GetY() + 1, nodes);
			if (checkingNode != nullptr)
				if (ProcessNode(actualNode, checkingNode, endNode, toCheckNodes, heuristic))
					return CheckFullPath(checkingNode, startingNode, nodes);

			//Left - Down
			checkingNode = GetNodeAt(actualNode->GetX() - 1, actualNode->GetY() + 1, nodes);
			if (checkingNode != nullptr)
				if (ProcessNode(actualNode, checkingNode, endNode, toCheckNodes, heuristic))
					return CheckFullPath(checkingNode, startingNode, nodes);

			//Right - Up
			checkingNode = GetNodeAt(actualNode->GetX() + 1, actualNode->GetY() - 1, nodes);
			if (checkingNode != nullptr)
				if (ProcessNode(actualNode, checkingNode, endNode, toCheckNodes, heuristic))
					return CheckFullPath(checkingNode, startingNode, nodes);

			//Left - Up
			checkingNode = GetNodeAt(actualNode->GetX() - 1, actualNode->GetY() - 1, nodes);
			if (checkingNode != nullptr)
				if (ProcessNode(actualNode, checkingNode, endNode, toCheckNodes, heuristic))
					return CheckFullPath(checkingNode, startingNode, nodes);
		}

		//To show checked nodes, purely aesthetic.
		map[actualNode->GetY()][actualNode->GetX()] = '.';

		actualNode->SetNodeState(ENodeState::VISITED);
		actualNode = GetLowestDistanceNode(toCheckNodes);
		//Erase the nodes from the checking vector.
		toCheckNodes.erase(std::find(toCheckNodes.begin(), toCheckNodes.end(), actualNode));

	} while (toCheckNodes.size() != 0);


	return std::vector<Node>();
}

bool ProcessNode(Node* actualNode, Node* checkingNode, Node* endNode, std::vector<Node*>& toCheckNodes, Heuristic* heuristic)
{
	if (checkingNode->operator==(endNode))
	{
		checkingNode->SetParentNode(actualNode);
		return true;
	}
	if (heuristic->CalculateHeuristic(actualNode, checkingNode, endNode))
	{
		toCheckNodes.push_back(checkingNode);
		
	}
	return false;
}

std::vector<Node> CheckFullPath(Node* checkingNode, Node* startingNode, std::vector<Node> nodes)
{
	std::vector<Node> path;
	std::vector<Node> tmpPath;
	tmpPath.push_back(*checkingNode);
	
	//Get the path from the parentNode pointer.
	for (int i = 0; i < tmpPath.size(); i++)
	{
		if (tmpPath[tmpPath.size() - 1].GetParentNode() == startingNode)
		{
			tmpPath.push_back(*startingNode);
			break;
		}
			
		tmpPath.push_back(*tmpPath[tmpPath.size() - 1].GetParentNode());
	}
	
	//Revert the path.
	for (auto it = tmpPath.begin(); it != tmpPath.end(); it++)
	{
		path.push_back(*it);
	}

	return path;
}

Node* GetNodeAt(int x, int y, std::vector<Node>& nodes)
{
	for (auto it = nodes.begin(); it != nodes.end(); it++)
	{
		if ((*it).GetX() == x && (*it).GetY() == y)
			return &*it;	//Direction of the value of the iterator.
	}
	return nullptr;
}

Node* GetLowestDistanceNode(std::vector<Node*>& nodes)
{
	Node* lowestDistNode = nullptr;
	lowestDistNode = nodes[0];
	//Get the unvisited node with lowest distance
	for (auto it = nodes.begin(); it != nodes.end(); it++)
		if ((*it)->GetDistance() < lowestDistNode->GetDistance() && (*it)->GetNodeState() == ENodeState::UNVISITED)
			lowestDistNode = *it;
	return lowestDistNode;
}

