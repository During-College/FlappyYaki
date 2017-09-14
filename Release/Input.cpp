/*
Created by Matthew Hwang
Last Updated: 9/14/2017
*/

#include "Engine.h"

// Method used for all keyboard inputs
void Engine::input() {
	// Exiting the game with the ESC key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		m_Window.close();
	}
	// All key input besides ESC available when not in an animation (fading in/out, character entering screen)
	if (!m_InAnimation) {
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			// Setting variables to allow the game to start and text to fade out
			if (!m_GameStarted) {
				m_StartSound.play();
				m_Wait.play();
				m_CurrentScoreInt = 0;
				m_InAnimation = true;
				m_TransitionIn = true;
				m_TransitionOut = false;
				m_YakiEntering = false;
				m_CurrentScoreInt = 0;
				m_Yaki.setVelocity(Vector2f(3, 0));
				m_Yaki.setPosition(Vector2f(-m_Yaki.getSprite().getGlobalBounds().width, 100));

				for (int i = 0; i < 5; i++) {
					m_Pipes[i].reset(m_CurrentScoreInt);
					m_Pipes[i].setPosition(Vector2f(m_Pipes[i].getPosition().x + i * 200, m_Pipes[i].getPosition().y));
				}
			}
			else {
				// Making the character jump
				if (m_Yaki.getVelocity().y >= 0) {
					m_Yaki.setVelocity(Vector2f(m_Yaki.getVelocity().x, -m_Yaki.getMaxFallingVelocity()));
				}
			}
		}
	}
}