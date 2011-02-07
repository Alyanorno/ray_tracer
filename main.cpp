#include "use_sdl.h"
#include "raytracer.h"

SDL_Surface* screen;
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
	screen = SDL_SetVideoMode( 800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );

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
		while( time + 100 > secondTime)
		{
			SDL_Delay(1);
			secondTime = SDL_GetTicks();
		}

		Input();
		Draw();
		time = SDL_GetTicks();
	}
	SDL_Quit();
}

void Input( void )
{
	SDL_Event event;
	while( SDL_PollEvent(&event) )
		if(event.key.keysym.sym == SDLK_ESCAPE)
			done = true;
		else if(event.key.keysym.sym == 'd')
			raytracer._spheres[0].position[0] += 10;
		else if(event.key.keysym.sym == 'a')
			raytracer._spheres[0].position[0] -= 10;
		else if(event.key.keysym.sym == 's')
			raytracer._spheres[0].position[1] += 10;
		else if(event.key.keysym.sym == 'w')
			raytracer._spheres[0].position[1] -= 10;
		else if(event.key.keysym.sym == 'e')
			raytracer._spheres[0].position[2] += 10;
		else if(event.key.keysym.sym == 'f')
			raytracer._spheres[0].position[2] -= 10;
}

void Draw( void )
{
	raytracer.Draw();
	SDL_Flip( screen );
}
