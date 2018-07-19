#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
        char c;
        int sprites = 0;
        int window_size = 0;
        int sprite_size = 0; 
        char filename[100];
        while ((c = getopt(argc, argv, "w:s:f:")) != -1) {
                switch (c) {
                        case 'w':
                                window_size = atoi(optarg);
                                break;
                        case 's':
                                sprite_size = atoi(optarg);
                                break;
                        case 'f':
                                strcpy(filename, optarg);
                                break;
                }
        }
        if (window_size == 0) window_size = 300;
        if (sprite_size == 0) sprite_size = 300;

        bool quit = false;
        SDL_Event input;
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG);

        SDL_Window* window = SDL_CreateWindow("Sprite Render",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        window_size,
                        window_size,
                        SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Texture* spriteSheet = IMG_LoadTexture(renderer, filename);
        SDL_Rect windowRect = {0, 0, sprite_size, sprite_size};

        SDL_Rect textureRect;
        textureRect.x = 0;
        textureRect.y = 0;
        SDL_QueryTexture(spriteSheet, NULL, NULL, &textureRect.w, &textureRect.h);
        sprites = textureRect.w / textureRect.h;
        textureRect.w /= sprites;


        while (!quit) {
                while (SDL_PollEvent(&input) > 0)
                {
                        if (input.type == SDL_QUIT) quit = true;
                }

                int totalFrames = sprites;
                int delayPerFrame = 100;
                int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
                textureRect.x = frame * textureRect.w;

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);

                SDL_RenderCopy(renderer, spriteSheet, &textureRect, &windowRect);
                SDL_RenderPresent(renderer);
        }
        SDL_DestroyTexture(spriteSheet);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
}
