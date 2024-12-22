#include "Controller.h"

Uint32 lastTime = SDL_GetTicks();
float deltaTime = 0.0f;


Controller::Controller() : m_window("DontStopMoving", 800, 600), m_player(370, 270, 60, 60, "DontStopMoving/Src/Assets/Images/boarder2.png",m_window.GetRenderer()),
 m_backgroundFirst(0,0,800,600,"DontStopMoving/Src/Assets/Images/road.jpg",m_window.GetRenderer()), m_backgroundSecond(800, 0, 800, 600, "DontStopMoving/Src/Assets/Images/road.jpg", m_window.GetRenderer()),
    /*m_rock(500, 200, 30, 30, "Src/Assets/Images/rock.png", m_window.GetRenderer()),*/ m_banana(-100, -100, 35, 35, "DontStopMoving/Src/Assets/Images/banana.png", m_window.GetRenderer()),
    m_lego(900, 400, 55, 55, "DontStopMoving/Src/Assets/Images/lego.png", m_window.GetRenderer()),
    m_arrow(390, 700, 20, 70, "DontStopMoving/Src/Assets/Images/arrow.png", m_window.GetRenderer()),
    m_arrowHead(-100, 100, 70, 70, "DontStopMoving/Src/Assets/Images/ArrowHead.png", m_window.GetRenderer()),
    m_frisbee(360, 30, 80, 80, "DontStopMoving/Src/Assets/Images/frisbee.png", m_window.GetRenderer()),
    m_shuriken(865, -130, 65, 65, "DontStopMoving/Src/Assets/Images/shuriken.png", m_window.GetRenderer()),
    m_wasd(150, 200, 200, 200, "DontStopMoving/Src/Assets/Images/wasd.png", m_window.GetRenderer()),
    m_escape(500, 200, 200, 200, "DontStopMoving/Src/Assets/Images/escape.png", m_window.GetRenderer()),
    m_title(m_window.GetRenderer()),
    m_exitAbout(m_window.GetRenderer()),
    m_score(m_window.GetRenderer()),
    m_endScore(m_window.GetRenderer()),
    m_replay(m_window.GetRenderer())

      
{
    m_title.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", 70);
    m_score.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", 30);
    m_endScore.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", 40);
    SetEndScreenText();

    
    

    SDL_SetRenderDrawBlendMode(m_window.GetRenderer(), SDL_BLENDMODE_BLEND);

    

    

    m_window.SetStopMovement(true);
    m_window.SetState(0);
    std::jthread t1(&Controller::Run, this);
    Events();
    
}

Controller::~Controller()
{
    SDL_Quit();
}

void Controller::Run()
{
    while (m_window.GetIsOpen())
    {
        if (m_window.GetState() == GameState::Start)
        {                     
            m_window.Set();
            m_backgroundFirst.DrawImage(m_window.GetRenderer());
            //m_backgroundSecond.DrawImage(m_window.GetRenderer());
            m_title.renderText("Faster Quicker", 130, 60, 255, 0, 0, 255);
            m_window.RenderText();
            
            

            m_window.Present();


        }

        if (m_window.GetState() == GameState::Play)
        {
            if (m_window.GetResetPlayerPos())
            {
                ResetObstacles();
                m_player.SetPos(370, 270);
                m_window.SetResetPlayerPos(false);
            }
            m_window.Set();
            m_backgroundFirst.DrawImage(m_window.GetRenderer());
            m_backgroundSecond.DrawImage(m_window.GetRenderer());
            m_player.DrawImage(m_window.GetRenderer());

            //m_rock.DrawImage(m_window.GetRenderer());
            m_banana.DrawImage(m_window.GetRenderer());
            m_lego.DrawImage(m_window.GetRenderer());
            m_arrow.DrawImage(m_window.GetRenderer());
            m_arrowHead.DrawImage(m_window.GetRenderer());
            m_frisbee.DrawImage(m_window.GetRenderer());
            m_shuriken.DrawImage(m_window.GetRenderer());

            m_score.renderText("SCORE " + std::to_string(m_playerScore), 600, 10, 255, 0, 0, 255);

            m_playerScore++;

            m_window.Present();
            ScrollBackground();
            MoveObstacles();
            DetectHits();
        }

        if (m_window.GetState() == GameState::About)
        {
            m_window.Set();
            m_backgroundFirst.DrawImage(m_window.GetRenderer());
            m_title.renderText("Controls", 250, 60, 255, 0, 0, 255);
            m_wasd.DrawImage(m_window.GetRenderer());
            m_escape.DrawImage(m_window.GetRenderer());
            m_exitAbout.renderText("EXIT", 382, 470, 255, 0, 0, 255);


            m_window.Present();
        }

        if (m_window.GetState() == GameState::End)
        {
            if (m_window.GetSetText())
            {
                SetEndScreenText();
                m_window.SetText(false);
            }

            m_window.Set();
            m_backgroundFirst.DrawImage(m_window.GetRenderer());
            m_title.renderText("YOU SURVIVED", 150, 60, 255, 0, 0, 255);
            m_endScore.renderText("With a Score of " + std::to_string(m_playerScore), 215, 220, 255, 0, 0, 255);
            m_exitAbout.renderText("EXIT", 382, 470, 255, 0, 0, 255);
            m_replay.renderText("REPLAY", 382, 410, 255, 0, 0, 255);


            m_window.Present();
        }
    }
}

void Controller::Events()
{
    m_window.Events(m_player);
}

void Controller::ScrollBackground()
{
    m_backgroundFirst.MovePositionX(-5);
    m_backgroundSecond.MovePositionX(-5);

    if (m_backgroundFirst.GetPosX() < -800)
    {
        m_backgroundFirst.MovePositionX(1600);
    }
    if (m_backgroundSecond.GetPosX() < -800)
    {
        m_backgroundSecond.MovePositionX(1600);
    }
}

