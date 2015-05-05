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
	text.push_back(new JAM_Text("Hit Delete to Quit", "font/Underdog_tt_hinted.ttf", 25, renderer, 102, 51, 153));
	text.push_back(new JAM_Text("Hit Escape to Return", "font/Underdog_tt_hinted.ttf", 25, renderer, 102, 51, 153));
	text.push_back(new JAM_Text("Commands:", "font/Underdog_tt_hinted.ttf", 25, renderer, 102, 51, 153));
	text.push_back(new JAM_Text("-Press enter to apply all rules.", "font/Underdog_tt_hinted.ttf", 20, renderer, 102, 51, 153));
	text.push_back(new JAM_Text("-Press 1 to apply rule 1 only.", "font/Underdog_tt_hinted.ttf", 20, renderer, 102, 51, 153));
	text.push_back(new JAM_Text("-Press 2 to apply rule 2 only.", "font/Underdog_tt_hinted.ttf", 20, renderer, 102, 51, 153));
	text.push_back(new JAM_Text("-Press 3 to apply rule 3 only.", "font/Underdog_tt_hinted.ttf", 20, renderer, 102, 51, 153));
	text.push_back(new JAM_Text("-Hold Space to scatter the flock.", "font/Underdog_tt_hinted.ttf", 20, renderer, 102, 51, 153));
	text.push_back(new JAM_Text("Rules:", "font/Underdog_tt_hinted.ttf", 25, renderer, 102, 51, 153));
	text.push_back(new JAM_Text("-Rule 1 = Boids try to fly towards the centre of mass", "font/Underdog_tt_hinted.ttf", 20, 
		renderer, 102, 51, 153));
	text.push_back(new JAM_Text("of neighbouring boids.", "font/Underdog_tt_hinted.ttf", 20, renderer, 102, 51, 153));
	text.push_back(new JAM_Text("-Rule 2 = Boids try to keep a small distance away from other", "font/Underdog_tt_hinted.ttf", 20,
		renderer, 102, 51, 153));
	text.push_back(new JAM_Text("objects (including other boids).", "font/Underdog_tt_hinted.ttf", 20, renderer, 102, 51, 153));
	text.push_back(new JAM_Text("-Rule 3 = Boids try to match velocity with near boids.", "font/Underdog_tt_hinted.ttf", 20, 
		renderer, 102, 51, 153));
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

			return false;
			break;

		case SDL_KEYDOWN:

			switch (incomingEvent.key.keysym.sym)
			{
			case SDLK_DELETE: /*If Delete is pressed, end the game loop*/

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
	background->pushToScreen(renderer, 0, 0);

	/*display text*/
	text[0]->pushToScreen(screenWidth - 210, 10);
	text[1]->pushToScreen(10, 10);
	text[2]->pushToScreen(10, 70);
	text[3]->pushToScreen(10, 100);
	text[4]->pushToScreen(10, 130);
	text[5]->pushToScreen(10, 160);
	text[6]->pushToScreen(10, 190);
	text[7]->pushToScreen(10, 220);
	text[8]->pushToScreen(10, 280);
	text[9]->pushToScreen(10, 310);
	text[10]->pushToScreen(110, 340);
	text[11]->pushToScreen(10, 370);
	text[12]->pushToScreen(110, 400);
	text[13]->pushToScreen(10, 430);
}