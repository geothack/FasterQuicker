#include "Text.h"

// Constructor
Text::Text(SDL_Renderer* renderer)
    : mRenderer(renderer), mFont(nullptr), isCentered(false) 
{
    if (TTF_Init() == -1) 
    {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
    }
}

// Destructor
Text::~Text() 
{
    //cleanUp();
    TTF_Quit();
}

// Load a font with the specified size
bool Text::loadFont(const std::string& fontPath, int fontSize) 
{
    cleanUp();
    mFont = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!mFont) 
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

// Render text at a specified position with color
void Text::renderText(const std::string& text, int x, int y, const unsigned char& r,const unsigned char& g,const unsigned char& b,const unsigned char& a) {
    if (!mFont) {
        std::cerr << "Font not loaded. Call loadFont() first." << std::endl;
        return;
    }

    // Create surface from the text
    SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text.c_str(), { r,g,b,a });
    if (!textSurface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }

    // Convert surface to texture
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    if (!textTexture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    // Get the dimensions of the text
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    // Clean up the surface
    SDL_FreeSurface(textSurface);

    // Calculate centered position if needed
    if (isCentered) {
        x -= textWidth / 2;
        y -= textHeight / 2;
    }

    // Define the destination rectangle for the texture
    SDL_Rect destRect = { x, y, textWidth, textHeight };

    // Render the texture to the screen
    SDL_RenderCopy(mRenderer, textTexture, nullptr, &destRect);

    // Cleanup
    SDL_DestroyTexture(textTexture);
}

// Set the font size by reloading the font
void Text::setFontSize(int fontSize) {
    if (mFont) {
        TTF_SetFontSize(mFont, fontSize);
    }
}

// Set text alignment
void Text::setTextAlignment(bool centered) {
    isCentered = centered;
}

// Clean up resources
void Text::cleanUp() {
    if (mFont) 
    {
        TTF_CloseFont(mFont);
        mFont = nullptr;
    }
}