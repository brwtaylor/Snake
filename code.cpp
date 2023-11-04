#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <emscripten.h>
#include <vector>
#include <random>
#include <iostream>

Uint32 lastTime = 0;

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

TTF_Font* font = nullptr;
SDL_Color textColor = { 255, 255, 255 };

enum class GameState {
    START,
    RUNNING,
    GAMEOVER
};

class Snake {
private:
  int size = 1;
public:
  inline void Update(float deltaTime) {

  }
  inline void Draw() {

  }
  inline void Turn() {

  }

}

class food {
  

}

EM_JS(void, saveScore, (int highScore), {
    localStorage.setItem('highScore', highScore);
});

EM_JS(int, getScore, (), {
    var highScore = localStorage.getItem('highScore');
    return highScore;
});


class Game {
public:
    GameState gameState = GameState::START;
private:
  Snake snake;
  int score = 0;
  int highScore = getScore();

  inline void StartGame() {
    gameState = GameState::RUNNING;
    score = 0;
  }
}

Game game;

extern "C" void mainloop() {
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    game.HandleInput();

    if (game.gameState == GameState::RUNNING) { // Ensure the game updates only in RUNNING state
        game.Update(deltaTime);
    }

    game.Render();
}

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (TTF_Init() == -1) std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;

    font = TTF_OpenFont("assets/ArcadeFont.ttf", 28);
    if (!font) std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;

    emscripten_set_main_loop(mainloop, 0, 1);

    SDL_DestroyRenderer(renderer);
    return 0;
}


