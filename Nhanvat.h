#ifndef NHAN_VAT_H
#define NHAN_VAT_H

#include <vector>
#include "Function.h"
#include "Object.h"
#include "Explosion.h"
#include "Music.h"
#include "Map.h"

#define ROI_SPEED 4
#define ROI_MAX 10
#define PLAYER_SPEED 10
#define PLAYER_JUMP_VAL 40

class Explosion;
class Nhanvat : public Object
{
public:
    Nhanvat();
    ~Nhanvat();

    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
    };

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen, Music& music);
    void set_clips();

    void DoPlayer(Map& map_data, Explosion& explosion, Music& music);
    void CheckMap(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }
    void CenterEntityOnMap(Map& map_data);

    bool IsDead(const Map& map_data) const ;
    bool IsDeadByExplosion(const Explosion& explosion) const;

    void Reset(const Map& map_data);
    int GetPos() const { return x_pos_;}

private:
    float x_val;
    float y_val;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[8];
    Input input_type_;
    int frame_;
    int status_;
    bool on_ground;

    int map_x_;
    int map_y_;
};

#endif // NHAN_VAT_H
