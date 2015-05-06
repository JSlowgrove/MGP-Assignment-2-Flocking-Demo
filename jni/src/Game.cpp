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
	flocking = new JAM_Flocking(25, boidTexture, screenWidth, screenHeight, 25.0f, screenHeight);

#ifdef _WIN32
	
	/*initialise the text*/
	text.push_back(new JAM_Text(
		"Hit Delete to Quit", "font/Underdog_tt_hinted.ttf", 
		(int)JAM_Utilities::scaleNumber(25.0f, screenHeight), 
		renderer, 0, 0, 0));

#elif __ANDROID__

	/*initialise the text*/
	text.push_back(new JAM_Text(
		"Hit Back to Quit", "font/Underdog_tt_hinted.ttf",
		(int)JAM_Utilities::scaleNumber(25.0f, screenHeight), 
		renderer, 0, 0, 0));


#endif

	/*initialise the current rule setting*/
	current = 0;

	/*create a texture for the buttons*/
	boidTexture = new JAM_Texture(renderer, 135, 199, 46);

	/*push back button 0*/
	buttons.push_back(new JAM_Button(boidTexture,
		JAM_Utilities::scaleNumber(10.0f, screenHeight),
		JAM_Utilities::scaleNumber(70.0f, screenHeight),
		"All Rules",
		"font/Underdog_tt_hinted.ttf",
		(int)JAM_Utilities::scaleNumber(24.0f, screenHeight),
		0,
		0,
		0,
		renderer,
		JAM_Utilities::scaleNumber(5.0f, screenHeight),
		JAM_Utilities::scaleNumber(150.0f, screenHeight),
		JAM_Utilities::scaleNumber(50.0f, screenHeight)));

	/*push back button 1*/
	buttons.push_back(new JAM_Button(boidTexture, 
		JAM_Utilities::scaleNumber(10.0f, screenHeight),
		JAM_Utilities::scaleNumber(130.0f, screenHeight),
		"Rule 1",
		"font/Underdog_tt_hinted.ttf",
		(int)JAM_Utilities::scaleNumber(24.0f, screenHeight),
		0,
		0,
		0,
		renderer,
		JAM_Utilities::scaleNumber(5.0f, screenHeight),
		JAM_Utilities::scaleNumber(150.0f, screenHeight),
		JAM_Utilities::scaleNumber(50.0f, screenHeight)));

	/*push back button 2*/
	buttons.push_back(new JAM_Button(boidTexture,
		JAM_Utilities::scaleNumber(10.0f, screenHeight),
		JAM_Utilities::scaleNumber(190.0f, screenHeight),
		"Rule 2",
		"font/Underdog_tt_hinted.ttf",
		(int)JAM_Utilities::scaleNumber(24.0f, screenHeight),
		0,
		0,
		0,
		renderer,
		JAM_Utilities::scaleNumber(5.0f, screenHeight),
		JAM_Utilities::scaleNumber(150.0f, screenHeight),
		JAM_Utilities::scaleNumber(50.0f, screenHeight)));

	/*push back button 3*/
	buttons.push_back(new JAM_Button(boidTexture,
		JAM_Utilities::scaleNumber(10.0f, screenHeight),
		JAM_Utilities::scaleNumber(250.0f, screenHeight),
		"Rule 3",
		"font/Underdog_tt_hinted.ttf",
		(int)JAM_Utilities::scaleNumber(24.0f, screenHeight),
		0,
		0,
		0,
		renderer,
		JAM_Utilities::scaleNumber(5.0f, screenHeight),
		JAM_Utilities::scaleNumber(150.0f, screenHeight),
		JAM_Utilities::scaleNumber(50.0f, screenHeight)));

	/*push back button 4*/
	buttons.push_back(new JAM_Button(boidTexture,
		JAM_Utilities::scaleNumber(10.0f, screenHeight),
		JAM_Utilities::scaleNumber(310.0f, screenHeight),
		"Scatter",
		"font/Underdog_tt_hinted.ttf",
		(int)JAM_Utilities::scaleNumber(24.0f, screenHeight),
		0,
		0,
		0,
		renderer,
		JAM_Utilities::scaleNumber(5.0f, screenHeight),
		JAM_Utilities::scaleNumber(150.0f, screenHeight),
		JAM_Utilities::scaleNumber(50.0f, screenHeight)));

	/*push back button 5*/
	buttons.push_back(new JAM_Button(boidTexture,
		JAM_Utilities::scaleNumber(10.0f, screenHeight),
		JAM_Utilities::scaleNumber(10.0f, screenHeight),
		"Help",
		"font/Underdog_tt_hinted.ttf",
		(int)JAM_Utilities::scaleNumber(24.0f, screenHeight),
		0,
		0,
		0,
		renderer,
		JAM_Utilities::scaleNumber(5.0f, screenHeight),
		JAM_Utilities::scaleNumber(150.0f, screenHeight),
		JAM_Utilities::scaleNumber(50.0f, screenHeight)));
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
	for (auto button : buttons)
	{
		delete button;
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
		switch (incomingEvent.type)
		{
		case SDL_QUIT: /*If quit is pressed, end the game loop*/

			SDL_Log("Exiting Main Loop");
			return false;
			break;
		}

		/*handle button 0 inputs (all rules)*/
		if (buttons[0]->input(incomingEvent))
		{
			/*activate all rules*/
			current = 0;
		}

		/*handle button 1 inputs (rule 1)*/
		if (buttons[1]->input(incomingEvent))
		{
			/*activate rule 1 and deactivate all other rules*/
			current = 1;
		}

		/*handle button 2 inputs (rule 2)*/
		if (buttons[2]->input(incomingEvent))
		{
			/*activate rule 2 and deactivate all other rules*/
			current = 2;
		}

		/*handle button 3 inputs (rule 3)*/
		if (buttons[3]->input(incomingEvent))
		{
			/*activate rule3 and deactivate all other rules*/
			current = 3;
		}

		/*handle button 4 inputs (scatter)*/
		if (buttons[4]->input(incomingEvent))
		{
			/*activate rule 2 and 3 and invert rule 1*/
			current = 4;
		}

		/*handle button 5 inputs (help)*/
		if (buttons[5]->input(incomingEvent))
		{
			/*open up the help*/
			stateManager->addState(new Help(stateManager, renderer, screenWidth, screenHeight, music));
			return true;
		}

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
	case SDL_KEYDOWN:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_DELETE: /*If Escape is pressed, end the game loop*/

			SDL_Log("Exiting Main Loop");
			return false;
			break;
		}
		break;
	}
	return true;
}

/**************************************************************************************************************/

/*handles android inputs*/
bool Game::androidInput(SDL_Event& incomingEvent)
{
	switch (incomingEvent.type)
	{
	case SDL_KEYDOWN:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_AC_BACK: /*If Back is pressed on the phone, end the game loop*/

			SDL_Log("Exiting Main Loop");
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

	/*display text*/
	text[0]->pushToScreen(screenWidth - (int)JAM_Utilities::scaleNumber(210.0f, screenHeight), (int)JAM_Utilities::scaleNumber(10.0f, screenHeight));

	/*display buttons*/
	for (auto button : buttons)
	{
		button->draw(renderer);
		button->drawText(renderer);
	}
}