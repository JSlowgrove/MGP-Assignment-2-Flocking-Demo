#include "Game.h"
#include "Help.h"

/**************************************************************************************************************/

/*Constructs the game object*/
Game::Game(JAM_StateManager * stateManager, SDL_Renderer* renderer, int screenWidth, int screenHeight)
	: JAM_State(stateManager, renderer, screenWidth, screenHeight)
{
	/*initialise the music*/
	music = new JAM_Audio("aud/Long Time Coming.ogg", true);
	music->startAudio();

	/*create a texture for the boids*/
	boidTexture = new JAM_Texture(renderer, 255, 255, 255);

	/*initialise the flocking object*/
	flocking = new JAM_Flocking(25, boidTexture, screenWidth, screenHeight, 25.0f);

#ifdef _WIN32
	
	/*initialise the text*/
	text.push_back(new JAM_Text(
		"Hit Delete to Quit", "font/Underdog_tt_hinted.ttf", 
		(int)JAM_Utilities::scaleNumber(25.0f, screenHeight), 
		renderer, 0, 0, 0));

	text.push_back(new JAM_Text(
		"Hit Escape for Help", "font/Underdog_tt_hinted.ttf",
		(int)JAM_Utilities::scaleNumber(25.0f, screenHeight),
		renderer, 0, 0, 0));

#elif __ANDROID__

	/*initialise the text*/
	text.push_back(new JAM_Text(
		"Press the screen to change the Boids behaviour", "font/Underdog_tt_hinted.ttf",
		(int)JAM_Utilities::scaleNumber(25.0f, screenHeight), 
		renderer, 0, 0, 0));


#endif

	/*initialise the current rule setting*/
	current = 0;
}

/**************************************************************************************************************/

/*Destructs the game object*/
Game::~Game()
{
	/*stop music*/
	music->stopAudio();
	/*delete audio pointers*/
	delete music;
	/*delete pointers*/
	delete flocking;
	delete boidTexture;
	for (auto message : text)
	{
		delete message;
	}
}

/**************************************************************************************************************/

/*handles inputs*/
bool Game::input()
{
	/*Check for user input*/
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{

#ifdef __ANDROID__

		/*handle the android inputs*/
		return androidInput(incomingEvent);

#elif _WIN32	

		/*handle the windows inputs*/
		return windowsInput(incomingEvent);

#endif

	}
	return true;
}

/**************************************************************************************************************/

/*handles windows inputs*/
bool Game::windowsInput(SDL_Event& incomingEvent)
{
	switch (incomingEvent.type)
	{
	case SDL_QUIT: /*If quit is pressed, end the game loop*/

		SDL_LogMessage(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR, "Exiting Main Loop");
		return false;
		break;

	case SDL_KEYDOWN:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_DELETE: /*If Delete is pressed, end the game loop*/

			SDL_LogMessage(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR, "Exiting Main Loop");
			return false;
			break;

		case SDLK_ESCAPE: /*If Escape is pressed, open menu*/
			/*open up the help*/
			stateManager->addState(new Help(stateManager, renderer, screenWidth, screenHeight, music));
			return true;
			break;

		case SDLK_RETURN: /*If Enter is pressed all rules are active*/

			/*activate all rules*/
			current = 0;
			break;

		case SDLK_1: /*If 1 is pressed only rule 1 is active*/

			/*activate rule 1 and deactivate all other rules*/
			current = 1;
			break;

		case SDLK_2: /*If 2 is pressed only rule 2 is active*/

			/*activate rule 2 and deactivate all other rules*/
			current = 2;
			break;

		case SDLK_3: /*If 3 is pressed only rule 3 is active*/

			/*activate rule3 and deactivate all other rules*/
			current = 3;
			break;

		case SDLK_SPACE: /*If Space is pressed scatter the flock*/

			/*activate rule 2 and 3 and invert rule 1*/
			current = 4;
			break;
		}
		break;

	case SDL_KEYUP:

		switch (incomingEvent.key.keysym.sym)
		{

		case SDLK_SPACE: /*If Space is released activate all rules*/

			/*activate all rules*/
			current = 0;
			break;
		}
	}
	return true;
}

/**************************************************************************************************************/

/*handles android inputs*/
bool Game::androidInput(SDL_Event& incomingEvent)
{
	switch (incomingEvent.type)
	{
	case SDL_QUIT: /*If quit is pressed, end the game loop*/

		SDL_LogMessage(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR, "Exiting Main Loop");
		return false;
		break;

	case SDL_FINGERDOWN:

		/*update the current rule settings*/
		current++;
		if (current > 4)
		{
			current = 0;
		}
		break;

	case SDL_KEYDOWN:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_AC_BACK: /*If Back is pressed on the phone, end the game loop*/

			SDL_LogMessage(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR, "Exiting Main Loop");
			return false;
			break;
		}
		break;
	}
	return true;
}

/**************************************************************************************************************/

/*updates the game*/
void Game::update(float dt)
{
	/*keep the music playing*/
	music->startAudio();

	/*update the rules*/
	switch (current)
	{
	case 0: /*If 0 all rules are active*/

		/*activate all rules*/
		flocking->setRule1(1);
		flocking->setRule2(1);
		flocking->setRule3(1);
		break;

	case 1: /*If 1 only rule 1 is active*/

		/*activate rule 1*/
		flocking->setRule1(1);
		/*deactivate all other rules*/
		flocking->setRule2(0);
		flocking->setRule3(0);
		break;

	case 2: /*If 2  only rule 2 is active*/

		/*activate rule 2*/
		flocking->setRule2(1);
		/*deactivate all other rules*/
		flocking->setRule1(0);
		flocking->setRule3(0);
		break;

	case 3: /*If 3 only rule 3 is active*/

		/*activate rule3*/
		flocking->setRule3(1);
		/*deactivate all other rules*/
		flocking->setRule1(0);
		flocking->setRule2(0);
		break;

	case 4: /*If 4 scatter the flock*/

		/*activate rule 2 and 3*/
		flocking->setRule2(1);
		flocking->setRule3(1);
		/*invert rule 1*/
		flocking->setRule1(-1);
		break;
	}

	/*update the flocking*/
	flocking->update(dt);
}

/**************************************************************************************************************/

/*draws the game*/
void Game::draw()
{
	/*draw the flocking object*/
	flocking->draw(renderer);

#ifdef _WIN32

	/*display text*/
	text[0]->pushToScreen(screenWidth - (int)JAM_Utilities::scaleNumber(210.0f, screenHeight), (int)JAM_Utilities::scaleNumber(10.0f, screenHeight));
	text[1]->pushToScreen((int)JAM_Utilities::scaleNumber(10.0f, screenHeight), (int)JAM_Utilities::scaleNumber(10.0f, screenHeight));

#elif __ANDROID__

	/*display text*/
	text[0]->pushToScreen((int)JAM_Utilities::scaleNumber(10.0f, screenHeight), (int)JAM_Utilities::scaleNumber(10.0f, screenHeight));

#endif

}