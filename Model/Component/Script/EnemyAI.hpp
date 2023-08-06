#ifndef COMPONENTS_ENEMY_AI_HPP
#define COMPONENTS_ENEMY_AI_HPP

#include "../../Pooling/Tank/Player.hpp"

#include "../Component.hpp"

#include "../../Enum/EnumComponentType.hpp"
#include "../../Enum/EnumPoolTag.hpp"

#include "../../../Controller/Singleton/MapManager.hpp"
#include "../../../Controller/Singleton/GameObjectManager.hpp"
#include "../../../Controller/Singleton/ObjectPoolManager.hpp"

namespace ai {
    using namespace std;
    //copypasted from A* code - Joachim
    struct Point{
        int x, y;
    };

    struct Node{
        Point pointPosition;
        int g;  // distance
        int h;  // heuristic
        int f;  // cost
        Node* pParent;  // linked list :(

        Node(Point pointPosition, int g, int h, Node* pParent) : pointPosition(pointPosition), g(g), h(h), pParent(pParent) {
            f = g + h;
        }
    };

    //for priority_queue
    struct CompareNodes{
        bool operator()(Node* nodeA, Node* nodeB) {
            return nodeA->f > nodeB->f;
        }
    };

    //check if point is valid, return boolean if true or false
    bool isValid(int x, int y, int nRows, int nCols, vector<vector<int>>& vecBoard, vector<vector<bool>>& vecVisited) {
        /*in pseudocode
            if(x && y are within bounds) && if(vecBoard[x][y] was not visited)
        */
        if (x < 0 || x >= nCols || y < 0 || y >= nRows || vecVisited[y][x] || vecBoard[y][x] == 1 || vecBoard[y][x] == 2){
            return false;
        }
        return true;
    }

    //heuristics
    int calculateHeuristic(Point pointCurrent, Point pointEnd) {
        return abs(pointCurrent.x - pointEnd.x) + abs(pointCurrent.y - pointEnd.y);
    }

    //finds point above, right, below, and to the left of the point in that order; returns vector of valid points
    vector<Point> getNeighbors(Point pointCurrent, int nRows, int nCols, vector<vector<int>>& vecBoard, vector<vector<bool>>& vecVisited) {
        // up, right, down, left; used to get direction
        int dx[] = {-1, 0, 1, 0}; 
        int dy[] = {0, 1, 0, -1};

        vector<Point> vecNeighbors;

        //find neighboring points up, right, down, left respectively
        for (int i = 0; i < 4; i++) {
            int newX = pointCurrent.x + dx[i];
            int newY = pointCurrent.y + dy[i];
            if (isValid(newX, newY, nRows, nCols, vecBoard, vecVisited)) {
                vecVisited[newY][newX] = true;
                vecNeighbors.push_back({newX, newY});
            }
        }

        return vecNeighbors;
    }

    //uses queue and a loop to find a path to the destination, returns a vector of points which represents the path found going to the player
    vector<Point> findPath(vector<vector<int>>& vecBoard, Point pointStart, Point pointEnd) {
        int nRows = vecBoard.size();
        int nCols = vecBoard[0].size();
        
        //i wish this was discussed in gdprog
        priority_queue<Node*, vector<Node*>, CompareNodes> queNode;

        vector<vector<Node*>> vecNodes(nRows, vector<Node*>(nCols, nullptr));

        int h = calculateHeuristic(pointStart, pointEnd);
        Node* nodeStart = new Node(pointStart, 0, h, nullptr);
        vecNodes[pointStart.y][pointStart.x] = nodeStart;
        queNode.push(nodeStart);

        //so we know if we've been there before
        vector<vector<bool>> vecVisited(nRows, vector<bool>(nCols, false));

        vecVisited[pointStart.y][pointStart.x] = true;

        while (!queNode.empty()) {
            Node* nodeCurrent = queNode.top();
            queNode.pop();

            Point pointCurrent = nodeCurrent->pointPosition;
            if (pointCurrent.x == pointEnd.x && pointCurrent.y == pointEnd.y) {
                break;
            }

            vecVisited[pointCurrent.x][pointCurrent.y] = true;

            vector<Point> vecNeighbors = getNeighbors(pointCurrent, nRows, nCols, vecBoard, vecVisited);
            for (Point pointNeighbor : vecNeighbors) {
                int newX = pointNeighbor.x;
                int newY = pointNeighbor.y;

                int g = nodeCurrent->g + 1; // cost to move to the neighbor is always 1
                int h = calculateHeuristic(pointNeighbor, pointEnd);
                int f = g + h;

                Node* nodeNeighbor = vecNodes[newX][newY];
                if (nodeNeighbor == nullptr) {
                    nodeNeighbor = new Node(pointNeighbor, g, h, nodeCurrent);
                    vecNodes[newY][newX] = nodeNeighbor;
                    queNode.push(nodeNeighbor);
                } 
                else if (g < nodeNeighbor->g) {
                    nodeNeighbor->g = g;
                    nodeNeighbor->f = f;
                    nodeNeighbor->pParent = nodeCurrent;
                }
            }
        }

        vector<Point> vecPath;

        //this too longer than expected, been crashing my BFS code that i based my A* code on
        //return empty vector if there is no Node for end point
        if(vecNodes[pointEnd.y][pointEnd.x] == nullptr){
            return {};
        }

        //pushes points into the path vector by traversing points pushed in the linked lists
        Node* nodeCurrent = vecNodes[pointEnd.y][pointEnd.x];
        while (nodeCurrent != nullptr) {
            vecPath.push_back(nodeCurrent->pointPosition);
            nodeCurrent = nodeCurrent->pParent;
        }

        return vecPath;
    }
}

namespace components {
    using namespace controllers;

    class EnemyAI : public Component {
        private:
            float fSpeed;
            float fFrameInterval;
            float fTicks;

            int nPrevMove;

            int nX, nY;
            
        public:
            EnemyAI(std::string strName);

        public:
            void perform();
    };
}

#endif