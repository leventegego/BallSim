#ifndef BALLBOX_H
#define BALLBOX_H


#include <stdlib.h>
#include <vector>
#include <math.h>

#include "Ball.h"
#include "vops.h"

// Stores balls, and handles their motion
class BallBox
{
private:

    sf::Vector2f size;

    const float collisionredothresh = 1;
    const int maxcollisionredos = 1000;

    void update_positions(float deltaTime); // moves the balls according to their speed
    void update_collisions(float deltaTime); // calculates position and speed changes from collisions
    void update_gravity(float deltaTime); // calculates speed change from gravity

    bool ball_collision(Ball &b1, Ball &b2); // returns true, if collision happened. (updates state)
    bool border_collision(Ball &i); // returns true, if collision happened. (updates state)

    // returns true, if a collision happened. (updates state)
    // p and v represent the geometric line of a specific border.
    bool check_border(Ball &b, sf::Vector2f p, sf::Vector2f v);

public:

    BallBox(sf::Vector2f size);

    void update(float deltaTime);


    std::vector<Ball> balls;

    float gravity;
    bool elastic;
    bool borders;

};


#endif
