#include "Ball.h"

Ball::Ball(sf::Vector2f pos, sf::Vector2f v, float r, int type, sf::Color color)
    : pos(pos), v(v), r(r), m(r * r * r), type(type), color(color)
{

}