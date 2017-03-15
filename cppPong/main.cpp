#include <SDL.h>

SDL_Window* createWindow(const int& xWinPos, const int& yWinPos, const int& xRes, const int& yRes,
						SDL_Window* window);
SDL_Renderer* createRenderer(SDL_Window *window, SDL_Renderer *renderer);
void rendering(SDL_Renderer *renderer);

int main(int argc, char **argv)
{
	const int xWinPos = 63;
	const int yWinPos = 126;
	const int xRes = 800;
	const int yRes = 600;

	SDL_Window* window = nullptr;
	window = createWindow(xWinPos, yWinPos, xRes, yRes, window);
	
	SDL_Renderer* renderer = nullptr;
	renderer = createRenderer(window, renderer);

	auto done = false;
	SDL_Event event;

	while (!done)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type) {
			
			case SDL_MOUSEMOTION:
				// add the event
				break;
			case SDL_QUIT:
				done = true;
				break;
			}
		}
		rendering(renderer);
	}

	SDL_Quit();
	return 0;
}

SDL_Window* createWindow(const int& xWinPos, const int& yWinPos, const int& xRes, const int& yRes,
	SDL_Window* window)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

	return window = SDL_CreateWindow("cpp_pong", xWinPos, yWinPos, xRes, yRes, SDL_WINDOW_BORDERLESS);
}

SDL_Renderer* createRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
	return renderer = SDL_CreateRenderer(window, -1, 0); // window, index, flags
}

void rendering(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	SDL_RenderPresent(renderer);

}