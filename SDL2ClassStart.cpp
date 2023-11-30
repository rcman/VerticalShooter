#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class VerticalShootingGame {
public:
    VerticalShootingGame(int screenWidth, int screenHeight)
        : screenWidth(screenWidth), screenHeight(screenHeight) {}

    // Initialize SDL, create window and renderer
    bool initialize();

    // Load game assets
    bool loadMedia();

    // Handle keyboard input
    void handleInput();

    // Update game state
    void update();

    // Render the game
    void render();

    // Clean up resources
    void close();

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Texture* playerTexture = nullptr;
    SDL_Texture* bulletTexture = nullptr;

    int playerX, playerY;
    int playerSpeed;

    std::vector<std::pair<int, int>> bullets;  // Vector to store bullet positions

    int screenWidth, screenHeight;
};

bool VerticalShootingGame::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Vertical Shooting Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool VerticalShootingGame::loadMedia() {
    // Load player texture
    // Load bullet texture
    // ...

    return true;
}

void VerticalShootingGame::handleInput() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            // Handle quit event
        }
        else if (e.type == SDL_KEYDOWN) {
            // Handle keydown event (e.g., move player or shoot)
        }
    }
}

void VerticalShootingGame::update() {
    // Update player position based on input
    // Update bullet positions
    // ...
}

void VerticalShootingGame::render() {
    // Clear the renderer
    SDL_RenderClear(renderer);

    // Render player
    // Render bullets
    // ...

    // Present the renderer
    SDL_RenderPresent(renderer);
}

void VerticalShootingGame::close() {
    // Cleanup resources (textures, renderer, window)
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[]) {
    VerticalShootingGame game(800, 600);

    if (!game.initialize()) {
        printf("Failed to initialize!\n");
        return -1;
    }

    if (!game.loadMedia()) {
        printf("Failed to load media!\n");
        return -1;
    }

    bool quit = false;
    while (!quit) {
        game.handleInput();
        game.update();
        game.render();
    }

    game.close();

    return 0;
}
