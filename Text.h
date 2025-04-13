#ifndef TEXT_H
#define TEXT_H

#include "Function.h"
#include <string>
#include <SDL_ttf.h>

class Text
{
public:
    Text();
    ~Text();

    bool LoadFont(std::string path, int size);
    void RenderText(SDL_Renderer* renderer, std::string text, int x, int y, SDL_Color color);

private:
    TTF_Font* font_;
};

#endif // TEXT_H
