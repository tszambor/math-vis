#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <chrono>
#include <vector>

// Screen dimensions constants
const int SCALE = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init(const int SCALE)
{
	bool bSuccess = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initilize! SDL_Error: " << SDL_GetError() << std::endl;
		bSuccess = false;
	}
	else
	{

		// Create window
		gWindow = SDL_CreateWindow("Ulam Sieve", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCALE, SCALE, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			bSuccess = false;
		}
		else
		{
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				bSuccess = false;
			}
			else
			{
				// Initilize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				SDL_RenderClear(gRenderer);

				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			}
		}
	}

	return bSuccess;
}

void close()
{
	// Destroy renderer
	if (gRenderer != NULL)
	{
		SDL_DestroyRenderer(gRenderer);
		gRenderer = NULL;
	}

	// Destroy window
	if (gWindow != NULL)
	{
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
	}

	// Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	const int max_n = SCALE * SCALE;

	std::vector<bool> isPrime(max_n + 1, true);

	std::cout << "Vector capacity: " << isPrime.size() << std::endl;

	std::cout << "Generating prime number sieve..." << std::endl;

	auto sieveStarted = std::chrono::steady_clock::now();

	for (int i = 2; i <= max_n / i; i++)
	{
		if (isPrime[i])
		{
			for (int j = i; j <= max_n / i; j++)
				isPrime[i * j] = false;
		}
	}

	auto sieveEnded = std::chrono::steady_clock::now();

	std::chrono::microseconds sieveDuration = std::chrono::duration_cast<std::chrono::microseconds>(sieveEnded - sieveStarted);
	std::cout << "Prime sieve duration: " << sieveDuration.count() << std::endl;

	std::cout << "Done." << std::endl;

	if (init(SCALE))
	{
		int n = 1;
		int count = 2;

		int x = 0;
		int y = 0;

		auto renderStarted = std::chrono::steady_clock::now();

		if (isPrime[count])
			SDL_RenderDrawPoint(gRenderer, x + (SCALE / 2), y + (SCALE / 2));
		const int HALF_SCALE = SCALE / 2;

		while (count < max_n - 1)
		{
			int lim = ((n - 1) / 4) + 1;
			int modulo = n % 4;

			if (modulo == 1) {
				// get from current x to +lim
				while (x < lim && count < max_n - 1) {
					x++; count++;
					if (isPrime[count])
						SDL_RenderDrawPoint(gRenderer, x + (HALF_SCALE), y + (HALF_SCALE));
				}
			}
			else if (modulo == 2) {
				// get from current y to +lim
				while (y < lim && count < max_n - 1) {
					y++; count++;
					if (isPrime[count])
						SDL_RenderDrawPoint(gRenderer, x + (HALF_SCALE), y + (HALF_SCALE));
				}
			}
			else if (modulo == 3) {
				// get from current x down to -lim
				while (x > -1 * lim && count < max_n - 1) {
					x--; count++;
					if (isPrime[count])
						SDL_RenderDrawPoint(gRenderer, x + (HALF_SCALE), y + (HALF_SCALE));
				}
			}
			else {
				// get from current y down to -lim
				while (y > -1 * lim && count < max_n - 1) {
					y--; count++;
					if (isPrime[count])
						SDL_RenderDrawPoint(gRenderer, x + (HALF_SCALE), y + (HALF_SCALE));
				}
			}
			// SDL_RenderPresent(gRenderer);
			n++;
		}

		SDL_RenderPresent(gRenderer);

		auto renderEnded = std::chrono::steady_clock::now();

		std::chrono::microseconds renderDuration = std::chrono::duration_cast<std::chrono::microseconds>(renderEnded - renderStarted);
		std::cout << "Render duration: " << renderDuration.count() << std::endl;

		// Start the main loop
		bool bQuit = false;

		// Event handler
		SDL_Event e;

		// While application is running
		while (!bQuit)
		{
			while (SDL_WaitEvent(&e))
			{
				// User requests quit
				if (e.type == SDL_QUIT)
				{
					bQuit = true;
                    break;
				}
                SDL_Delay(50);
			}
		}
		close();
	}

	return 0;
}
