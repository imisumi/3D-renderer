#include <stdio.h>
#include <SDL2/SDL.d>
#include <X11/Xlib.h>

void	init_window()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		fprintf(stderr, "Error init SDLn\n");
}

int	main(void)
{
	// Create SDL window
	init_window();




	return (0);
}
