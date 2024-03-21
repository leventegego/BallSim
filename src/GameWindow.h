#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>

#include <SFML/Graphics.hpp>

#include "Ball.h"
#include "BallBox.h"

// Creates the simulation and handles user input
class GameWindow
{
private:

    const float speedmultiplier = 2.0f;
    const float dtmax = 0.025;
    const int maxballcount = 75;

    BallBox box;

    bool paused;
    bool doupdate;

    float ballsize;
    int balltype;

    sf::Vector2f mousestart;
    bool pressed;

    sf::RenderWindow window;
    sf::Clock clock;


    void handle_events();
    void draw(bool clear, float deltaTime);

    sf::Color get_ballcolor();

    void start_placement(sf::Vector2f pos);
    void end_placement(sf::Vector2f pos);
    void cancel_placement();

    void remove_at(sf::Vector2f pos);
    void remove_last();

    void set_size(int size);
    void change_type();

    void toggle_elastic();
    void toggle_borders();

    void toggle_paused();
    void update_once();

    void accelerate(float factor);
    void add_gravity(float delta);


public:

    GameWindow(int wx, int wy);
    void run();
};

#endif


