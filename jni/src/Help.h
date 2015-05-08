#pragma once

#include <SDL.h>
#include "JAM/State.h"
#include "JAM/StateManager.h"
#include "JAM/Audio.h"
#include "JAM/Texture.h"
#include "JAM/Text.h"
#include "JAM/Utilities.h"

/**
@brief Creates a Help object that inherits JAM_State.
Creates a Help object that inherits JAM_State and runs the Help.
@author Jamie Slowgrove
*/
class Help : public JAM_State
{
private:
	/**The text.*/
	std::vector<JAM_Text *> text;
	/**A pointer to the music.*/
	JAM_Audio* music;
	/**The background image.*/
	JAM_Texture* background;

	/**
	Handles the Windows Game input.
	@param incomingEvent A reference to the incoming SDL event.
	@returns If false then quit the Game State.
	*/
	bool windowsInput(SDL_Event& incomingEvent);

	/**
	Handles the Android Game input.
	@param incomingEvent A reference to the incoming SDL event.
	@returns If false then quit the Game State.
	*/
	bool androidInput(SDL_Event& incomingEvent);

public:
	/**
	Constructs the Help object.
	@param stateManager A pointer to the StateManager.
	@param renderer A pointer to the renderer.
	@param screenWidth The screen width.
	@param screenHeight The screen height.
	@param music A pointer to the music.
	*/
	Help(JAM_StateManager* stateManager, SDL_Renderer* renderer, int screenWidth, int screenHeight, JAM_Audio* music);

	/**
	Destructs the Help object.
	*/
	~Help();

	/**
	Handles the Help input.
	@returns If false the quit the Help State.
	*/
	bool input();

	/**
	A function to update the Help to allow the Help to run.
	@param dt The delta time.
	*/
	void update(float deltaTime);

	/**
	A function to draw to the screen.
	*/
	void draw();
};