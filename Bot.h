#ifndef BOT_H_
#define BOT_H_

#include "Function.h"
#include "Object.h"

#define BOT_FRAME_NUM 8
#define LIST_BOTS 30
#define BOT_SPEED 8

class Bot : public Object
{
public:
    Bot();
    ~Bot();

    enum TypeMove
    {
        STATIC_BOT = 0,
        DISTANCE = 1,
    };

    void set_x_val(const int xVal) {x_val_ = xVal;}
    void set_y_val(const int yVal) {y_val_ = yVal;}

    void set_x_pos(const float& xp) {x_pos_ = xp;}
    void set_y_pos(const float& yp) {y_pos_ = yp;}

    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}
    void SetMapXY (const int& mp_x, const int& mp_y) {map_x_ = mp_x; map_y_ = mp_y;}

    void set_clips();
    bool LoadImg (std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}
    void DoPlayer(Map& gMap,SDL_Renderer* screen);
    void CheckMap(Map& gMap,SDL_Renderer* screen);

    void set_type_move(const int& typeMove) {type_move_ = typeMove;}
    void SetAnimation (const int& pos_a, const int& pos_b) {animation_a_ = pos_a; animation_b_ = pos_b;}
    void input_left(const int& ipLeft) {input_type_.left_ = ipLeft;}
    void ImpMoveType(SDL_Renderer* screen);
    void InitBots();
private:

    int map_x_;
    int map_y_;
    float x_val_;
    float y_val_;
    float x_pos_;
    float y_pos_;
    bool on_ground_;
    int frame_;
    SDL_Rect frame_clip_[BOT_FRAME_NUM];
    int width_frame_;
    int height_frame_;

    int type_move_;
    int animation_a_;
    int animation_b_;
    Input input_type_;
};


#endif // BOT_H
