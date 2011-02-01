#include <Windows.h>
#include "SDL/include/SDL.h"

#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")

#include "raytracer.h"

bool done = false;
Raytracer raytracer;

void Initialize( void );
void Run( void );
int main( int argc, char *argv[])
{
	Initialize();
	Run();
	return 0;
}

void Initialize( void )
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(800, 600, 0, SDL_HWSURFACE);

	raytracer.Initialize();
}

void Input( void );
void Draw( void );
void Run( void )
{
	Uint32 time = SDL_GetTicks();
	Uint32 secondTime = SDL_GetTicks();
	while( !done )
	{
		while( time + 10 > secondTime)
		{
			SDL_Delay(1);
			secondTime = SDL_GetTicks();
		}

		Input();
		Draw();
		time = SDL_GetTicks();
	}
}

void Input( void )
{
	SDL_Event event;
	while( SDL_PollEvent(&event) )
		if(event.key.keysym.sym == SDLK_ESCAPE)
			done = true;
}

void Draw( void )
{
	raytracer.Draw();
}
