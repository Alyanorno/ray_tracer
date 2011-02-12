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
 	//raytracer._lights[0].position[xyz] += length;
void Input( void )
{
	static bool pressedD = false;
	static bool pressedA = false;
	static bool pressedS = false;
	static bool pressedW = false;
	static bool pressedE = false;
	static bool pressedF = false;

	SDL_Event event;
	while( SDL_PollEvent(&event) )
		if(event.key.keysym.sym == SDLK_ESCAPE)
			done = true;
		else if(event.key.keysym.sym == 'd')
			pressedD = pressedD ? false : true;
		else if(event.key.keysym.sym == 'a')
			pressedA = pressedA ? false : true;
		else if(event.key.keysym.sym == 's')
			pressedS = pressedS ? false : true;
		else if(event.key.keysym.sym == 'w')
			pressedW = pressedW ? false : true;
		else if(event.key.keysym.sym == 'e')
			pressedE = pressedE ? false : true;
		else if(event.key.keysym.sym == 'f')
			pressedF = pressedF ? false : true;
	if( pressedD )
		MOVE( 0, 10 )
	if( pressedA )
		MOVE( 0, -10 )
	if( pressedS )
		MOVE( 1, 10 )
	if( pressedW )
		MOVE( 1, -10 )
	if( pressedE )
		MOVE( 2, 10 )
	if( pressedF )
		MOVE( 2, -10 )
}
#undef MOVE

void Draw( void )
{
	raytracer.Draw();
	SDL_Flip( screen );
}
