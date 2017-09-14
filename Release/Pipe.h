/*
Created by Matthew Hwang
Last Updated: 9/14/2017
*/

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

// The pipe that stores both the upper and bottom pipe textures
class Pipe {

private:
	Vector2f m_Position;
	Vector2f m_Velocity;
	Texture m_PipeUpTexture;
	Texture m_PipeDownTexture;
	Sprite m_PipeUpSprite;
	Sprite m_PipeDownSprite;
	int m_Gap = 100;
	int m_MinPipe = 50;
	bool m_Passed;

public:
	Pipe();
	void reset(int points);
	Vector2f getPosition();
	Vector2f getVelocity();
	void setPosition(Vector2f newPosition);
	Sprite getPipeUpSprite();
	Sprite getPipeDownSprite();
	void update();
	bool getPassed();
	void setPassed(bool state);

};