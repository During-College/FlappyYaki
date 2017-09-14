/*
Created by Matthew Hwang
Last Updated: 9/14/2017
*/

#include "Engine.h"

// Method used to update everything about the game
void Engine::update() {

	// Making the background scroll and loop with two sprites
	m_BackgroundSprite1.setPosition(m_BackgroundSprite1.getPosition().x - 1, 0);
	m_BackgroundSprite2.setPosition(m_BackgroundSprite2.getPosition().x - 1, 0);
	if (m_BackgroundSprite1.getPosition().x + m_BackgroundSprite1.getGlobalBounds().width <= 0) {
		m_BackgroundSprite1.setPosition(Vector2f(800, 0));
	}
	if (m_BackgroundSprite2.getPosition().x + m_BackgroundSprite2.getGlobalBounds().width <= 0) {
		m_BackgroundSprite2.setPosition(Vector2f(800, 0));
	}

	// Updating strings that can change (High score, current score, and the volume indicator at bottom right)
	m_HighestScoreText.setString("High Score: " + to_string(m_HighestScoreInt));
	m_CurrentScoreText.setString(to_string(m_CurrentScoreInt));
	String volumeString = " ";
	int loops = m_Volume / 5;
	for (int i = 0; i < loops; i++) {
		volumeString += "| ";
	}
	loops = (MAX_VOLUME - m_Volume) / 5;
	for (int i = 0; i < loops; i++) {
		volumeString += "  ";
	}
	m_MusicLevel.setString(volumeString);

	// Making the title screen fade in and out
	if (m_ColorUp) {
		if (m_TitleColor.r > 76) {
			m_TitleColor.r--;
		}
		if (m_TitleColor.g > 115) {
			m_TitleColor.g--;
		}
		if (m_TitleColor.r <= 76 && m_TitleColor.g <= 115) {
			m_ColorUp = false;
		}
	}
	else {
		if (m_TitleColor.r < TITLE_COLOR_R) {
			m_TitleColor.r++;
		}
		if (m_TitleColor.g < TITLE_COLOR_G) {
			m_TitleColor.g++;
		}
		if (m_TitleColor.r >= TITLE_COLOR_R && m_TitleColor.g >= TITLE_COLOR_G) {
			m_ColorUp = true;
		}
	}
	m_Title1.setFillColor(m_TitleColor);
	m_Title2.setFillColor(m_TitleColor);

	// If the game has been started (space has been pressed)
	if (!m_GameStarted) {

		// Making the "Press Space to Play" instructions blink in and out
		if (m_InstructionsTimerCurrent > 0) {
			m_InstructionsTimerCurrent--;
		}
		else {
			m_InstructionsTimerCurrent = m_InstructionsTimerMax;
			m_ShowInstructions = !m_ShowInstructions;
		}

		// Making the character still fall after the player has lost
		if (m_TransitionOut) {
			if (m_Yaki.getVelocity().y < m_Yaki.getMaxFallingVelocity()) {
				m_Yaki.setVelocity(Vector2f(m_Yaki.getVelocity().x, m_Yaki.getVelocity().y + m_Yaki.getGravity()));
			}
			m_Yaki.setPosition(Vector2f(m_Yaki.getPosition().x + m_Yaki.getVelocity().x, m_Yaki.getPosition().y + m_Yaki.getVelocity().y));
		}
	}
	else {
		// Updating the character's position as it is moving into the screen from the left
		if (m_YakiEntering) {
			if (m_Yaki.getPosition().x >= 150) {
				m_Yaki.setVelocity(Vector2f(0, m_Yaki.getVelocity().y));
				m_YakiEntering = false;
				m_InAnimation = false;
			}
			// Making the character automatically bounce as it enters
			if (m_Yaki.getPosition().y > 150) {
				m_Yaki.setVelocity(Vector2f(m_Yaki.getVelocity().x, -m_Yaki.getMaxFallingVelocity()));
			}
		}
		// Making the character fall faster if not at max velocity
		if (m_Yaki.getVelocity().y < m_Yaki.getMaxFallingVelocity()) {
			m_Yaki.setVelocity(Vector2f(m_Yaki.getVelocity().x, m_Yaki.getVelocity().y + m_Yaki.getGravity()));
		}
		// Moving the character
		m_Yaki.setPosition(Vector2f(m_Yaki.getPosition().x + m_Yaki.getVelocity().x, m_Yaki.getPosition().y + m_Yaki.getVelocity().y));
	}

	// Moving Pipes
	if (!m_InAnimation && m_GameStarted) {
		for (int i = 0; i < 5; i++) {
			m_Pipes[i].setPosition(Vector2f(m_Pipes[i].getPosition().x + m_Pipes[i].getVelocity().x, m_Pipes[i].getPosition().y + m_Pipes[i].getVelocity().y));
			if (m_Pipes[i].getPosition().x + m_Pipes[i].getPipeUpSprite().getGlobalBounds().width <= 0) {
				m_Pipes[i].reset(m_CurrentScoreInt);
			}
			if (m_Pipes[i].getPosition().x + m_Pipes[i].getPipeUpSprite().getGlobalBounds().width <= m_Yaki.getSprite().getPosition().x) {
				if (!m_Pipes[i].getPassed()) {
					m_Pipes[i].setPassed(true);
					m_CurrentScoreInt++;
					m_PointSound.play();
				}
			}
			// Collision detection with character and pipes
			if (m_Yaki.getSprite().getGlobalBounds().intersects(m_Pipes[i].getPipeUpSprite().getGlobalBounds()) ||
				m_Yaki.getSprite().getGlobalBounds().intersects(m_Pipes[i].getPipeDownSprite().getGlobalBounds())) {
				defeat();
			}
		}
	}
	

	// Checking if out of bounds
	if ((m_Yaki.getPosition().y + m_Yaki.getSprite().getGlobalBounds().height > HEIGHT ||
		m_Yaki.getPosition().y < 0) && m_GameStarted) {
		defeat();
	}

	// Updating the pipe and character objects
	m_Yaki.update();
	for (int i = 0; i < 5; i++) {
		m_Pipes[i].update();
	}
}