
#include "BallBox.h"


BallBox::BallBox(sf::Vector2f size)
    : size(size), gravity(50), elastic(true), borders(true)
{ }



void BallBox::update_gravity(float deltaTime)
{
    for (int i = 0; i < (int)balls.size(); ++i)
    {
        for (int j = i + 1; j < (int)balls.size(); ++j)
        {
            int x = (balls[i].type == balls[j].type ? 1 : -1);
            sf::Vector2f d = balls[j].pos - balls[i].pos;
            sf::Vector2f dm = d * (float)(deltaTime * x * gravity * balls[i].m * balls[j].m / pow(vec::size(d), 3));
            balls[i].v += dm / balls[i].m;
            balls[j].v += -dm / balls[j].m;
        }
    }
}

void BallBox::update_positions(float deltaTime)
{
    for(Ball &b : balls)
    {
        b.pos += b.v * deltaTime;
    }
}

void BallBox::update_collisions(float deltaTime)
{
    int nredos = 0;
    bool redo;
    auto prev = balls;
    do
    {
        ++nredos;
        redo = false;
        for (int i = 0; i < (int)balls.size(); ++i)
        {
            if(borders && border_collision(balls[i]))
                redo = true;
            for (int j = i + 1; j < (int)balls.size(); ++j)
                if (ball_collision(balls[i], balls[j]))
                    redo = true;
        }


    } while(redo && nredos <= maxcollisionredos);
}

bool BallBox::ball_collision(Ball &b1, Ball &b2)
{
    float sr = b1.r + b2.r;
    sf::Vector2f P = b1.pos - b2.pos;
    float overlap = sr - vec::size(P);
    if(overlap <= 0)
        return false;

    float sm = b1.m + b2.m;
    sf::Vector2f V = b1.v - b2.v;
    float V2 = vec::dot(V, V);
    int dir = vec::comp_size(b1.v, -P) + vec::comp_size(b2.v, P) > 0 ? 1 : -1;
    float deltaTime2 = (vec::dot(P, V) + dir * sqrt(V2 * sr * sr - pow(vec::dot(P, vec::ortho(V)), 2))) / V2;
    if (isnan(deltaTime2) || isinf(deltaTime2))
        deltaTime2 = 0;

    b1.pos -= b1.v * deltaTime2;
    b2.pos -= b2.v * deltaTime2;

    sf::Vector2f ci = vec::comp(b1.v, b2.pos - b1.pos);
    sf::Vector2f cj = vec::comp(b2.v, b1.pos - b2.pos);
    b1.v -= ci;
    b2.v -= cj;
    if (elastic)
    {
        b1.v += ((b1.m - b2.m) * ci + 2 * b2.m * cj) / sm;
        b2.v += ((b2.m - b1.m) * cj + 2 * b1.m * ci) / sm;
    }
    else
    {
        sf::Vector2f vc = (b1.m * ci + b2.m * cj) / sm;
        b1.v += vc;
        b2.v += vc;
    }

    b1.pos += b1.v * deltaTime2;
    b2.pos += b2.v * deltaTime2;

    return overlap > collisionredothresh;
}

bool BallBox::border_collision(Ball &i)
{

    sf::Vector2f corner1 = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f corner2 = sf::Vector2f(0.0f, size.y);
    sf::Vector2f corner3 = sf::Vector2f(size.x, 0.0f);
    sf::Vector2f corner4 = sf::Vector2f(size.x, size.y);

    bool r = false;
    r |= check_border(i, corner2, corner1 - corner2);
    r |= check_border(i, corner1, corner3 - corner1);
    r |= check_border(i, corner3, corner4 - corner3);
    r |= check_border(i, corner4, corner2 - corner4);

    return r;
}

bool BallBox::check_border(Ball &b, sf::Vector2f p, sf::Vector2f v)
{
    v = vec::norm(v);
    sf::Vector2f o = vec::ortho(v);
    sf::Vector2f vo = vec::comp(b.v, o);
    sf::Vector2f e = b.pos + o * b.r;
    sf::Vector2f ep = e - p;
    sf::Vector2f eo = ep - v * vec::dot(v, ep);

    if(vec::cross(v, ep) < 0)
    {
        if(elastic)
        {
            b.pos -= eo * 2.0f;
            b.v -= vo * 2.0f;
        }
        else
        {
            b.pos -= eo;
            b.v -= vo;
        }

        return true;
    }
    return false;
}

void BallBox::update(float deltaTime)
{
    update_gravity(deltaTime);
    update_positions(deltaTime);
    update_collisions(deltaTime);
}





