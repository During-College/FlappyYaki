/*
Created by Matthew Hwang
Last Updated: 9/14/2017
*/

#include "Engine.h"

// Constructor that sets all variables
Engine::Engine() {
	// Creating window
	m_Window.create(VideoMode(WIDTH, HEIGHT), "Flappy Yaki", Style::Close);

	// Font
	m_Font.loadFromFile("SquareFont.ttf");

	// Background
	m_BackgroundTexture.loadFromFile("Images/Background.png");
	m_BackgroundSprite1.setTexture(m_BackgroundTexture);
	m_BackgroundSprite2.setTexture(m_BackgroundTexture);
	m_BackgroundSprite1.setPosition(Vector2f(0, 0));
	m_BackgroundSprite2.setPosition(Vector2f(WIDTH, 0));

	// Audio system UI
	m_MusicOnTexture.loadFromFile("Images/MusicOn.png");
	m_MusicOffTexture.loadFromFile("Images/MusicOff.png");
	m_MusicButton.setTexture(m_MusicOnTexture);
	m_MusicLevel.setFont(m_Font);
	m_MusicLevel.setCharacterSize(20);
	m_MusicLevel.setOutlineColor(m_OutlineColor);
	m_MusicLevel.setOutlineThickness(3);
	m_MusicLevel.setString(" | |     ");
	m_MusicLevelLeft.setFont(m_Font);
	m_MusicLevelRight.setFont(m_Font);
	m_MusicLevelLeft.setCharacterSize(20);
	m_MusicLevelRight.setCharacterSize(20);
	m_MusicLevelLeft.setOutlineColor(m_OutlineColor);
	m_MusicLevelRight.setOutlineColor(m_OutlineColor);
	m_MusicLevelLeft.setOutlineThickness(3);
	m_MusicLevelRight.setOutlineThickness(3);
	m_MusicLevelLeft.setString("<");
	m_MusicLevelRight.setString(">"); 
	m_MusicLevelRight.setPosition(WIDTH - m_MusicLevelRight.getGlobalBounds().width - MARGIN, HEIGHT - m_MusicLevelRight.getGlobalBounds().height - MARGIN);
	m_MusicLevel.setPosition(m_MusicLevelRight.getPosition().x - m_MusicLevel.getGlobalBounds().width, m_MusicLevelRight.getPosition().y);
	m_MusicLevelLeft.setPosition(m_MusicLevel.getPosition().x - m_MusicLevelLeft.getGlobalBounds().width, m_MusicLevel.getPosition().y);
	m_MusicButton.setPosition(m_MusicLevelLeft.getPosition().x - m_MusicButton.getGlobalBounds().width - MARGIN, HEIGHT - MARGIN - m_MusicButton.getGlobalBounds().height + 3);

	// Music and sound effects
	m_BackgroundMusic.openFromFile("Sounds/BackgroundMusic.wav");
	m_BackgroundMusic.setVolume(10);
	m_BackgroundMusic.setLoop(true);
	m_BackgroundMusic.play();
	m_StartSound.openFromFile("Sounds/GameStart.wav");
	m_StartSound.setVolume(60);
	m_VolumeChange.openFromFile("Sounds/VolumeChange.wav");
	m_HitSound.openFromFile("Sounds/Hit.wav");
	m_PointSound.openFromFile("Sounds/Point.wav");
	m_DefeatSound.openFromFile("Sounds/Defeat.wav");
	m_Wait.openFromFile("Sounds/Wait.wav");

	// Title screen UI
	m_Title1.setFont(m_Font);
	m_Title2.setFont(m_Font);
	m_HighestScoreText.setFont(m_Font);
	m_CurrentScoreText.setFont(m_Font);
	m_Instructions.setFont(m_Font);
	m_Title1.setCharacterSize(90);
	m_Title2.setCharacterSize(90);
	m_HighestScoreText.setCharacterSize(20);
	m_CurrentScoreText.setCharacterSize(20);
	m_Instructions.setCharacterSize(30);
	m_Title1.setFillColor(m_TitleColor);
	m_Title1.setOutlineColor(m_OutlineColor);
	m_Title1.setOutlineThickness(3);
	m_Title2.setFillColor(m_TitleColor);
	m_Title2.setOutlineColor(m_OutlineColor);
	m_Title2.setOutlineThickness(3);
	m_HighestScoreText.setOutlineColor(m_OutlineColor);
	m_HighestScoreText.setFillColor(m_FillColor);
	m_HighestScoreText.setOutlineThickness(3);
	m_Instructions.setOutlineColor(m_OutlineColor);
	m_Instructions.setFillColor(m_FillColor);
	m_Instructions.setOutlineThickness(3);
	m_CurrentScoreText.setOutlineColor(m_OutlineColor);
	m_CurrentScoreText.setFillColor(m_FillColor);
	m_CurrentScoreText.setOutlineThickness(3);
	m_Title1.setString("Flappy");
	m_Title2.setString("Yaki");
	m_HighestScoreText.setString("High Score: 0");
	m_CurrentScoreText.setString("0");
	m_Instructions.setString("Press 'Space' to Start");
	m_Title1.setPosition((WIDTH - m_Title1.getGlobalBounds().width) / 2, 5);
	m_Title2.setPosition((WIDTH - m_Title2.getGlobalBounds().width) / 2, 100);
	m_HighestScoreText.setPosition((WIDTH - m_HighestScoreText.getGlobalBounds().width) / 2, 200);
	m_CurrentScoreText.setPosition((WIDTH - m_CurrentScoreText.getGlobalBounds().width) / 2, 10);
	m_Instructions.setPosition((WIDTH - m_Instructions.getGlobalBounds().width) / 2, 240);

	// Booleans
	m_GameStarted = false;
	m_ShowInstructions = true;
	m_InAnimation = false;
	m_Muted = false;
	m_ColorUp = true;
	m_TransitionIn = false;
	m_TransitionOut = false;
	m_YakiEntering = false;

	// Integer variables
	m_HighestScoreInt = 0;
	m_InstructionsTimerMax = 40;
	m_Volume = MAX_VOLUME / 2;
	m_InstructionsTimerCurrent = m_InstructionsTimerMax;
}

// Method that is called whenever the player loses
void Engine::defeat() {
	m_InAnimation = true;
	m_GameStarted = false;
	m_TransitionOut = true;
	m_TransitionIn = false;
	m_HitSound.play();
	m_DefeatSound.play();
	if (m_CurrentScoreInt > m_HighestScoreInt) {
		m_HighestScoreInt = m_CurrentScoreInt;
	}
}

// Method that is called to start the entire game
void Engine::start() {

	Clock clock;

	while (m_Window.isOpen()) {
		Event event;
		while (m_Window.pollEvent(event)) {
			// Checking if the window has been closed
			if (event.type == Event::Closed) {
				m_Window.close();
			}
			mouseInput(event);
		}

		// Loops every 0.03 seconds
		if (clock.getElapsedTime().asMilliseconds() >= 30) {
			input();
			update();
			draw();
			clock.restart();
		}
	}
}