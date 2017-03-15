#include <SDL.h>
#include <iostream>

class Player 
{
public:
	int xValPlayer;
	int yValPlayer;

	Player()
	{
		xValPlayer = 0;
		yValPlayer = 0;
	}
};

class Opponent
{
public:
	int xValOpponent;
	int yValOpponent;

	Opponent()
	{
		xValOpponent = 0;
		yValOpponent = 0;
	}
};

class Pong
{
public:
	int xValPong;
	int yValPong;
	int xPongV;
	int yPongV;

	Pong()
	{
		xValPong = 0;
		yValPong = 0;
		xPongV = 5;
		yPongV = 5;
	}
};

SDL_Window* createWindow(const int& xWinPos, const int& yWinPos, const int& xRes, const int& yRes,
						SDL_Window* window);

SDL_Renderer* createRenderer(SDL_Window*, SDL_Renderer*);
void gameLogic(const int&, const int&, SDL_Renderer*, Player*, Opponent*, Pong*);
void rendering(SDL_Renderer*, const int&, Player*, Opponent*, Pong*);
void clean(Player*, Opponent*, Pong*);

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

	Player* player = new Player;
	Opponent* opponent = new Opponent;
	Pong* pong = new Pong;

	auto currentTick = SDL_GetTicks() / 17;

	auto done = false;
	SDL_Event event;

	while (!done)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type) {
			
			case SDL_MOUSEMOTION:
				player->yValPlayer = event.motion.y - 50;
				break;
			case SDL_QUIT:
				done = true;
				break;
			}
		}
			gameLogic(xRes, yRes, renderer, player, opponent, pong);
			rendering(renderer, xRes, player, opponent, pong);

	}

	clean(player, opponent, pong);
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

SDL_Renderer* createRenderer(SDL_Window* window, SDL_Renderer* renderer)
{
	return renderer = SDL_CreateRenderer(window, -1, 0); // window, index, flags
}

void gameLogic(const int& xRes, const int& yRes, SDL_Renderer* renderer, Player* player, Opponent* opponent, Pong* pong)
{

	pong->xValPong += pong->xPongV;	// movement
	pong->yValPong += pong->yPongV;

	if (pong->yValPong < 0 && pong->yPongV < 0) { pong->yPongV *= -1; }		// is ball flying
	
	if (pong->yValPong > yRes && pong->yPongV > 0) { pong->yPongV *= -1; }	// vertical movement
	
	if (pong->xValPong < 0 && pong->xPongV < 0)
	{
		pong->xPongV *= -1;
		if (pong->yValPong < player->yValPlayer || pong->yValPong > player->yValPlayer + 50)
		{
			// ++aiScore;
			pong->xValPong = xRes / 2;
			pong->yValPong = yRes / 2;
		}
	}

	if (pong->xValPong > xRes && pong->xPongV > 0)
	{
		pong->xPongV *= -1;
		if (pong->yValPong < opponent->yValOpponent || pong->yValPong > opponent->yValOpponent + 50)
		{
			// ++playerScore
			pong->xValPong = xRes / 2;
			pong->yValPong = yRes / 2;
		}
	}
}

void rendering(SDL_Renderer* renderer, const int& xRes, Player* player, Opponent* opponent, Pong* pong)
{
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	SDL_Rect rect;
	rect.x = 15;
	rect.y = player->yValPlayer;
	rect.w = 5;
	rect.h = 50;
	SDL_RenderFillRect(renderer, &rect);

	rect.x = xRes - 15;
	rect.y = opponent->yValOpponent;
	rect.w = 5;
	rect.h = 50;
	SDL_RenderFillRect(renderer, &rect);

	rect.x = pong->xValPong - 5;
	rect.y = pong->yValPong - 5;
	rect.w = 5;
	rect.h = 5;
	SDL_RenderFillRect(renderer, &rect);

	SDL_RenderPresent(renderer);
}

void clean(Player* player, Opponent* opponent, Pong* pong)
{
	delete player;
	delete opponent;
	delete pong;
}