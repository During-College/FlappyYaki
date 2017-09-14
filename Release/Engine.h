/*
Created by Matthew Hwang
Last Updated: 9/14/2017
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Yaki.h"
#include "Pipe.h"

using namespace sf;
using namespace std;

// Self made engine that controls everything about the game
class Engine {

	// Constants
	const int WIDTH = 800;
	const int HEIGHT = 300;
	const int MARGIN = 10;
	const int MAX_VOLUME = 20;
	const int TITLE_COLOR_R = 160;
	const int TITLE_COLOR_G = 185;
	const int TITLE_COLOR_B = 255;

private:
	RenderWindow m_Window;
	Font m_Font;

	// Background
	Texture m_BackgroundTexture;
	Sprite m_BackgroundSprite1;
	Sprite m_BackgroundSprite2;

	// The character
	Yaki m_Yaki;

	// Audio control UI
	Texture m_MusicOnTexture;
	Texture m_MusicOffTexture;
	Sprite m_MusicButton;
	Text m_MusicLevel;
	Text m_MusicLevelLeft;
	Text m_MusicLevelRight;

	// Title Screen
	Color m_TitleColor = Color::Color(TITLE_COLOR_R, TITLE_COLOR_G, TITLE_COLOR_B, 255);
	Color m_OutlineColor = Color::Color(0, 0, 0, 255);
	Color m_FillColor = Color::Color(255, 255, 255, 255);
	Text m_Title1;
	Text m_Title2;
	Text m_HighestScoreText;
	Text m_CurrentScoreText;
	Text m_Instructions;

	// All music and sound effects that is to be played
	Music m_BackgroundMusic;
	Music m_StartSound;
	Music m_VolumeChange;
	Music m_HitSound;
	Music m_PointSound;
	Music m_DefeatSound;
	Music m_Wait;

	// Booleans
	bool m_GameStarted;
	bool m_ShowInstructions;
	bool m_InAnimation;
	bool m_Muted;
	bool m_ColorUp;
	bool m_TransitionIn;
	bool m_TransitionOut;
	bool m_YakiEntering;

	// Integers
	int m_HighestScoreInt;
	int m_CurrentScoreInt;
	int m_InstructionsTimerMax;
	int m_InstructionsTimerCurrent;
	int m_Volume;

	// Array of the pipes. Leftmost pipe will cycle back to the right
	Pipe m_Pipes[5];

	// Methods that it pulls from other cpp files
	void input();
	void update();
	void draw();
	void defeat();
	void mouseInput(Event event);

public:
	// Engine constructor
	Engine();
	// Method that is called by main to start
	void start();

};