#include <SDL.h>
#include <map>

#define MOVE_R 1
#define MOVE_L 2
#define MOVE_SOFTDROP 4
#define MOVE_HARDDROP 8
#define MOVE_ROTATE_R 16
#define MOVE_ROTATE_L 32
#define MOVE_HOLD 64

namespace tetoris {
	
	class Tetoris {
	private:
		SDL_Window* gameWindow;
		SDL_Renderer* renderer;
		bool isRunning;
		unsigned int bitflag;
		std::map<int, int> keymap;

		void processInput();
		void update();
		void generateOutput();
	public:
		bool initialize();
		void shutdown();
		void runLoop();
	};

	bool Tetoris::initialize() {
		int initflag = SDL_Init(SDL_INIT_VIDEO);
		if (initflag != 0) {
			SDL_Log("SDLの初期化に失敗しました: %s", SDL_GetError());
			return false;
		}

		gameWindow = SDL_CreateWindow("Tetoris", NULL, NULL, NULL, NULL, SDL_WINDOW_FULLSCREEN_DESKTOP);
		if (!gameWindow) {
			SDL_Log("ウィンドウの生成に失敗しました: %s", SDL_GetError());
			return false;
		}

		renderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!renderer) {
			SDL_Log("レンダラーの生成に失敗しました: %s", SDL_GetError());
			return false;
		}

		keymap[SDL_SCANCODE_RIGHT] = MOVE_R;
		keymap[SDL_SCANCODE_LEFT] = MOVE_L;
		keymap[SDL_SCANCODE_DOWN] = MOVE_SOFTDROP;
		keymap[SDL_SCANCODE_UP] = MOVE_ROTATE_R;
		keymap[SDL_SCANCODE_Z] = MOVE_ROTATE_L;
		keymap[SDL_SCANCODE_X] = MOVE_ROTATE_R;
		keymap[SDL_SCANCODE_C] = MOVE_HOLD;
		keymap[SDL_SCANCODE_LSHIFT] = MOVE_HOLD;
		keymap[SDL_SCANCODE_SPACE] = MOVE_HARDDROP;

		keymap[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] = MOVE_R;
		keymap[SDL_CONTROLLER_BUTTON_DPAD_LEFT] = MOVE_L;
		keymap[SDL_CONTROLLER_BUTTON_DPAD_DOWN] = MOVE_SOFTDROP;
		keymap[SDL_CONTROLLER_BUTTON_LEFTSHOULDER] = MOVE_ROTATE_L;
		keymap[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] = MOVE_ROTATE_R;
		keymap[SDL_CONTROLLER_BUTTON_A] = MOVE_HOLD;
		keymap[SDL_CONTROLLER_BUTTON_DPAD_DOWN] = MOVE_HARDDROP;

		bitflag = 0;
		isRunning = true;

		return true;
	}

	void Tetoris::shutdown() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(gameWindow);
		SDL_Quit();
	}

	void Tetoris::runLoop() {
		while (isRunning) {
			processInput();
			update();
			generateOutput();
		}
	}

	void Tetoris::processInput() {
		SDL_Event event;
		bitflag |= MOVE_ROTATE_R | MOVE_ROTATE_L;
		bitflag ^= MOVE_ROTATE_R | MOVE_ROTATE_L;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				bitflag |= keymap[event.key.keysym.scancode];
				break;
			case SDL_KEYUP:
				bitflag ^= bitflag & keymap[event.key.keysym.scancode];
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				bitflag |= keymap[event.cbutton.button];
				break;
			case SDL_CONTROLLERBUTTONUP:
				bitflag ^= bitflag & keymap[event.cbutton.button];
				break;
			case SDL_QUIT:
				isRunning = false;
				break;
			}
		}

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE]) {
			isRunning = false;
		}
	}

	void Tetoris::update() {

	}

	void Tetoris::generateOutput() {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
}