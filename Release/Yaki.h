/*
Created by Matthew Hwang
Last Updated: 9/14/2017
*/

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

// The character
class Yaki {

private:
	Vector2f m_Position;
	Vector2f m_Velocity;
	Texture m_Texture;
	Texture m_TextureUp;
	Texture m_TextureDown;
	Sprite m_Sprite;
	int m_MaxFallingVelocity;
	int m_Gravity;

public:
	Yaki();
	int getMaxFallingVelocity();
	Vector2f getPosition();
	Vector2f getVelocity();
	void setPosition(Vector2f newPosition);
	void setVelocity(Vector2f newVelocity);
	Sprite getSprite();
	void update();
	int getGravity();

};