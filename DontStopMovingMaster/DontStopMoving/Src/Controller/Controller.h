#pragma once

//standard libraries
#include <thread>
#include <random>

//created classes 
#include "Render/Window.h"
#include "Math/Rectangle.h"
#include "Render/Text.h"

class Controller
{
public:
	Controller();
	~Controller();

	void Run();

private:
	void Events();
	void ScrollBackground();
	void MoveObstacles();
	void DetectHits();

	void SetEndScreenText();
	void ResetObstacles();


private:
	int GenerateNumber(const int min,const int max);

private:
	Window m_window;
	
	Rectangle m_player;

	Rectangle m_backgroundFirst;
	Rectangle m_backgroundSecond;

	//Rectangle m_rock;
	Rectangle m_banana;
	Rectangle m_lego;
	Rectangle m_arrow;
	Rectangle m_arrowHead;
	Rectangle m_frisbee;
	Rectangle m_shuriken;
	Rectangle m_wasd;
	Rectangle m_escape;

	

	Text m_title;
	Text m_exitAbout;
	Text m_score;
	Text m_endScore;
	Text m_replay;

	


	SDL_Color m_menuRectColour;

private:
	float m_counter;
	int m_shurikenPosCounter = 0;
	bool m_swapShuriken;

	int m_frisbeeX = -5;
	int m_frisbeeY = 5;

	float m_angle = 45.0f;

	int m_playerScore = 0;


private:
	

};

