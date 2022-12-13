#include <vector>
#include <string> 
#include <stack>
#include "maze.h"

int main(int argc, char* argv[])
{
    int x, y;
    int length, width;

    std::vector<std::vector<Cell> > mazeCells;
    std::stack<std::vector<int> > stackCells;

    Cell cell;

    try
    {
        if(argc == 3)
        {
            length = std::stoi(argv[1]);
            width = std::stoi(argv[2]);
            srand(time(NULL));

            if(length < 0 || width < 0)
            {
                throw std::runtime_error("!ERROR!: Invalid parameters");
            }
        }

        else if (argc == 4)
        {   
            length = std::stoi(argv[1]);
            width = std::stoi(argv[2]);
            int temp = std::stoi(argv[3]);
            srand(temp);

            if(length < 0 || width < 0)
            {
                throw std::runtime_error("!ERROR!: Invalid parameters");
            }
        }

        else
        {
            throw std::runtime_error("!ERROR!: Invalid input");
        } 

        Maze maze(length, width);
        int count = 1;

        maze.constructMaze(0, 0, stackCells, count);
        maze.clearCells();
        maze.findPath(0, 0);
        maze.PrintOut();
    }

    catch(std::runtime_error &excpt)
    {
        std::cout << excpt.what() << std::endl;
    }

    catch(std::invalid_argument)
    {
        std::cout << "!ERROR!: Must only input numbers" << std::endl;
    }

    catch(std::out_of_range)
    {
        std::cout << "!ERROR!: Numbers too large" << std::endl;
    }

    return 0;
}
