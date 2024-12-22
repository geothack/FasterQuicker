#pragma once 
//other libraries
#include <SDL.h>
#include <SDL_image.h>

//standard libraries 
#include <cmath>


class Rectangle {
public:

    Rectangle()
    {

    }

    // Constructor to initialize the rectangle's position, dimensions, and color
    Rectangle(int x, int y, int width, int height, SDL_Color color) : m_rect{ x, y, width, height }, m_color(color)
    {

    }

    Rectangle(int x, int y, int width, int height, const std::string& imagePath, SDL_Renderer* renderer) : m_rect{ x, y, width, height }, m_texture(nullptr)
    {
        m_texture = loadTexture(imagePath, renderer);
        if (!m_texture) 
        {
            std::cerr << "Failed to load texture: " << imagePath << std::endl;
        }
    }

    // Sets the color of the rectangle
    void SetColor(SDL_Color color)
    {
        m_color = color;
    }

    bool SetTexture(const std::string& imagePath, SDL_Renderer* renderer)
    {
        if (m_texture) 
        {
            SDL_DestroyTexture(m_texture);
        }

        
        m_texture = loadTexture(imagePath, renderer);
        return m_texture != nullptr;
    }

    SDL_Texture* loadTexture(const std::string& imagePath, SDL_Renderer* renderer)
    {
        SDL_Texture* newTexture = IMG_LoadTexture(renderer, imagePath.c_str());
        if (!newTexture) 
        {
            std::cerr << "Failed to load texture from " << imagePath << ": " << IMG_GetError() << std::endl;
        }
        return newTexture;
    }


    // Draws the rectangle on the given renderer
    void DrawImage(SDL_Renderer* renderer) const
    {
        SDL_RenderCopy(renderer, m_texture, nullptr, &m_rect);
        
    }

    void DrawRect(SDL_Renderer* renderer) const
    {
        SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
        
        SDL_RenderFillRect(renderer, &m_rect);
    }

    // Set position of the rectangle
    void MovePositionX(int x)
    {
        m_rect.x += x;
        
    }

    void MovePositionY(int y)
    {
        m_rect.y += y;
        
    }

    inline const int SetPosX(int x) { return m_rect.x = x; }
    inline const int SetPosY(int y) { return m_rect.y = y; }

    inline const int GetPosX() const { return m_rect.x; }
    inline const int GetPosY() const { return m_rect.y; }
  

    SDL_Rect* GetRect() { return &m_rect; }

    // Set dimensions of the rectangle
    void SetSize(int width, int height)
    {
        m_rect.w = width;
        m_rect.h = height;
    }

    void SetPos(int x, int y)
    {
        m_rect.x = x;
        m_rect.y = y;
    }

    void MoveRectInCircle(SDL_Rect& rect, int centerX, int centerY, int radius, float& angle, float speed) {
        // Update the angle based on the speed
        angle += speed;

        // Keep angle within 0 to 2π range for simplicity
        if (angle > 2 * M_PI) {
            angle -= 2 * M_PI;
        }

        // Calculate new X and Y position based on angle
        rect.x = centerX + static_cast<int>(radius * cos(angle)) - rect.w / 2;
        rect.y = centerY + static_cast<int>(radius * sin(angle)) - rect.h / 2;
    }


    bool RectsOverlap(const SDL_Rect &rect1,const SDL_Rect &rect2)
    {
        if (rect1.x + rect1.w > rect2.x + rect2.w && rect1.y < rect2.y && rect1.x < rect2.x + rect2.w
            && rect1.y + rect1.h > rect2.y)
        {
            return true;
        }
        
        return false;
    }

    bool IsMouseInRect(const int mouseX,const int mouseY,const SDL_Rect &rect) const
    {
        if (mouseX >= rect.x && mouseX < (rect.x + rect.w) &&
            mouseY >= rect.y && mouseY < (rect.y + rect.h))
            return true;

        return false;
    }
    


private:
    SDL_Rect m_rect;    
    SDL_Color m_color;  

    SDL_Texture* m_texture;

};