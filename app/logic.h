void gravity(std::vector<std::vector<int>> &map)
{
    int cols = map.size() - 1;
    int rows = map[0].size();

    for (int y = cols; y > -1; y--)
    {
        for (int x = 0; x < rows; x++)
        {
            if (y != 0 && map[y - 1][x] && !map[y][x])
            {
                map[y][x] = map[y - 1][x];
                map[y - 1][x] = 0;
            }
        }
    }
}

void lineDes(std::vector<std::vector<int>> &map, int line)
{
    int row_size = map[0].size();

    for (int x = 0; x < row_size; x++)
    {
        map[line][x] = 0;
    }

    gravity(map);
}

void lineDesCheck(std::vector<std::vector<int>> &map)
{
    int counter = 0;
    int cols_co = 0;
    int row_size = map[0].size();

    for (auto cols : map)
    {
        for (auto color : cols)
        {
            if (color)
            {
                counter += 1;
            } else 
            {
                break;
            }
        }
        if (counter == row_size)
        {
            lineDes(map, cols_co);
            gravity(map);
        }
        counter = 0;
        cols_co += 1;
    }
}

void makeFigure(std::vector<std::vector<std::vector<int>>> &figures, Figure &figure, std::map<int, sf::Color> &colors)
{
    srand(static_cast<unsigned>(time(0)));

    int random_f = rand() % 7;

    std::vector<std::vector<int>> c_figure = figures[1];

    int random_x = rand() % (10 - c_figure[0].size());
    int random_c = rand() % (colors.size() - 1) + 1;

    for (int i = 0; i < c_figure.size(); i++)
    {
        for (int j = 0; j < c_figure[i].size(); j++)
        {
            if (c_figure[i][j])
                c_figure[i][j] = random_c;
            else 
                c_figure[i][j] = 0;
        }
    }

    figure = Figure(c_figure, random_x, 0);
}

void fallFigure(std::vector<std::vector<int>> &map, Figure &figure)
{
    bool hit = false;

    for (int y = 0; y < figure.c.size(); y++)
    {
        for (int x = 0; x < figure.c[y].size(); x++)
        {
            if (figure.c[y][x])
            {
                if (figure.y + y + 1 >= map.size() || (figure.y + y + 1 < map.size() && (figure.x + x < 0 || figure.x + x >= map[0].size() || map[figure.y + y + 1][figure.x + x])))
                {
                    hit = true;
                    break;
                }
            }
        }
        if (hit)
            break;
    }

    if (!hit) 
        figure.y += 1;
    else
    {
        for (int y = 0; y < figure.c.size(); y++)
        {
            for (int x = 0; x < figure.c[y].size(); x++)
            {
                if (figure.c[y][x])
                    map[figure.y + y][figure.x + x] = figure.c[y][x];
            }
        }
        figure.c = {};
    }
}

void moveFigure(std::vector<std::vector<int>> &map, Figure &figure, int n)
{
    bool free = true;
        
    for (int y = 0; y < figure.c.size(); y++)
    {
        for (int x = 0; x < figure.c[0].size(); x++)
        {
            if (!figure.c[y][x])
                continue;
                
            if (n > 0) 
            {
                if (figure.x + x + 1 > map[0].size() || map[figure.y + y][figure.x + x + 1]) 
                {
                    free = false;
                    break;                 
                }
            }

            if (n < 0) 
            {
                if (figure.x + x - 1 > map[0].size() || map[figure.y + y][figure.x + x - 1]) 
                {
                    free = false;
                    break;                 
                }
            }
        }
    }

    if (free)
        figure.move(n);
}

void rotateFigure(std::vector<std::vector<int>> &map, Figure &figure)
{
    std::vector<std::vector<int>> r_figure(figure.c[0].size(), std::vector<int>(figure.c.size()));

    for (int y = 0; y < figure.c.size(); y++)
    {
        for (int x = 0; x < figure.c[0].size(); x++)
        {
            r_figure[x][figure.c.size() - y - 1] = figure.c[y][x];
        }
    }
    
    int free = true;
    for (int y = 0; y < r_figure.size(); y++)
    {
        for (int x = 0; x < r_figure[0].size(); x++)
        {
            if (figure.y < 0 || figure.y + y > map.size() || map[figure.y + y][figure.x + x])
            {
                free = false;
                break;
            }
        }
        if (!free)
            break;
    }

    if (free && figure.x + figure.c[0].size() < 10)
        figure.c = r_figure;
}
