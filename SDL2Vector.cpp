#include <SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BULLET_SPEED 5
#define MAX_BULLETS 500

typedef struct {
    float x, y;
    float dx, dy;
    bool active;
} Bullet;

void updateBullet(Bullet *bullet) {
    if (bullet->active) {
        bullet->x += bullet->dx;
        bullet->y += bullet->dy;

        // Check if the bullet is out of bounds
        if (bullet->x < 0 || bullet->x > SCREEN_WIDTH || bullet->y < 0 || bullet->y > SCREEN_HEIGHT) {
            bullet->active = false;
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Bullet Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize bullets
    Bullet bullets[MAX_BULLETS];
    for (int i = 0; i < MAX_BULLETS; ++i) {
        bullets[i].active = false;
    }

    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                // Find an inactive bullet to shoot
                for (int i = 0; i < MAX_BULLETS; ++i) {
                    if (!bullets[i].active) {
                        bullets[i].active = true;
                        bullets[i].x = SCREEN_WIDTH / 2;
                        bullets[i].y = SCREEN_HEIGHT - 20;
                        bullets[i].dx = 0;
                        bullets[i].dy = -BULLET_SPEED;
                        break;
                    }
                }
            }
        }

        // Update bullets
        for (int i = 0; i < MAX_BULLETS; ++i) {
            updateBullet(&bullets[i]);
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw bullets
        for (int i = 0; i < MAX_BULLETS; ++i) {
            if (bullets[i].active) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_Rect bulletRect = { (int)bullets[i].x, (int)bullets[i].y, 5, 10 };
                SDL_RenderFillRect(renderer, &bulletRect);
            }
        }

        // Update the screen
        SDL_RenderPresent(renderer);

        // Cap the frame rate
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
