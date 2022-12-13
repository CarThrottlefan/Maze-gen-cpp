#include "cell.h"
#include <vector>
#include <stack>
#include <cstdlib>
#include <iostream>
#include <ctime>

class Maze
{
public:
    Maze(int length, int width);
    void construct(std::vector<std::vector<Cell> > &maze);
    bool isValidMove(int x, int y, int tryX, int tryY);
    bool findPath(int y, int x);
    void constructMaze(int y, int x, std::stack<std::vector<int> > &cellTry, int &count);
    void clearCells();
    void PrintOut();
    bool isVisited();
    private:
    int length, width;
    std::vector<std::vector<Cell>> mazeCells;
};

Maze::Maze(int l, int w)
{
    length = l;
    width = w;
    mazeCells = std::vector<std::vector<Cell>> (l, std::vector<Cell> (w, Cell()));
}

bool Maze::isValidMove(int y, int x, int tryY, int tryX)
{
    if((tryX >= 0) && (tryX < width) && (tryY >= 0) && (tryY < length) && !mazeCells.at(tryY).at(tryX).visited)
    {
        if((!mazeCells.at(y).at(x).leftWall) && (tryX == x - 1))
        {
            return true;
        }

        if((!mazeCells.at(y).at(x).rightWall) && (tryX == x + 1))
        {
            return true;
        }

        if((!mazeCells.at(y).at(x).downWall) && (tryY == y + 1))
        {
            return true;
        }

        if((!mazeCells.at(y).at(x).upWall) && (tryY == y - 1))
        {
            return true;
        }
    }

    return false;
}

void Maze::constructMaze(int y, int x, std::stack<std::vector<int>>& cellTry, int &count)
{
    if(count == width * length)
    {
        return;
    }

    int tryX = x, tryY = y;
    mazeCells.at(y).at(x).visited = true;

    std::vector<std::vector<int> > neighbors;

        cellTry.push({y, x});

        if(x > 0)
        {
            tryX = x - 1;
            if(!mazeCells.at(tryY).at(tryX).visited)
                {
                    neighbors.push_back({tryY, tryX});
                }
            tryX = x;
        }

        if(y > 0)
        {
            tryY = y - 1;
            if(!mazeCells.at(tryY).at(tryX).visited)
                {
                    neighbors.push_back({tryY, tryX});
                }
            tryY = y;
        }

        if(x < width - 1)
        {
            tryX = x + 1;
            if(!mazeCells.at(tryY).at(tryX).visited)
                {
                    neighbors.push_back({tryY, tryX});
                }
            tryX = x;
        }

        if(y < length - 1)
        {
            tryY = y + 1;
            if(!mazeCells.at(tryY).at(tryX).visited)
                {
                    neighbors.push_back({tryY, tryX});
                }
            tryY = y;
        }

    ++count;
 
    if(neighbors.size() == 0)
    {
        cellTry.pop();
        cellTry.pop();
        --count;

        tryY = cellTry.top().at(0); 
        tryX = cellTry.top().at(1);

        constructMaze(tryY, tryX, cellTry, count); 
        return;
    }

    int direction = rand();
    int temp = direction % (neighbors.size());
    
    tryX = neighbors.at(temp).at(1);
    tryY = neighbors.at(temp).at(0);

    if(tryX == x + 1)
    {
        mazeCells.at(y).at(x).rightWall = false;
        mazeCells.at(tryY).at(tryX).leftWall = false;
    }

    if(tryX == x - 1)
    {
        mazeCells.at(y).at(x).leftWall = false;
        mazeCells.at(tryY).at(tryX).rightWall = false;
    }

    if(tryY == y + 1)
    {
        mazeCells.at(y).at(x).downWall = false;
        mazeCells.at(tryY).at(tryX).upWall = false;
    }

    if(tryY == y - 1)
    {
        mazeCells.at(y).at(x).upWall = false;
        mazeCells.at(tryY).at(tryX).downWall = false;
    }

    cellTry.push({tryY, tryX});
    constructMaze(tryY, tryX, cellTry, count);
}

void Maze::clearCells()
{
    for(int i = 0; i < mazeCells.size(); i++)
    {
        for(int j = 0; j < mazeCells.at(0).size(); j++)
        {
            mazeCells.at(i).at(j).visited = false;
        }
    }
}

bool Maze::findPath(int y, int x)
{

    mazeCells.at(y).at(x).visited = true;
    mazeCells.at(y).at(x).path = true;

    int endY = length - 1;
    int endX = width - 1;

    int tryX, tryY;

    if((y == endY) && (x == endX))
    {
        return true;
    }

    std::vector <int> possibleX = {1, -1, 0, 0}; 
    std::vector <int> possibleY = {0, 0, 1, -1}; 

    for(int i = 0; i < 4; i++) 
    {
        tryY = y + possibleY.at(i);
        tryX = x + possibleX.at(i);

        if (isValidMove(y, x, tryY, tryX))
        {
            if(findPath(tryY, tryX)) 
            {
                mazeCells.at(y).at(x).path = true;
                return true;
            }
        }
    }
    mazeCells.at(y).at(x).path = false;

    return false;
}

void Maze::PrintOut()
{
    for(int x = 0; x < mazeCells.at(0).size(); x++)
    {
        std::cout<<"+---";
    }
    std::cout << "+";
    std::cout << std::endl;

    for(int y = 0; y < mazeCells.size(); y++) 
    {
        std::cout << "|";
        for(int x = 0; x < mazeCells.at(y).size(); x++)
        {
            if(mazeCells.at(y).at(x).path)
            {
                std::cout << " . ";
            }
            else
            {
                std::cout << "   ";
            }

            if(mazeCells.at(y).at(x).rightWall)
            {
                std::cout << "|";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;

        for(int x = 0; x < mazeCells.at(y).size(); x++)
        {
            if(mazeCells.at(y).at(x).downWall)
            {
                std::cout << "+---";
            }
            else
            {
                std::cout << "+   ";
            }
        }
        std::cout << "+";
        std::cout << std::endl;
    }
}
