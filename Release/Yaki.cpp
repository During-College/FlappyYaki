/*
Created by Matthew Hwang
Last Updated: 9/14/2017
*/

#include "Yaki.h"

// Constructor
Yaki::Yaki() {
	m_Texture.loadFromFile("Images/Yaki.png");
	m_TextureUp.loadFromFile("Images/YakiUp.png");
	m_TextureDown.loadFromFile("Images/YakiDown.png");
	m_Sprite.setTexture(m_Texture);
	m_Position.x = -m_Sprite.getGlobalBounds().width;
	m_Position.y = 100;
	m_Velocity.x = 2;
	m_Velocity.y = 0;
	m_Gravity = 2;
	m_Sprite.setPosition(m_Position);
	m_MaxFallingVelocity = 14;
}

// Returns the maximum falling velocity
int Yaki::getMaxFallingVelocity() {
	return m_MaxFallingVelocity;
}

// Returns the position of the character
Vector2f Yaki::getPosition() {
	return m_Position;
}

// Returns the velocity of the character
Vector2f Yaki::getVelocity() {
	return m_Velocity;
}

// Sets the position of the character to the given new position
void Yaki::setPosition(Vector2f newPosition) {
	m_Position = newPosition;
}

// Returns the gravity value
int Yaki::getGravity() {
	return m_Gravity;
}

// Sets the velocity of the character to the given new velocity
void Yaki::setVelocity(Vector2f newVelocity) {
	m_Velocity = newVelocity;
}

// Get the sprite of the character
Sprite Yaki::getSprite() {
	return m_Sprite;
}

// Update method to be called upon every update frame
void Yaki::update() {
	if (m_Velocity.y > 4) {
		m_Sprite.setTexture(m_TextureDown);
	}
	else if (m_Velocity.y < -4) {
		m_Sprite.setTexture(m_TextureUp);
	}
	else {
		m_Sprite.setTexture(m_Texture);
	}
	m_Sprite.setPosition(m_Position);
}