void draw(sf::RenderWindow &window, std::vector<std::vector<int>> &map, std::map<int, sf::Color> &colors)
{
    int s = 30;
    int x = 0;
    int y = 0;

    for (auto &row : map) 
    {
        for (auto &block : row)
        {
            sf::RectangleShape color(sf::Vector2f(s, s));

            color.setPosition(x, y);
            color.setFillColor(colors[block]);

            window.draw(color);
            
            x += s;
        }
        x = 0;
        y += s;
    }
}

void drawFigure(sf::RenderWindow &window, std::map<int, sf::Color> &colors, Figure &figure)
{
    int s = 30;

    for (int y = 0; y < figure.c.size(); y++)
    {
        for (int x = 0; x < figure.c[y].size(); x++)
        {
            if (figure.c[y][x])
            {
                sf::RectangleShape color(sf::Vector2f(s, s));

                color.setPosition(figure.x * s + x * s, figure.y * s + y * s);
                color.setFillColor(colors[figure.c[y][x]]);

                window.draw(color);
            }
        }
    }
}

void drawLines(sf::RenderWindow &window, std::vector<std::vector<int>> &map, int s, sf::Color color)
{
    for(int y = 0; y < map.size(); y++)
    {
        sf::Vertex line_y[] =
        {
            sf::Vertex(sf::Vector2f(0, y * s), color),
            sf::Vertex(sf::Vector2f(map[0].size() * s, y * s), color)
        };
        
        window.draw(line_y, 2, sf::Lines);
    }
    for (int x = 0; x < map[0].size(); x++)
    {
        sf::Vertex line_x[] =
        {
            sf::Vertex(sf::Vector2f(x * s, 0), color),
            sf::Vertex(sf::Vector2f(x * s, s * map.size()), color)
        };
        
        window.draw(line_x, 2, sf::Lines);
    }
}
