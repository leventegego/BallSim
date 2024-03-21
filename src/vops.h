#ifndef VOPS_H
#define VOPS_H


#include <SFML/System.hpp>

// 2d vector operations
namespace vec
{
    float size(sf::Vector2f v);
    float dot(sf::Vector2f a, sf::Vector2f b);
    float cross(sf::Vector2f a, sf::Vector2f b);
    sf::Vector2f norm(sf::Vector2f v);
    sf::Vector2f ortho(sf::Vector2f v);

    // size of vector component in direction of par
    float comp_size(sf::Vector2f v, sf::Vector2f par);
    // vector component parallel to par
    sf::Vector2f comp(sf::Vector2f v, sf::Vector2f par);

    sf::Vector2f mirror(sf::Vector2f p, sf::Vector2f v, sf::Vector2f x);
}



#endif


