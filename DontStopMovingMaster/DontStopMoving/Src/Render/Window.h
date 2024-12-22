#pragma once
//other libraries
#include <SDL.h>
#include <SDL_image.h>



//standard libraries
#include <iostream>

//created classes
#include "Math/Rectangle.h"
#include "Render/Text.h"
#include "Sounds/Sound.h"

enum class GameState
{
    Start,
    Play,
    About,
    End
};


class Window 
{
public:
    Window() = default;

    Window(const char* title, int width, int height);
    ~Window();
    
    void Events(Rectangle &player);

    void Set();
    void Present();
    
    void RenderText();

    void SetState(int index);
    void SetText(int index);


    inline bool GetIsOpen() const { return m_open; }
    


    inline bool SetIsOpen(bool value) { return m_open = value; } 
    inline bool SetStopMovement(bool value) { return m_stopPlayerMovement = value; }
    inline bool SetMenuActive(bool value) { return m_MenuActive = value; }

    inline SDL_Renderer* const GetRenderer() const { return m_renderer; }

    GameState GetState() { return m_gameStates; }
    
    inline int GetNormalTextSize() { return m_normalSize; }
    inline int GetChoiceTextSize() { return m_choiceSize; }

    inline bool GetSetText() { return m_setText; }
    inline bool SetText(bool value) { return m_setText = value; }

    inline bool GetResetPlayerPos() { return m_resetPlayer; }
    inline bool SetResetPlayerPos(bool value) { return m_resetPlayer = value; }

    inline bool SetEndScreen(bool value) { return m_endScreen = value; }
    
private:
    // Helper function to handle SDL initialization errors
    void HandleSDLError(const std::string& message);

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_open;
    bool m_stopPlayerMovement = false;
    bool m_MenuActive = false;

    
    GameState m_gameStates;

    Text m_play;
    Text m_about;
    Text m_exit;

    Sound m_sounds;


    int m_textIndex = 0;

    bool m_returnToMenu = false;
    bool m_setText = false;

    bool m_resetPlayer = false;
    bool m_endScreen = false;

    int m_choiceSize = 56;
    int m_normalSize = 36;
   
};

