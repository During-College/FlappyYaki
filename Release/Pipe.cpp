/*
Created by Matthew Hwang
Last Updated: 9/14/2017
*/

#include "Pipe.h"

// Constructor
Pipe::Pipe() {
	m_PipeUpTexture.loadFromFile("Images/PipeUp.png");
	m_PipeDownTexture.loadFromFile("Images/PipeDown.png");
	m_PipeUpSprite.setTexture(m_PipeUpTexture);
	m_PipeDownSprite.setTexture(m_PipeDownTexture);
	m_Position.x = 800;
	m_Position.y = -150 + (rand() % 100);
	m_Velocity.x = -6;
	m_Velocity.y = 0;
	m_PipeDownSprite.setPosition(m_Position.x, m_Position.y);
	m_PipeUpSprite.setPosition(m_Position.x, m_Position.y + m_PipeDownSprite.getGlobalBounds().height + m_Gap);
	m_Passed = false;
}

// Resets the pipe to the right side of the screen and randomizes the height
void Pipe::reset(int points) {
	m_Position.x = 940;
	m_Position.y = -150 + (rand() % 100);
	m_PipeDownSprite.setPosition(m_Position.x, m_Position.y);
	m_PipeUpSprite.setPosition(m_Position.x, m_Position.y + m_PipeDownSprite.getGlobalBounds().height + m_Gap);
	m_Passed = false;
	if (points >= 1) {
		m_Velocity.y = (rand() % 3) - 1;
	}
}

// Returns if the player has passed through the pipes
bool Pipe::getPassed() {
	return m_Passed;
}

// Sets the value of whether or not the player has passed through the pipes
void Pipe::setPassed(bool state) {
	m_Passed = state;
}

// Returns the position of the upper pipe
Vector2f Pipe::getPosition() {
	return m_Position;
}

// Returns the velocity of the pipes
Vector2f Pipe::getVelocity() {
	return m_Velocity;
}

// Sets the position of the pipes
void Pipe::setPosition(Vector2f newPosition) {
	m_Position = newPosition;
}

// Gets the sprite of the upper pipe
Sprite Pipe::getPipeUpSprite() {
	return m_PipeUpSprite;
}

// Gets the sprite of the bottom pipe
Sprite Pipe::getPipeDownSprite() {
	return m_PipeDownSprite;
}

// Method to be called on every update frame
void Pipe::update() {
	m_PipeDownSprite.setPosition(m_Position.x, m_Position.y);
	m_PipeUpSprite.setPosition(m_Position.x, m_Position.y + m_PipeDownSprite.getGlobalBounds().height + m_Gap);
	if (m_Position.y >= -50 && m_Velocity.y > 0) {
		m_Velocity.y *= -1;
	}
	else if (m_Position.y <= -150 && m_Velocity.y < 0) {
		m_Velocity.y *= -1;
	}
}