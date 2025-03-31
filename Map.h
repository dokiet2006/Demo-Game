#ifndef MAP_H_
#define MAP_H_

#include "Function.h"
#include "Object.h"

#define MAX_TILE 15

class TileMat : public Object
{
public:
    TileMat() {;}
    ~TileMat() {;}
};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap (SDL_Renderer* screen);
    Map getMap() const {return game_map_;};
    void setMap (Map& map_data) {game_map_ = map_data;};
private:
    Map game_map_;
    TileMat tile_mat[MAX_TILE];

};

#endif // MAP_H_

