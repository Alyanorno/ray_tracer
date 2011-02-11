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

#define MOVE( xyz, length ) \
 	((Sphere*)raytracer._primitivs[0])->position[xyz] += length;
void Input( void )
{
	SDL_Event event;
	while( SDL_PollEvent(&event) )
		if(event.key.keysym.sym == SDLK_ESCAPE)
			done = true;
		else if(event.key.keysym.sym == 'd')
			MOVE( 0, 10 )
		else if(event.key.keysym.sym == 'a')
			MOVE( 0, -10 )
		else if(event.key.keysym.sym == 's')
			MOVE( 1, 10 )
		else if(event.key.keysym.sym == 'w')
			MOVE( 1, -10 )
		else if(event.key.keysym.sym == 'e')
			MOVE( 2, 10 )
		else if(event.key.keysym.sym == 'f')
			MOVE( 2, -10)
}
#undef MOVE

void Draw( void )
{
	raytracer.Draw();
	SDL_Flip( screen );
}
