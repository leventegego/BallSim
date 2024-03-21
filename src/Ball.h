#ifndef BALL_H
#define BALL_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Ball
{
public:

    sf::Vector2f pos, v; // position, velocity
    float r, m;          // radius, mass
    int type;
    sf::Color color;

    Ball(sf::Vector2f pos, sf::Vector2f v, float r, int tpye, sf::Color color);
};


#endif
