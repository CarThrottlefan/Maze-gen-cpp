class Cell
{
    public:
        Cell();
        bool visited = false;
        bool rightWall = true;
        bool leftWall = true;
        bool upWall = true;
        bool downWall = true;
        bool path = false;
};

Cell::Cell()
{
}