void Controller::MoveObstacles()
{
    Uint32 currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 100.0f;
    lastTime = currentTime;

    m_counter += deltaTime * 5;

    m_arrow.MovePositionY(-5);

    if (m_arrow.GetPosY() < -70)
    {
        m_arrow.SetPosX(m_player.GetPosX());
        m_arrow.MovePositionY(700);
    }

    m_arrowHead.MovePositionX(5);

    if (m_arrowHead.GetPosX() > 900)
        m_arrowHead.SetPosX(-100);

    
    if (m_counter > 500)
    {
        int x = GenerateNumber(50, 750);
        int y = GenerateNumber(50, 550);
        m_banana.SetPosX(x);
        m_banana.SetPosY(y);
        m_counter = 0;
    }

    m_shuriken.MovePositionY(5);
    m_shuriken.MovePositionX(-5);
      
    if (m_shuriken.GetPosY() > 700)
    {
        if (m_shurikenPosCounter > -910 && !m_swapShuriken)
            m_shurikenPosCounter -= 65;
        else
            m_swapShuriken = true;
        if (m_swapShuriken && m_shurikenPosCounter < 715)
            m_shurikenPosCounter += 65;
        else
            m_swapShuriken = false;
        m_shuriken.SetPosY(-130);
        m_shuriken.SetPosX(865 + m_shurikenPosCounter);
        
    }

    m_frisbee.MovePositionY(m_frisbeeY);
    m_frisbee.MovePositionX(m_frisbeeX);

    if (m_frisbee.GetPosX() < 0)
        m_frisbeeX = 5;

    if (m_frisbee.GetPosX() > 720)
        m_frisbeeX = -5;

    if (m_frisbee.GetPosY() < 0)
        m_frisbeeY = 5;

    if (m_frisbee.GetPosY() > 520)
        m_frisbeeY = -5;

    m_lego.MovePositionX(-5);

    if (m_lego.GetPosX() < -100)
        m_lego.SetPosX(900);

    //m_rock.moveRectInCircle(*m_rock.GetRect(), 400, 300, 250.0f, m_angle, 25.0f);
}

void Controller::DetectHits()
{
    if (m_player.RectsOverlap(*m_player.GetRect(),*m_arrow.GetRect()))
    {
        m_player.SetPosX(-200);
        m_player.SetPosY(-200);
        m_window.SetStopMovement(true);
        m_window.SetState(2);
        m_window.SetEndScreen(true);
        m_backgroundFirst.SetPos(0, 0);
    }
    if (m_player.RectsOverlap(*m_player.GetRect(), *m_banana.GetRect()))
    {
        m_player.SetPosX(-200);
        m_player.SetPosY(-200);
        m_window.SetStopMovement(true);
        m_window.SetState(2);
        m_window.SetEndScreen(true);
        m_backgroundFirst.SetPos(0, 0);
    }
    if (m_player.RectsOverlap(*m_player.GetRect(), *m_lego.GetRect()))
    {
        m_player.SetPosX(-200);
        m_player.SetPosY(-200);
        m_window.SetStopMovement(true);
        m_window.SetState(2);
        m_window.SetEndScreen(true);
        m_backgroundFirst.SetPos(0, 0);
    }
    if (m_player.RectsOverlap(*m_player.GetRect(), *m_arrowHead.GetRect()))
    {
        m_player.SetPosX(-200);
        m_player.SetPosY(-200);
        m_window.SetStopMovement(true);
        m_window.SetState(2);
        m_window.SetEndScreen(true);
        m_backgroundFirst.SetPos(0, 0);
    }
    if (m_player.RectsOverlap(*m_player.GetRect(), *m_frisbee.GetRect()))
    {
        m_player.SetPosX(-200);
        m_player.SetPosY(-200);
        m_window.SetStopMovement(true);
        m_window.SetState(2);
        m_window.SetEndScreen(true);
        m_backgroundFirst.SetPos(0, 0);
    }
    if (m_player.RectsOverlap(*m_player.GetRect(), *m_shuriken.GetRect()))
    {
        m_player.SetPosX(-200);
        m_player.SetPosY(-200);
        m_window.SetStopMovement(true);
        m_window.SetState(2);
        m_window.SetEndScreen(true);
        m_backgroundFirst.SetPos(0, 0);
    }

    if (m_player.GetPosX() < 10)
        m_player.SetPosX(10);
    if (m_player.GetPosY() < 10)
        m_player.SetPosY(10);
    if (m_player.GetPosX() > 730)
        m_player.SetPosX(730);
    if (m_player.GetPosY() > 530)
        m_player.SetPosY(530);

    

}

void Controller::SetEndScreenText()
{
    m_exitAbout.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", m_window.GetNormalTextSize());
    m_exitAbout.setTextAlignment(true);
    m_replay.loadFont("DontStopMoving/Src/Assets/Fonts/Star Vintage.ttf", m_window.GetChoiceTextSize());
    m_replay.setTextAlignment(true);
}

void Controller::ResetObstacles()
{
    m_lego.SetPos(900,400);
    m_arrow.SetPos(360, 700);
    m_arrowHead.SetPos(-100, 100);
    m_frisbee.SetPos(360, 30);
    m_shuriken.SetPos(865, -130);
    m_banana.SetPos(-100, -100);
    m_backgroundSecond.SetPos(800, 0);
    m_playerScore = 0;
}

int Controller::GenerateNumber(const int min,const int max)
{
    std::random_device rd;                        // Seed for random number engine
    std::mt19937 generator(rd());                 // Mersenne Twister engine
    std::uniform_int_distribution<int> dist(min, max); // Uniform distribution over [min, max]
    return dist(generator);
}
