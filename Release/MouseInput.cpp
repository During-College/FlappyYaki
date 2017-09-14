/*
Created by Matthew Hwang
Last Updated: 9/14/2017
*/

#include "Engine.h"
#include <iostream>

// Method responsible for all mouse input, specifically for use with the audio system
void Engine::mouseInput(Event event) {
	// When the mute button is clicked
	if (event.type == Event::MouseButtonPressed) {
		int x = Mouse::getPosition(m_Window).x;
		int y = Mouse::getPosition(m_Window).y;
		if (x >= m_MusicButton.getPosition().x && x <= m_MusicButton.getPosition().x + m_MusicButton.getGlobalBounds().width &&
			y >= m_MusicButton.getPosition().y && y <= m_MusicButton.getPosition().y + m_MusicButton.getGlobalBounds().height) {
			// Unmuting
			if (m_Muted) {
				m_MusicButton.setTexture(m_MusicOnTexture);
				m_Muted = false;
				m_BackgroundMusic.setVolume(m_Volume);
				m_VolumeChange.play();
			}
			// Muting
			else {
				m_MusicButton.setTexture(m_MusicOffTexture);
				m_Muted = true;
				m_BackgroundMusic.setVolume(0);
				m_VolumeChange.play();
			}
		}
	}
	// Moving mouse over left and right arrows of the audio system
	if (event.type == Event::MouseMoved) {
		int x = Mouse::getPosition(m_Window).x;
		int y = Mouse::getPosition(m_Window).y;
		// Turn left button red
		if (x >= m_MusicLevelLeft.getPosition().x && x <= m_MusicLevelLeft.getPosition().x + m_MusicLevelLeft.getGlobalBounds().width &&
			y >= m_MusicLevelLeft.getPosition().y + 3 && y <= m_MusicLevelLeft.getPosition().y + m_MusicLevelLeft.getGlobalBounds().height + 3) {
			m_MusicLevelLeft.setFillColor(Color::Color(255, 0, 0, 255));
		}
		// Turn left button white
		else {
			m_MusicLevelLeft.setFillColor(Color::Color(255, 255, 255, 255));
		}

		// Turn right button red
		if (x >= m_MusicLevelRight.getPosition().x && x <= m_MusicLevelRight.getPosition().x + m_MusicLevelRight.getGlobalBounds().width &&
			y >= m_MusicLevelRight.getPosition().y + 3 && y <= m_MusicLevelRight.getPosition().y + m_MusicLevelRight.getGlobalBounds().height + 3) {
			m_MusicLevelRight.setFillColor(Color::Color(255, 0, 0, 255));
		}
		// Turn right button white
		else {
			m_MusicLevelRight.setFillColor(Color::Color(255, 255, 255, 255));
		}
	}
	// Clicking on the left and right arrows of the audio system
	if (event.type == Event::MouseButtonPressed) {
		int x = Mouse::getPosition(m_Window).x;
		int y = Mouse::getPosition(m_Window).y;
		// Left arrow pressed to decrease volume
		if (x >= m_MusicLevelLeft.getPosition().x && x <= m_MusicLevelLeft.getPosition().x + m_MusicLevelLeft.getGlobalBounds().width &&
			y >= m_MusicLevelLeft.getPosition().y + 3 && y <= m_MusicLevelLeft.getPosition().y + m_MusicLevelLeft.getGlobalBounds().height + 3) {
			if (m_Volume > 0) {
				m_Volume -= 5;
				m_BackgroundMusic.setVolume(m_Volume);
				m_VolumeChange.play();
			}
		}
		// Right arrow pressed to increase volume
		if (x >= m_MusicLevelRight.getPosition().x && x <= m_MusicLevelRight.getPosition().x + m_MusicLevelRight.getGlobalBounds().width &&
			y >= m_MusicLevelRight.getPosition().y + 3 && y <= m_MusicLevelRight.getPosition().y + m_MusicLevelRight.getGlobalBounds().height + 3) {
			if (m_Volume < 20) {
				m_Volume += 5;
				m_BackgroundMusic.setVolume(m_Volume);
				m_VolumeChange.play();
			}
		}
	}
}