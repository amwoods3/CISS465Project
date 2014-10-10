#include "Bomber.h"

Bomber::Bomber(std::string image_file, Screen & s)
    : animation(NULL), img(Image(image_file, s))
{
    active_time = SDL_GetTicks();
    horizontal = 0;
    vertical = 0;
    frame = 0;
    speed = 140;
    pos[0] = 100;
    pos[1] = 100;
    int x = 2;
    int y = 1;
    int w = 18;
    int h = 29;
    for (int i = 0; i < 6; ++i)
    {
        SDL_Rect a = {x, y, w, h};
        walk_down.push_back(a);
        if (i % 2 == 0) x += 18;
        else x += 19;
    }
    for (int i = 0; i < 6; ++i)
    {
        SDL_Rect a = {x, y, w, h};
        walk_right.push_back(a);
        if (i % 2 == 0) x += 17;
        else x += 17;
    }
    x = 2;
    y = 31;
    for (int i = 0; i < 6; ++i)
    {
        SDL_Rect a = {x, y, w, h};
        walk_up.push_back(a);
        if (i % 2 == 0) x += 18;
        else x += 19;
    }
    for (int i = 0; i < 6; ++i)
    {
        SDL_Rect a = {x, y, w, h};
        walk_left.push_back(a);
        if (i % 2 == 0) x += 17;
        else x += 17;
    }
    animation = &walk_down;
}


void Bomber::draw(Screen & s)
{
    SDL_Rect p;
    p.x = pos[0];
    p.y = pos[1];
    p.w = (*animation)[frame].w;
    p.h = (*animation)[frame].h;
    img.draw(s, &(*animation)[frame], &p);
}


void Bomber::set_animation(int i)
{
    if (i == 0) animation = &walk_down;
    else if (i == 1) animation = &walk_right;
    else if (i == 2) animation = &walk_up;
    else if (i == 3) animation = &walk_left;
}


void Bomber::reset_frame(int amount, int frames)
{
    if (amount==-1)frame = 0;
    frame = amount % frames;
}


void Bomber::inc_frame()
{
    Uint32 temp = SDL_GetTicks();
    if (temp - frame_timer > 100)
    {
        frame += (temp - frame_timer) / 100;
        frame_timer = temp;
    }
    if (frame >= animation->size())
        reset_frame(frame,animation->size());
}


void Bomber::update()
{
    if (!is_active())
    {
        frame = 0;
        frame_timer = SDL_GetTicks();
        travel_time = SDL_GetTicks();
    }
    else
    {
        if (SDL_GetTicks() - travel_time > 10)
        {
            travel_time = SDL_GetTicks();
            pos[1] += vertical;
            pos[0] += horizontal;
            horizontal = vertical = 0;
        }
    }
}


bool Bomber::is_active()
{
    return (SDL_GetTicks() - active_time < 100);
}


int Bomber::get_travel_distance() const
{
    Uint32 now = SDL_GetTicks();
    return speed * (now - travel_time) / 1000;
}


void Bomber::move_up()
{
    vertical = -get_travel_distance();
    active_time = SDL_GetTicks();
}


void Bomber::move_down()
{
    vertical = get_travel_distance();
    active_time = SDL_GetTicks();
}


void Bomber::move_left()
{
    horizontal = -get_travel_distance();
    active_time = SDL_GetTicks();
}


void Bomber::move_right()
{
    horizontal = get_travel_distance();
    active_time = SDL_GetTicks();
}