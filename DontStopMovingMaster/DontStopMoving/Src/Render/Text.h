#pragma once
//other libraries
#include <SDL.h>
#include <SDL_ttf.h>
//standard libraries 
#include <string>
#include <iostream>

class Text 
{
public:
    // Constructor and Destructor
    Text() = default;

    Text(SDL_Renderer* renderer);
    ~Text();

    // Load a font with a specified size
    bool loadFont(const std::string& fontPath, int fontSize);

    // Render text at a given position with a specified color
    void renderText(const std::string& text, int x, int y, const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& a);

    // Setters for adjusting text alignment and style
    void setFontSize(int fontSize);
    void setTextAlignment(bool centered);

private:
    SDL_Renderer* mRenderer;
    TTF_Font* mFont;
    bool isCentered;

    // Internal method to cleanup resources
    void cleanUp();
};

