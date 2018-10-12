#include <iostream>
#include <vector>
#include <exception>
#include <string>
#include "SFML/Graphics.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    sf::Text text;
    sf::Font font;
    text.setFont(font);
    font.loadFromFile("resourses/Arial.ttf");
    if (!font.loadFromFile("resourses/Arial.ttf")){
        throw std::logic_error("");
    }
    text.setString("Hello world");
    text.setCharacterSize(54);
    text.setColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}
