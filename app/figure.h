struct Figure
{
public:
    std::vector<std::vector<int>> c;

    int x;
    int y;
    
    Figure() {}
    Figure(std::vector<std::vector<int>> c, int x, int y)
        : c(c)
        , x(x)
        , y(y)
    {    
    }

    bool isValid()
    {
        if (c.size() > 0)
        {
            return true;
        }
        return false;
    }

    void move(int n)
    {
        x += n;
    }
};
