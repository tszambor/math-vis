//
//  main.cpp
//  BGIColors
//
//  Created by Tomasz Szambor on 25/12/2021.
//

#include <iostream>
#include <SDL2/sdl.h>

// screen dimension
const int SCALE = 800;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

// define BGI color constants
const SDL_Color bgiBLACK        = {.r = 0, .g = 0, .b = 0};
const SDL_Color bgiBLUE         = {.r = 0, .g = 0, .b = 170};
const SDL_Color bgiGREEN        = {.r = 0, .g = 170, .b = 0};
const SDL_Color bgiCYAN         = {.r = 0, .g = 170, .b = 170};
const SDL_Color bgiRED          = {.r = 170, .g = 0, .b = 0};
const SDL_Color bgiMAGENTA      = {.r = 170, .g = 0, .b = 170};
const SDL_Color bgiBROWN        = {.r = 170, .g = 85, .b = 0};
const SDL_Color bgiWHITE        = {.r = 170, .g = 170, .b = 170};
const SDL_Color bgiGRAY         = {.r = 85, .g = 85, .b = 85};
const SDL_Color bgiLIGHTBLUE    = {.r = 85, .g = 85, .b = 255};
const SDL_Color bgiLIGHTGREEN   = {.r = 85, .g = 255, .b = 85};
const SDL_Color bgiLIGHTCYAN    = {.r = 85, .g = 255, .b = 255};
const SDL_Color bgiLIGHTRED     = {.r = 255, .g = 85, .b = 85};
const SDL_Color bgiLIGHTMAGENTA = {.r = 255, .g = 85, .b = 255};
const SDL_Color bgiYELLOW       = {.r = 255, .g = 255, .b = 85};
const SDL_Color bgiBRIGHTWHITE  = {.r = 255, .g = 255, .b = 255};

SDL_Color bgiPalette[16];

void initPalette(SDL_Color (&palette)[16])
{
    // initialize full BGI palette
    palette[0] = bgiBLACK;
    palette[1] = bgiBLUE;
    palette[2] = bgiGREEN;
    palette[3] = bgiCYAN;
    palette[4] = bgiRED;
    palette[5] = bgiMAGENTA;
    palette[6] = bgiBROWN;
    palette[7] = bgiWHITE;
    palette[8] = bgiGRAY;
    palette[9] = bgiLIGHTBLUE;
    palette[10] = bgiLIGHTGREEN;
    palette[11] = bgiLIGHTCYAN;
    palette[12] = bgiLIGHTRED;
    palette[13] = bgiLIGHTMAGENTA;
    palette[14] = bgiYELLOW;
    palette[15] = bgiBRIGHTWHITE;
}

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


int main(int argc, const char * argv[]) {
    
    initPalette(bgiPalette);
    std::cout << "Hello, World!\n" << std::endl;
    std::cout << (int)bgiPalette[7].r << std::endl;
    std::cout << (int)bgiPalette[7].g << std::endl;
    std::cout << (int)bgiPalette[7].b << std::endl;
    
    return 0;
}
