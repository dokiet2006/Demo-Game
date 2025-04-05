
#include "Text.h"

Text::Text() : font_(nullptr) {}

Text::~Text() {
    if (font_) {
        TTF_CloseFont(font_);
        font_ = nullptr;
    }
}

bool Text::LoadFont(std::string path, int size) {
    font_ = TTF_OpenFont(path.c_str(), size);
    if (font_ == nullptr) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    return true;
}

void Text::RenderText(SDL_Renderer* renderer, std::string text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font_, text.c_str(), color);
    if (surface == nullptr) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect renderQuad = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

