// Pathfinding.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 

#include <iostream>
#include "Node.h"
#include "Pathfinder.h"
#include "ManhattanHeuristic.h"
#include "DijkstraHeuristic.h"
#include "DiagonalHeuristic.h"
#include "EuclideanHeuristic.h"
#include <chrono>
#include "GlobalConstants.h"

using namespace std;



void InitPathfinding(char map[SIZE_Y][SIZE_X], bool allowDiagonals, Heuristic* heuristic);

void InitPathfinding(char map[SIZE_Y][SIZE_X], bool allowDiagonals, Heuristic* heuristic)
{
    //Copy the map
    char mapToPrint[SIZE_X][SIZE_Y];
    for (int i = 0; i < SIZE_Y; i++)
        for (int j = 0; j < SIZE_X; j++)
            mapToPrint[i][j] = map[i][j];

    std::vector<Node> nodes;

    //Create nodes and add them to the vector.
    Node *startingNode = nullptr, *endingNode = nullptr;
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            if (map[i][j] == 'S')
            {
                Node startNode('S',j,i, ENodeType::START, 0);
                nodes.push_back(startNode);
                if (startingNode == nullptr)
                    startingNode = &startNode;
            }
            if (map[i][j] == 'E')
            {
                Node endNode('E', j, i, ENodeType::END, UNINIT_DISTANCE);
                nodes.push_back(endNode);
                if (endingNode == nullptr)
                    endingNode = &endNode;
            }
            if (map[i][j] == ' ')
            {
                Node walkableNode(' ', j, i, ENodeType::WALKABLE, UNINIT_DISTANCE);
                nodes.push_back(walkableNode);
            }

        }
    }

    if (startingNode == nullptr || endingNode == nullptr)
        return;
    
    std::vector<Node> path;
    path = Search(nodes, *startingNode, *endingNode, allowDiagonals, heuristic, mapToPrint);
    
    //If a path exists, print P for every node.
    if (path.size() > 0) {
        mapToPrint[(*path.begin()).GetY()][(*path.begin()).GetX()] = (*path.begin()).GetSprite();
        mapToPrint[(*(path.end() - 1)).GetY()][(*(path.end() - 1)).GetX()] = (*(path.end() - 1)).GetSprite();
        path.erase(path.begin());
        path.pop_back();
        for (auto it = path.begin(); it != path.end(); it++)
            mapToPrint[(*it).GetY()][(*it).GetX()] = 'P';
    }
    
    

    //Print the map
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            std::cout << mapToPrint[i][j] << " ";
            if (j == SIZE_X - 1)
                std::cout << std::endl;
        }
    }
    //If the returned path vector is empty, print No path found.
    if (path.size() == 0)
        std::cout << "No path found\n";
}



int main()
{

    
    char mapToPrint[SIZE_Y][SIZE_X] = 
    { 
        //Bottle-neck test
        {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'},
        {'X', ' ', 'X', ' ', 'X', 'X', 'X', 'X', ' ', 'X'}, 
        {'X', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', 'X'},
        {'X', ' ', ' ', 'S', ' ', ' ', 'X', ' ', ' ', 'X'},
        {'X', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', 'X'},
        {'X', ' ', ' ', ' ', ' ', ' ', 'X', 'E', ' ', 'X'},
        {'X', ' ', 'X', 'X', 'X', 'X', 'X', ' ', ' ', 'X'}, 
        {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}

        //Normal map
        /*{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'},
        {'X', ' ', 'S', ' ', 'X', 'X', ' ', ' ', ' ', 'X'}, 
        {'X', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', 'X'},
        {'X', ' ', ' ', 'X', 'X', 'X', 'X', ' ', ' ', 'X'},
        {'X', ' ', ' ', ' ', 'X', 'X', ' ', 'X', ' ', 'X'},
        {'X', 'X', 'X', ' ', ' ', ' ', 'X', 'E', ' ', 'X'},
        {'X', ' ', 'X', ' ', 'X', 'X', ' ', 'X', ' ', 'X'}, 
        {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'} */
        
        //Map without any possible path
        /*{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', 'X', ' ', ' ', ' ', 'X', ' ', ' ', ' ', 'X'},
        {'X', 'S', ' ', ' ', 'X', 'X', ' ', ' ', ' ', 'X'},
        {'X', ' ', ' ', 'X', ' ', 'X', ' ', ' ', ' ', 'X'},
        {'X', ' ', ' ', 'X', 'X', 'X', 'X', ' ', ' ', 'X'},
        {'X', ' ', ' ', ' ', 'X', 'X', ' ', 'X', ' ', 'X'},
        {'X', 'X', 'X', ' ', ' ', 'X', 'X', ' ', ' ', 'X'},
        {'X', ' ', 'X', ' ', 'X', 'X', 'E', 'X', ' ', 'X'},
        {'X', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}*/
    };

    //Print base map
    std::cout << "Mapa base:\n";
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            std::cout << mapToPrint[i][j] << " ";
            if (j == SIZE_X - 1)
                std::cout << std::endl;
        }
    }

    //Heuristics:
    DijkstraHeuristic dH;
    ManhattanHeuristic mH;
    DiagonalHeuristic oH;
    EuclideanHeuristic eH;


    cout << "\n Dijkstra with diagonals \n";
    
    auto start = chrono::high_resolution_clock::now();

    InitPathfinding(mapToPrint, true, &dH);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time spent calculating: " << duration.count() << " microseconds" << endl;
    cout << "\n\n\n\n";



    cout << "\n Dijkstra without diagonals \n";
    start = chrono::high_resolution_clock::now();

    InitPathfinding(mapToPrint, false, &dH);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time spent calculating: " << duration.count() << " microseconds" << endl;
    cout << "\n\n\n\n";



    cout << "\n A* with diagonals \n";
    
    start = chrono::high_resolution_clock::now();

    InitPathfinding(mapToPrint, true, &oH);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time spent calculating: " << duration.count() << " microseconds" << endl;
    cout << "\n\n\n\n";
    


    cout << "\n A* without diagonals \n";
    start = chrono::high_resolution_clock::now();

    InitPathfinding(mapToPrint, false, &mH);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time spent calculating: " << duration.count() << " microseconds" << endl;
    cout << "\n\n\n\n";



    cout << "\n Euclidean without diagonals \n";
    start = chrono::high_resolution_clock::now();

    InitPathfinding(mapToPrint, false, &eH);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time spent calculating: " << duration.count() << " microseconds" << endl;
    cout << "\n\n\n\n";



    cout << "\n Euclidean with diagonals \n";
    start = chrono::high_resolution_clock::now();

    InitPathfinding(mapToPrint, true, &eH);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time spent calculating: " << duration.count() << " microseconds" << endl;
    cout << "\n\n\n\n";
}


