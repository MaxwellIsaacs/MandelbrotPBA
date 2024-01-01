#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* define window and iteration parameters */
const int WIDTH = 800; // window width
const int HEIGHT = 600; // window height
int maxIterations = 185; // max iterations, can be adjusted for detail

/* zoom and pan variables */
double zoom = 1.0; // zoom factor
double offsetX = -0.5; // x offset for centering
double offsetY = 0.0; // y offset for centering

/* mouse drag state */
int lastX = 0; // last recorded mouse x position
int lastY = 0; // last recorded mouse y position
bool dragging = false; // dragging state

/*
* @brief initializes SDL, creates window, renderer, and texture
* @params window pointer, renderer pointer, texture pointer
* @return success or failure
*/
int initSDL(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    *window = SDL_CreateWindow("Mandelbrot Set", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    *texture = SDL_CreateTexture(*renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
    if (*texture == NULL) {
        printf("Texture could not be created! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    return 0;  // success
}

/*
* @brief draws mandelbrot set
* @params renderer pointer, texture pointer
* @return void
*/
void drawMandelbrot(SDL_Renderer *renderer, SDL_Texture *texture) {
    Uint32 *buffer = (Uint32 *)malloc(WIDTH * HEIGHT * sizeof(Uint32));
    if (buffer == NULL) {
        fprintf(stderr, "Unable to allocate buffer\n");
        exit(1);
    }

    for (int px = 0; px < WIDTH; px++) {
        for (int py = 0; py < HEIGHT; py++) {
            double x0 = ((double)px / WIDTH) * (4.0 / zoom) - (2.0 / zoom) + offsetX;
            double y0 = ((double)py / HEIGHT) * (2.0 / zoom) - (1.0 / zoom) + offsetY;

            double x = 0;
            double y = 0;
            int iteration = 0;

            while (x*x + y*y <= 4 && iteration < maxIterations) {
                double xtemp = x*x - y*y + x0;
                y = 2*x*y + y0;
                x = xtemp;
                iteration++;
            }

            // Set color based on whether point is in the Mandelbrot set
            if (iteration == maxIterations) {
                buffer[(py * WIDTH) + px] = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888), 0, 0, 0); // Mandelbrot set points are black
            } else {
                buffer[(py * WIDTH) + px] = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888), 255, 255, 255); // Other points are white
            }
        }
    }

    SDL_UpdateTexture(texture, NULL, buffer, WIDTH * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    free(buffer);
}

/*
* @brief main function, entry point of the program
* @params command line arguments
* @return exit status
*/
int main(int argc, char* args[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Event event;
    bool quit = false;

    if (initSDL(&window, &renderer, &texture)) {
        return 1; // SDL Initialization failed
    }

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                dragging = true;
                SDL_GetMouseState(&lastX, &lastY);
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                dragging = false;
            } else if (event.type == SDL_MOUSEMOTION && dragging) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                offsetX += (mouseX - lastX) / zoom;
                offsetY += (mouseY - lastY) / zoom;
                lastX = mouseX;
                lastY = mouseY;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_q: // zoom in
                        zoom *= 1.1;
                        break;
                    case SDLK_z: // zoom out
                        zoom /= 1.1;
                        break;
                    case SDLK_w: // shift up
                        offsetY -= .5 / zoom;
                        break;
                    case SDLK_s: // shift down
                        offsetY += .5 / zoom;
                        break;
                    case SDLK_a: // shift left
                        offsetX -= .5 / zoom;
                        break;
                    case SDLK_d: // shift right
                        offsetX += .5 / zoom;
                        break;
                }
            }
        }

        drawMandelbrot(renderer, texture);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
