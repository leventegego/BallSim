#include "GameWindow.h"

GameWindow::GameWindow(int wx, int wy)
    : box(sf::Vector2f(wx, wy)), paused(false), doupdate(false), ballsize(20), balltype(0), pressed(false), // wx(wx), wy(wy),
      window(sf::VideoMode(wx, wy), "", sf::Style::Titlebar | sf::Style::Close)
{ }

void GameWindow::run()
{
    while (window.isOpen())
    {
        handle_events();

        if(!paused || doupdate)
        {
            doupdate = false;

            float deltaTime = std::min(dtmax, clock.restart().asSeconds());
            box.update(deltaTime);

            draw(true, deltaTime);
        }
    }
}


void GameWindow::handle_events()
{
    sf::Event event;
    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(window));
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
                start_placement(pos);

            if (event.mouseButton.button == sf::Mouse::Right)
                remove_at(pos);
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
                end_placement(pos);
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code > sf::Keyboard::Num0 &&
                event.key.code <= sf::Keyboard::Num9)
                set_size(event.key.code - sf::Keyboard::Num0);

            switch (event.key.code)
            {
            case sf::Keyboard::BackSpace: remove_last(); break;
            case sf::Keyboard::Escape:    cancel_placement(); break;
            case sf::Keyboard::T:         change_type(); break;
            case sf::Keyboard::E:         toggle_elastic(); break;
            case sf::Keyboard::B:         toggle_borders(); break;
            case sf::Keyboard::K:         toggle_paused(); break;
            case sf::Keyboard::L:         update_once(); break;

            case sf::Keyboard::Space: accelerate(0.0f); break;
            case sf::Keyboard::Down:  accelerate(0.8f); break;
            case sf::Keyboard::Up:    accelerate(1.25f); break;

            case sf::Keyboard::Add:      add_gravity(10.0f); break;
            case sf::Keyboard::Subtract: add_gravity(-10.0f); break;

            default: break;
            }
        }
    }
}

void GameWindow::draw(bool clear, float deltaTime)
{
    // background
    if(clear)
        window.clear(sf::Color::Black);


    // balls
    for (Ball &b : box.balls)
    {
        sf::CircleShape c(b.r);
        c.setPosition(b.pos.x - b.r, b.pos.y - b.r);
        c.setFillColor(b.color);
        window.draw(c);
    }


    // shadow ball
    if (pressed)
    {
        sf::CircleShape c(ballsize);
        c.setPosition(mousestart.x - ballsize, mousestart.y - ballsize);
        c.setFillColor(sf::Color(255, 255, 255, 75));
        window.draw(c);

        sf::Vertex line[]{
            sf::Vertex(sf::Vector2f(mousestart), sf::Color(255, 255, 255, 75)),
            sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(window)), sf::Color(255, 255, 255, 75))};
        window.draw(line, 2, sf::Lines);
    }


    // status text
    std::stringstream ss;
    ss.precision(0);
    ss << std::fixed
       << "ballcount " << box.balls.size()
       << "   ballsize[1-9] " << ballsize
       << "   [t]ype " << balltype
       << "   gravity[+/-] " << box.gravity
       << "   [e]lastic " << box.elastic
       << "   [b]orders " << box.borders
       << "   paused[k] " << paused
       << "   fps " << 1.0f / deltaTime;
    sf::Font font;
    font.loadFromFile("Lucida Console Regular.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(17);
    text.setFillColor(sf::Color::White);
    text.setString(ss.str());
    window.draw(text);

    window.display();
}


sf::Color GameWindow::get_ballcolor()
{
    int c = 255 - ballsize * 2;
    sf::Color r;
    switch (balltype)
    {
        case 0: r = sf::Color(0, c, 0); break;
        case 1: r = sf::Color(c, 0, 0); break;
        case 2: r = sf::Color(0, 0, c); break;
        case 3: r = sf::Color(c, 0, c); break;
    }

    return r;
}

void GameWindow::start_placement(sf::Vector2f pos)
{
    if((int)box.balls.size() >= maxballcount)
        return;
    mousestart = pos;
    pressed = true;
}


void GameWindow::end_placement(sf::Vector2f pos)
{
    if(!pressed)
        return;
    pressed = false;

    sf::Color ballcolor = get_ballcolor();
    box.balls.push_back(Ball(
        mousestart, speedmultiplier * (pos - mousestart),
        ballsize, balltype, ballcolor));
}


void GameWindow::remove_at(sf::Vector2f pos)
{
    for(int i = 0; i < (int)box.balls.size(); ++i)
    {
        if(vec::size(box.balls[i].pos - pos) < box.balls[i].r)
        {
            box.balls.erase(box.balls.begin() + i);
            break;
        }
    }
}


void GameWindow::set_size(int size)
{
    ballsize = size * 10.0f;
}


void GameWindow::remove_last()
{
    if(box.balls.size())
        box.balls.pop_back();
}


void GameWindow::cancel_placement()
{
    pressed = false;
}

void GameWindow::change_type()
{
    balltype = (balltype + 1) % 4;
}


void GameWindow::toggle_elastic()
{
    box.elastic = !box.elastic;
}


void GameWindow::toggle_borders()
{
    box.borders = !box.borders;
}


void GameWindow::toggle_paused()
{
    paused = !paused;
}


void GameWindow::update_once()
{
    doupdate = true;
}

void GameWindow::accelerate(float factor)
{
    for (Ball &b : box.balls)
        b.v *= factor;
}


void GameWindow::add_gravity(float delta)
{
    box.gravity += delta;
}





