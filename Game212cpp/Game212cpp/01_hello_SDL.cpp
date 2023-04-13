#include "Application.h"

/*
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

enum State 
{
	MENU_STATE = 0,
	GAME_STATE,
	END_STATE
};

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int CurrentState = State::MENU_STATE;
int foxPosX = 0;
int foxPosY = 0;

float timer = 0.0f;
float deltaTime = 0.0f;
float currentTime = 0.0f;
float lastTime = 0.0f;
float lifetime = 0.0f;
float sinus = 0.0f;
float cosinus = 0.0f;

bool running = true;
bool timerIncrement = false;

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y, int w, int h);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//Globally used font
TTF_Font* gFont = nullptr;

//Rendered  fonttexture
LTexture gMenuInfoTexture;
LTexture gEndTexture;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

//Scene textures
LTexture gFoxTexture;
LTexture gNatureBackgroundTexture;
LTexture gEndFoxLeftTopTexture;
LTexture gEndFoxRightBottomTexture;

//The music that will be played
Mix_Music *gMusic = nullptr;

//Check if the music is playing
bool gIsMusicPlaying = false;

LTexture::LTexture()
{
	//Initialize
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != nullptr;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, int w = -1, int h = -1)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Checks the rendering dimensions
	if (w != -1 && h != -1)
	{
		renderQuad.w = w;
		renderQuad.h = h;
	}

	SDL_RenderCopy(gRenderer, mTexture, nullptr, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != nullptr;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) )
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == nullptr)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("Font/Boba_Cups.ttf", 28);
	if (gFont == nullptr)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!gMenuInfoTexture.loadFromRenderedText("Start the game by clicking on the screen, or exit the game by the 'X' icon", textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	//Load music
	gMusic = Mix_LoadMUS("Music/What_Does_The_Fox_Say.ogg");
	if (gMusic == nullptr)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load Fox texture
	if (!gFoxTexture.loadFromFile("Images/foxcartoon.png"))
	{
		printf("Failed to load foxcartoon.png texture image!\n");
		success = false;
	}

	foxPosX = SCREEN_WIDTH	/ 2;
	foxPosY = SCREEN_HEIGHT	/ 2;

	//Load background texture
	if (!gNatureBackgroundTexture.loadFromFile("Images/nature_background.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}

	//Load background texture
	if (!gEndFoxLeftTopTexture.loadFromFile("Images/fox2.png"))
	{
		printf("Failed to load fox.png texture image!\n");
		success = false;
	}

	//Load background texture
	if (!gEndFoxRightBottomTexture.loadFromFile("Images/fox.png"))
	{
		printf("Failed to load fox.png texture image!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gFoxTexture.free();
	gNatureBackgroundTexture.free();

	//Free global font
	TTF_CloseFont(gFont);
	gFont = nullptr;

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = nullptr;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	//Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void resetTimer()
{
	timer = 0.0f;
	timerIncrement = false;
}

void handleEvents()
{
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
			case SDL_QUIT:
			{
				running = false;

				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				if (CurrentState == State::MENU_STATE)
				{
					int mouseX, mouseY;
					SDL_GetMouseState(&mouseX, &mouseY);

					//Todo switch to gamestate when button is pressed

					CurrentState = State::GAME_STATE;
					resetTimer();

					break;
				}

				else if (CurrentState == State::GAME_STATE)
				{
					int mouseX, mouseY;
					SDL_GetMouseState(&mouseX, &mouseY);

					const SDL_FPoint mousePosition = {(float)mouseX, (float)mouseY};
					const SDL_FRect foxQuad = {(float)foxPosX, (float)foxPosY, (float)gFoxTexture.getWidth(), (float)gFoxTexture.getHeight()};

					if(SDL_PointInFRect(&mousePosition, &foxQuad))
					{
						if (!gIsMusicPlaying)
						{
							Mix_PlayMusic(gMusic, -1);
							gIsMusicPlaying = true;
						
							//Start the timer here
							timerIncrement = true;
						}
					}
					
					break;
				}

				else if (CurrentState == State::END_STATE)
				{
					// TODO: maybe go back to the menu state
					// if you want to go to the menu state, do this:
					CurrentState = State::MENU_STATE;

					break;
				}

				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				if (CurrentState == State::MENU_STATE)
				{
					// Do something in the menu when the mouse button is released?
					// Do that here

					break;
				}

				else if (CurrentState == State::GAME_STATE)
				{
					if (gIsMusicPlaying)
					{
						Mix_HaltMusic();
						gIsMusicPlaying = false;

						// Generate the end texture
						SDL_Color textColor = { 0, 0, 0 };
						gEndTexture.loadFromRenderedText("You managed to hold the mouse pointer for " + std::to_string((int)timer) + " seconds.", textColor);
						//Stop the timer
						timerIncrement = false;

						CurrentState = State::END_STATE;
					}

					break;
				}

				else if (CurrentState == State::END_STATE)
				{
					// Do something in the end state when the mouse button is released?
					// Do that here


					break;
				}

				break;
			}

			default:
				break;
		}
	}
}

void update() 
{
	lastTime = currentTime;
	currentTime = SDL_GetTicks();

	deltaTime = (currentTime - lastTime) * 0.001;

	if (CurrentState == State::GAME_STATE)
	{
		if (timerIncrement)
			timer += deltaTime;
	}

	else if (CurrentState == State::END_STATE)
	{
		lifetime += deltaTime;

		sinus = sinf(lifetime * 4.0f);
		cosinus = cosf(lifetime * 4.0f);

	}
}

void render()
{
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderClear(gRenderer);

	switch (CurrentState)
	{
		// Render the menu state
		case State::MENU_STATE:
		{
			// TODO: render menu stuff

			//Render current frame
			gMenuInfoTexture.render((SCREEN_WIDTH - gMenuInfoTexture.getWidth()) / 2, (SCREEN_HEIGHT - gMenuInfoTexture.getHeight()) / 2);



			break;
		}

		// Render the game state
		case State::GAME_STATE:
		{
			//Render background texture to screen
			gNatureBackgroundTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

			//Render Fox to the screen
			gFoxTexture.render(foxPosX, foxPosY);

			break;
		}

		// Render the game state
		case State::END_STATE:
		{
			// Render the stuff for the end state (some text etc?)

			gEndTexture.render((SCREEN_WIDTH - gEndTexture.getWidth()) / 2, (SCREEN_HEIGHT - gEndTexture.getHeight()) / 2);
			
			const Uint32 flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;

			gEndFoxLeftTopTexture.render(-gEndFoxLeftTopTexture.getWidth() + (cosinus * 300.0f), -gEndFoxLeftTopTexture.getHeight() + (cosinus * 300.0f));
			gEndFoxRightBottomTexture.render(SCREEN_WIDTH - (sinus * 300.0f), SCREEN_HEIGHT - (sinus * 300.0f));

			break;
		}

		default:
			break;
	}

	SDL_RenderPresent(gRenderer);
}
*/

int main(int argc, char* args[])
{
	Application::Initialize();

	if (Application::GetInstance().init())
	{
		Application::GetInstance().run();
		Application::GetInstance().close();
	}

	Application::Deinitialize();

	/*
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		currentTime = SDL_GetTicks();
		lastTime = SDL_GetTicks();

		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}

		else
		{
			//While application is running
			while (running)
			{
				handleEvents();
				update();
				render();
			}
		}
	}

	//Free resources and close SDL
	close();
	*/

	return 0;
};