#include <math.h>
#include "vops.h"

float vec::size(sf::Vector2f v)
{
    return sqrt(dot(v, v));
}


float vec::dot(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}

float vec::cross(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.y - a.y * b.x;
}

sf::Vector2f vec::norm(sf::Vector2f v)
{
    float s = size(v);
    if(s == 0)
        return sf::Vector2f(0, 0);
    else
        return v / s;
}


sf::Vector2f vec::ortho(sf::Vector2f v)
{
    return sf::Vector2f(v.y, -v.x);
}


float vec::comp_size(sf::Vector2f v, sf::Vector2f par)
{
    float s = size(par);
    if(s == 0)
        return 0;
    else
        return dot(v, par) / s;
}


sf::Vector2f vec::comp(sf::Vector2f v, sf::Vector2f par)
{
    return norm(par) * comp_size(v, par);
}

sf::Vector2f vec::mirror(sf::Vector2f p, sf::Vector2f v, sf::Vector2f x)
{
    x = x - p;
    x -= (x - comp(x, v)) * 2.0f;
    return x;
}
