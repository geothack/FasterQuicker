#include "Window.h"

Window::Window(const char* title, int width, int height) : m_window(nullptr), m_renderer(nullptr), m_open(true)


{   
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        HandleSDLError("SDL_Init");
        m_open = false;
        return;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) 
    {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Create SDL Window
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!m_window) 
    {
        HandleSDLError("SDL_CreateWindow");
        m_open = false;
        return;
    }

    // Create SDL Renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer) 
    {
        HandleSDLError("SDL_CreateRenderer");
        m_open = false;
    }

    m_play = Text(m_renderer);
    m_exit = Text(m_renderer);
    m_about = Text(m_renderer);

    SetText(m_textIndex);

    m_sounds.LoadSound("ping", "DontStopMoving/Src/Assets/Sounds/ping.wav");
    m_sounds.LoadSound("main", "DontStopMoving/Src/Assets/Sounds/fight.wav");
}

Window::~Window()
{
    if (m_renderer) 
        SDL_DestroyRenderer(m_renderer);
    if (m_window) 
        SDL_DestroyWindow(m_window);

    SDL_Quit();
}

void Window::Events(Rectangle &player)
{
    SDL_Event event;
    while (SDL_WaitEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            m_open = false;
            break;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                m_sounds.PlaySound("ping");
                m_open = false;
                break;
            }


            if (event.key.keysym.sym == SDLK_RETURN && m_returnToMenu)
            {
                m_sounds.PlaySound("ping");
                m_gameStates = GameState::Start;
                m_returnToMenu = false;
                goto back;
            }

            if (event.key.keysym.sym == SDLK_RETURN && m_textIndex == 0 && !m_endScreen)
            {
                m_stopPlayerMovement = false;
                m_gameStates = GameState::Play;   
                m_sounds.PlaySound("ping");
                m_sounds.PlaySound("main");
            }
            if (event.key.keysym.sym == SDLK_RETURN && m_textIndex == 1)
            {
                m_gameStates = GameState::About;
                m_returnToMenu = true;
                m_sounds.PlaySound("ping");
            }
            if (event.key.keysym.sym == SDLK_RETURN && m_textIndex == 2)
            {
                m_sounds.PlaySound("ping");
                m_open = false;
                break;
            }
            
        }

        back:

        if (event.type == SDL_KEYDOWN && m_stopPlayerMovement && m_returnToMenu == false && !m_endScreen)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                m_textIndex--;
                if(m_textIndex > -1)
                    SetText(m_textIndex);
                else
                {
                    m_textIndex = 0;
                }
                m_sounds.PlaySound("ping");
                break;
            case SDLK_s:
                m_textIndex++;
                if(m_textIndex < 3)
                    SetText(m_textIndex);
                else
                {
                    m_textIndex = 2;
                }
                m_sounds.PlaySound("ping");
                break;

            


            }
        }


        if (event.type == SDL_KEYDOWN && !m_stopPlayerMovement)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_w:               
                player.MovePositionY(-8);               
                break;
            case SDLK_a:
                player.MovePositionX(-8);
                break;
            case SDLK_s:
                player.MovePositionY(8);
                break;
            case SDLK_d:
                player.MovePositionX(8);
                break;

            }
        }

        if (event.type == SDL_KEYDOWN && m_gameStates == GameState::End)
        {
            if (event.key.keysym.sym == SDLK_RETURN && m_normalSize == 36)
            {
                m_sounds.PlaySound("ping");
                m_stopPlayerMovement = false;
                m_resetPlayer = true;
                m_gameStates = GameState::Play;               
            }
            else if (event.key.keysym.sym == SDLK_RETURN && m_normalSize == 56)
            {
                m_sounds.PlaySound("ping");
                m_open = false;
                break;
            }

            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                if (m_normalSize = 36)
                {
                    m_normalSize = 56;
                    m_choiceSize = 36;
                }
                else
                {
                    m_normalSize = 36;
                    m_choiceSize = 56;
                }
                m_setText = true;
                m_sounds.PlaySound("ping");
                break;
            case SDLK_s:
                if (m_normalSize = 56)
                {
                    m_normalSize = 36;
                    m_choiceSize = 56;
                }
                else
                {
                    m_normalSize = 56;
                    m_choiceSize = 36;
                }
                m_setText = true;
                m_sounds.PlaySound("ping");
                break;
            

            }
        }
        
        

        

       

    }
}

void Window::Set()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // Set background color to black
    SDL_RenderClear(m_renderer);
}

void Window::Present()
{
    SDL_RenderPresent(m_renderer); // Present the renderer
}

void Window::RenderText()
{
    m_play.renderText("PLAY", 385, 250, 255, 0, 0, 255);
    m_about.renderText("ABOUT", 382, 310, 255, 0, 0, 255);
    m_exit.renderText("EXIT", 382, 370, 255, 0, 0, 255);
}

void Window::SetState(int index)
{
    switch (index)
    {
    case 0:
        m_gameStates = GameState::Start;
        break;
    case 1:
        m_gameStates = GameState::Play;
        break;
    case 2:
        m_gameStates = GameState::End;
        break;

    default:
        std::cout << "Unknown Index for setting gamestate.\n";
        break;


    }
}

void Window::SetText(int index)
{
    switch (index)
    {
    case 0:
        m_play.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", 56);
        m_play.setTextAlignment(true);
        m_about.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", 36);
        m_about.setTextAlignment(true);
        m_exit.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", 36);
        m_exit.setTextAlignment(true);
        break;

    case 1:
        m_play.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", 36);
        m_play.setTextAlignment(true);
        m_about.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", 56);
        m_about.setTextAlignment(true);
        m_exit.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", 36);
        m_exit.setTextAlignment(true);
        break;

    case 2:
        m_play.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", 36);
        m_play.setTextAlignment(true);
        m_about.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", 36);
        m_about.setTextAlignment(true);
        m_exit.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", 56);
        m_exit.setTextAlignment(true);
        break;

    default:
        std::cout << "Unknown index for setting text.\n";
        break;
    }
}

void Window::HandleSDLError(const std::string& message)
{
    std::cerr << message << " Error: " << SDL_GetError() << std::endl;
}

