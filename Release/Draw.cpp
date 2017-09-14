/*
Created by Matthew Hwang
Last Updated: 9/14/2017
*/

#include "Engine.h"

// Method that is responsible for drawing everything on the window
void Engine::draw() {
	m_Window.clear();

	// Drawing the background
	m_Window.draw(m_BackgroundSprite1);
	m_Window.draw(m_BackgroundSprite2);

	// During fading in, fading out, and character moving into screen animations
	if (m_InAnimation) {
		int speed = 4;
		// Title Screen fading out
		if (m_TransitionIn) {
			if (m_Title1.getFillColor().a > 1) {
				if (m_TitleColor.a <= speed - 1) {
					m_TitleColor.a = 0;
					m_OutlineColor.a = 0;
					m_FillColor.a = 0;
					m_TransitionIn = false;
					m_TransitionOut = false;
					m_YakiEntering = true;
					m_GameStarted = true;
				}
				else {
					m_TitleColor.a -= speed;
					m_OutlineColor.a -= speed;
					m_FillColor.a -= speed;
				}
				m_Title1.setFillColor(m_TitleColor);
				m_Title1.setOutlineColor(m_OutlineColor);
				m_Title2.setFillColor(m_TitleColor);
				m_Title2.setOutlineColor(m_OutlineColor);
				m_HighestScoreText.setFillColor(m_FillColor);
				m_HighestScoreText.setOutlineColor(m_OutlineColor);
				m_Instructions.setFillColor(m_FillColor);
				m_Instructions.setOutlineColor(m_OutlineColor);
			}
		}
		// Title screen fading out
		else if (m_TransitionOut) {
			if (m_Title1.getFillColor().a < 255) {
				if (m_TitleColor.a >= 255 - speed - 1) {
					m_TitleColor.a = 255;
					m_OutlineColor.a = 255;
					m_FillColor.a = 255;
					m_TransitionIn = false;
					m_TransitionOut = false;
					m_InAnimation = false;
				}
				else {
					m_TitleColor.a += speed;
					m_OutlineColor.a += speed;
					m_FillColor.a += speed;
				}
				m_Title1.setFillColor(m_TitleColor);
				m_Title1.setOutlineColor(m_OutlineColor);
				m_Title2.setFillColor(m_TitleColor);
				m_Title2.setOutlineColor(m_OutlineColor);
				m_HighestScoreText.setFillColor(m_FillColor);
				m_HighestScoreText.setOutlineColor(m_OutlineColor);
				m_Instructions.setFillColor(m_FillColor);
				m_Instructions.setOutlineColor(m_OutlineColor);
			}
		}
	}

	// Drawing the title screen
	if (!m_GameStarted) {
		m_Window.draw(m_Title1);
		m_Window.draw(m_Title2);
		m_Window.draw(m_HighestScoreText);
		if (m_ShowInstructions) {
			m_Window.draw(m_Instructions);
		}
	}
	else {
		// Drawing the pipes
		if (!m_InAnimation) {
			for (int i = 0; i < 5; i++) {
				m_Window.draw(m_Pipes[i].getPipeUpSprite());
				m_Window.draw(m_Pipes[i].getPipeDownSprite());
			}
			m_Window.draw(m_CurrentScoreText);
		}
	}
	// Drawing the character
	m_Window.draw(m_Yaki.getSprite());

	// Drawing the audio system
	m_Window.draw(m_MusicButton);
	m_Window.draw(m_MusicLevelLeft);
	m_Window.draw(m_MusicLevel);
	m_Window.draw(m_MusicLevelRight);

	// Displaying the window
	m_Window.display();
}