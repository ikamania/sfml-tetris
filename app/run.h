#include <iostream>
#include <vector>
#include <cstdlib>
#include <map>
#include <SFML/Graphics.hpp>

#include "map.h"
#include "figures.h"
#include "figure.h"
#include "draw.h"
#include "logic.h"

void run()
{
    std::map<int, sf::Color> colors{{0, sf::Color::Black}, {1, sf::Color::Cyan}, {2, sf::Color::Blue}, {3, sf::Color::Yellow}, {4, sf::Color::Magenta}, {5, sf::Color::Red}};

    Figure figure;

    sf::RenderWindow window(sf::VideoMode({300, 600}), "Tetris");
    window.setFramerateLimit(60);
    
    int t = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                    case (sf::Keyboard::Left):
                        moveFigure(map, figure, -1);
                        break;
                    case (sf::Keyboard::Right):
                        moveFigure(map, figure, +1);
                        break;
                    case (sf::Keyboard::Space):
                        rotateFigure(map, figure);
                        break;
                    default:
                        break;
                }
        }
        t++;
           
        if (t > 15)
        {
            if (figure.isValid())
                fallFigure(map, figure);
            else
            {
                lineDesCheck(map);
                makeFigure(figures, figure, colors);
            }
            t = 0;
        }

        window.clear();

        draw(window, map, colors);
        drawFigure(window, colors, figure);
        drawLines(window, map, 30, sf::Color::White);

        window.display();
    }
}
