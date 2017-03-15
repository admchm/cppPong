#include <SDL.h>

void initSDL(const int&, const int&, const int&, const int&);

int main(int argc, char **argv)
{

	const int xWinPos = 63;
	const int yWinPos = 126;
	const int xRes = 1280;
	const int yRes = 720;

	initSDL(xWinPos, yWinPos, xRes, yRes);

	SDL_Quit();
	return 0;
}

void initSDL(const int& xWinPos, const int& yWinPos, const int& xRes, const int& yRes)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("cpp_pong", xWinPos, yWinPos, xRes, yRes, SDL_WINDOW_BORDERLESS);
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0); // window, index, flags
}