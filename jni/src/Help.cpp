#include "help.h"
#include "Game.h"

/**************************************************************************************************************/

/*Constructs the Help object*/
Help::Help(JAM_StateManager * stateManager, SDL_Renderer* renderer, int screenWidth, int screenHeight, JAM_Audio* music)
	: JAM_State(stateManager, renderer, screenWidth, screenHeight)
{
	/*initialise the music*/
	this->music = music;

	/*initialise the background*/
	background = new JAM_Texture("img/background.png", renderer);

	/*initialise the text*/
	text.push_back(new JAM_Text(
		"Commands:", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(25.0f, screenHeight), renderer, 102, 51, 153));
	text.push_back(new JAM_Text(
		"-Press 'All Rules' to apply all rules.", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(20.0f, screenHeight), renderer, 102, 51, 153));
	text.push_back(new JAM_Text(
		"-Press 'Rule 1' to apply rule 1 only.", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(20.0f, screenHeight), renderer, 102, 51, 153));
	text.push_back(new JAM_Text(
		"-Press 'Rule 2' to apply rule 2 only.", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(20.0f, screenHeight), renderer, 102, 51, 153));
	text.push_back(new JAM_Text(
		"-Press 'Rule 3' to apply rule 3 only.", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(20.0f, screenHeight), renderer, 102, 51, 153));
	text.push_back(new JAM_Text(
		"-Press 'Scatter' to scatter the flock.", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(20.0f, screenHeight), renderer, 102, 51, 153));
	text.push_back(new JAM_Text(
		"Rules:", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(25.0f, screenHeight), renderer, 102, 51, 153));
	text.push_back(new JAM_Text(
		"-Rule 1 = Boids try to fly towards the centre of mass", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(20.0f, screenHeight),
		renderer, 102, 51, 153));
	text.push_back(new JAM_Text(
		"of neighbouring boids.", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(20.0f, screenHeight), renderer, 102, 51, 153));
	text.push_back(new JAM_Text(
		"-Rule 2 = Boids try to keep a small distance away from other", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(20.0f, screenHeight),
		renderer, 102, 51, 153));
	text.push_back(new JAM_Text(
		"objects (including other boids).", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(20.0f, screenHeight), renderer, 102, 51, 153));
	text.push_back(new JAM_Text(
		"-Rule 3 = Boids try to match velocity with near boids.", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(20.0f, screenHeight),
		renderer, 102, 51, 153));

#ifdef _WIN32

	/*initialise the text*/
	text.push_back(new JAM_Text(
		"Hit Escape to Return", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(25.0f, screenHeight), renderer, 102, 51, 153));
	text.push_back(new JAM_Text(
		"Hit Delete to Quit", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(25.0f, screenHeight), renderer, 102, 51, 153));

#elif __ANDROID__

	/*initialise the text*/
	text.push_back(new JAM_Text(
		"Hit Back to Return", "font/Underdog_tt_hinted.ttf", (int)JAM_Utilities::scaleNumber(25.0f, screenHeight), renderer, 102, 51, 153));


#endif
}

/**************************************************************************************************************/

/*Destructs the Help object*/
Help::~Help()
{
	/*delete text*/
	for (unsigned int i = 0; i < text.size(); i++)
	{
		delete text[i];
	}
}

/**************************************************************************************************************/

/*handles inputs*/
bool Help::input()
{
	/*Check for user input*/
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{
		switch (incomingEvent.type)
		{
		case SDL_QUIT: /*If player closes the window, end the game loop*/

			SDL_Log("Exiting Main Loop");
			return false;
			break;
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
bool Help::windowsInput(SDL_Event& incomingEvent)
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

		case SDLK_ESCAPE: /*If Escape is pressed, return to game*/

			/*return to the game*/
			stateManager->removeLastState();
			return true;
			break;
		}
		break;
	}
	return true;
}

/**************************************************************************************************************/

/*handles android inputs*/
bool Help::androidInput(SDL_Event& incomingEvent)
{
	switch (incomingEvent.type)
	{
	case SDL_KEYDOWN:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_AC_BACK: /*If Back is pressed on the phone, return to the game*/

			/*return to the game*/
			stateManager->removeLastState();
			return true;
			break;
		}
		break;
	}
	return true;
}

/**************************************************************************************************************/

/*updates the Help*/
void Help::update(float dt)
{
	/*keep the music playing*/
	music->startAudio();
}

/**************************************************************************************************************/

/*draws the Help*/
void Help::draw()
{
	/*display the background*/
	background->pushToScreen(renderer, 0, 0, screenWidth, screenHeight);

	/*display text*/
	text[0]->pushToScreen((int)JAM_Utilities::scaleNumber(10.0f, screenHeight), (int)JAM_Utilities::scaleNumber(70.0f, screenHeight));
	text[1]->pushToScreen((int)JAM_Utilities::scaleNumber(10.0f, screenHeight), (int)JAM_Utilities::scaleNumber(100.0f, screenHeight));
	text[2]->pushToScreen((int)JAM_Utilities::scaleNumber(10.0f, screenHeight), (int)JAM_Utilities::scaleNumber(130.0f, screenHeight));
	text[3]->pushToScreen((int)JAM_Utilities::scaleNumber(10.0f, screenHeight), (int)JAM_Utilities::scaleNumber(160.0f, screenHeight));
	text[4]->pushToScreen((int)JAM_Utilities::scaleNumber(10.0f, screenHeight), (int)JAM_Utilities::scaleNumber(190.0f, screenHeight));
	text[5]->pushToScreen((int)JAM_Utilities::scaleNumber(10.0f, screenHeight), (int)JAM_Utilities::scaleNumber(220.0f, screenHeight));
	text[6]->pushToScreen((int)JAM_Utilities::scaleNumber(10.0f, screenHeight), (int)JAM_Utilities::scaleNumber(280.0f, screenHeight));
	text[7]->pushToScreen((int)JAM_Utilities::scaleNumber(10.0f, screenHeight), (int)JAM_Utilities::scaleNumber(310.0f, screenHeight));
	text[8]->pushToScreen((int)JAM_Utilities::scaleNumber(110.0f, screenHeight), (int)JAM_Utilities::scaleNumber(340.0f, screenHeight));
	text[9]->pushToScreen((int)JAM_Utilities::scaleNumber(10.0f, screenHeight), (int)JAM_Utilities::scaleNumber(370.0f, screenHeight));
	text[10]->pushToScreen((int)JAM_Utilities::scaleNumber(110.0f, screenHeight), (int)JAM_Utilities::scaleNumber(400.0f, screenHeight));
	text[11]->pushToScreen((int)JAM_Utilities::scaleNumber(10.0f, screenHeight), (int)JAM_Utilities::scaleNumber(430.0f, screenHeight));
	text[12]->pushToScreen((int)JAM_Utilities::scaleNumber(10.0f, screenHeight), (int)JAM_Utilities::scaleNumber(10.0f, screenHeight));

#ifdef _WIN32
	
	text[13]->pushToScreen(screenWidth - (int)JAM_Utilities::scaleNumber(210.0f, screenHeight), (int)JAM_Utilities::scaleNumber(10.0f, screenHeight));

#endif
}