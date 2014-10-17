#ifndef BOMBER_H
#define BOMBER_H

#include "includes.h"
#include <cmath>
#include "vec2d.h"
#include "constants.h"
#include "Screen.h"
#include "Image.h"
#include "includes.h"
#include "Stage.h"



class Bomb
{
public:
    Bomb(int x=0, int y=0, Uint32 fuse=-1)
        : time(SDL_GetTicks()), power(2),
          alive(true), fuse_length(fuse),
          time_left(fuse), explosion_time(0),
          exp_remaining(-1)
    {pos[0] = x; pos[1] = y;}
    
    
    Uint32 tick()
    {
        if (fuse_length == -1) return 1000;
        time_left = (int) fuse_length - (int) (SDL_GetTicks() - time);
        if (time_left < 0)
        {
            explode();
        }
        return time_left;
    }

    void set_time_left(Uint32 l) {time_left = l;}

    void update()
    {
        if (time_left < 0)
        {
            explode();
            exp_remaining = SDL_GetTicks() - explosion_time;
        }
    }

    int get_time_left()
    {
        return time_left;
    }

    int exp_time() {if (time_left > 0) return -1; if (exp_remaining != -1) return exp_remaining; return SDL_GetTicks() - explosion_time;}

    //implement explosion
    void explode();
    vec2d get_pos() {return pos;}
    int draw(Screen & s, Image & to_draw);
    void set_x(int _x) {pos[0] = _x;}
    void set_y(int _y) {pos[1] = _y;}
    void set_exp(int e) {explosion_time = e;}
    bool is_alive() {return alive;}
    bool is_exploding() {return (explosion_time > 0);}
private:
    vec2d pos;
    Uint32 time;
    Image img;
    int time_left;
    Uint32 fuse_length;
    bool alive;
    int power;
    Uint32 explosion_time;
    Uint32 exp_remaining;
    int frame;
    SDL_Rect exp_rect;
};

class Bomber
{
public:
    Bomber(const std::string & image_file, const std::string & bomb_name, const std::string & explosion_name, Screen & s);
    Bomber();
    int draw(Screen & s);
    void set_animation(int i = 0);
    void reset_frame(int amount=-1, int frames=5);
    void inc_frame();
    void update();
    SDL_Rect get_rect();
    bool is_active();
    bool is_alive() {return alive;}
    void reposition(const Stage & s, int coll);
    int get_travel_distance() const;
    void move_up();
    void move_down();
    void move_left();
    void move_right();
    void print_pos() {std::cout << "<" << ' '
                                << pos[0] << ',' << pos[1]
                                << ">" << std::endl;}
    void set_pos(int x, int y) { pos[0] = x; pos[1] = y; }
    void set_frame(int f) {frame = f;}
    std::string send_info(const std::string & name);
    void set(const std::string & info);
    void drop_bomb();
    void stop();
    int get_direction() {return direction;}
    int get_speed() {return speed;}
    void new_image(const std::string & file_name,
                   const std::string & bomb_name, const std::string & explosion_name, Screen & s)
    {
        img.get_new_texture(file_name, s);
        bomb_img.get_new_texture(bomb_name, s);
        exp_img.get_new_texture(explosion_name, s);
    }
    SDL_Texture * get_img() {return img.get_texture();}
    
private:
    std::vector<SDL_Rect> walk_down;
    std::vector<SDL_Rect> walk_right;
    std::vector<SDL_Rect> walk_up;
    std::vector<SDL_Rect> walk_left;
    int speed; // pixels per second
    int frame;
    int direction;
    Uint32 travel_time;
    Uint32 active_time;
    int vertical;
    int horizontal;
    Uint32 frame_timer;
    std::vector<SDL_Rect> * animation;
    std::vector<Bomb> active_bomb;
    Image bomb_img;
    Image exp_img;
    Image img;
    vec2d pos;
    int bombtype;
    bool alive;
    int health;
    int lives;
    
};

#endif
