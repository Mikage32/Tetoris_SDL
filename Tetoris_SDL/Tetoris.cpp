#include "Tetoris.hpp"

namespace tetoris {

	bool Tetoris::initialize() {
		int initflag = SDL_Init(SDL_INIT_VIDEO);
		if (initflag != 0) {
			SDL_Log("SDLの初期化に失敗しました: %s", SDL_GetError());
			return false;
		}

		gameWindow = SDL_CreateWindow("Tetoris", 100, 100, DISPLAYSIZE_H, DISPLAYSIZE_V, NULL);
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

		colorMap[NONE] = { 133, 133, 133, 255 };
		colorMap[T] = { 150, 50, 200, 255 };
		colorMap[Z] = { 200,50,50,255 };
		colorMap[S] = { 50,200,100,255 };
		colorMap[L] = { 80,80,200,255 };
		colorMap[J] = { 200,130,50,255 };
		colorMap[O] = { 200,200,50,255 };
		colorMap[I] = { 50,200,200,255 };

		bitflag = 0;

		MinoSeed.l_0 = rnd() % 7;
		MinoSeed.k = rnd() % 6;
		MinoSeed.i = 0;
		NextQue.push_back(rnd() % 7);
		rep(i, 7) NextQue.push_back(next_mino());
		popNext();
		holdMino.init(NONE);

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

	int Tetoris::next_mino() {
		++MinoSeed.i;
		return (NextQue.back() + (MinoSeed.l_0 + MinoSeed.k*(MinoSeed.i / 7)) % 6 + 1) % 7;
	}

	void Tetoris::popNext() {
		MainMino.init(static_cast<MINO_ID>(NextQue.front() + 1));
		NextQue.pop_front();
	}

	void Tetoris::update() {
		processInput();
		MainMino.move(bitflag, mainBoard);
		//ここに追加

		mainBoard.checkLine();
		generateOutput();
	}

	void Tetoris::generateOutput() {
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
		SDL_RenderClear(renderer);

		int boardBuf[BOARD_MAX_SIZE_V][BOARD_SIZE_H];
		mainBoard.get_board(boardBuf);
		SDL_Rect cell;
		cell.x = (DISPLAYSIZE_H - DISPLAYSIZE_V) / 2;
		cell.y = 0;
		cell.h = DISPLAYSIZE_V / 20;
		cell.w = cell.h;
		REP(i, BOARD_MAX_SIZE_V - BOARD_SIZE_V, BOARD_MAX_SIZE_V) {
			rep(j, BOARD_SIZE_H) {
				color c = colorMap[static_cast<MINO_ID>(boardBuf[i][j])];
				SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
				SDL_RenderFillRect(renderer, &cell);

				cell.x += cell.w;
			}

			cell.x -= cell.w * 10;
			cell.y += cell.h;
		}

		int minoBuf[GRAPH_SIZE][GRAPH_SIZE];
		MainMino.getGraph(minoBuf);
		pii cordinate = MainMino.getCordiante();
		cell.x = (DISPLAYSIZE_H - DISPLAYSIZE_V) / 2 + (cordinate.first - 2)*cell.w;
		cell.y = (cordinate.second - 2)*cell.h;
		rep(i, GRAPH_SIZE) {
			if (cordinate.second - 2 + i >= 0 && cordinate.second - 2 + i < BOARD_MAX_SIZE_V - BOARD_SIZE_V) {
				rep(j, GRAPH_SIZE) {
					if (cordinate.first - 2 + j >= 0 && cordinate.first - 2 + j < BOARD_SIZE_H && minoBuf[i][j] != 0) {
						color c = colorMap[MainMino.getId()];
						SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
						SDL_RenderFillRect(renderer, &cell);
					}
					cell.x += cell.w;
				}

				cell.x -= cell.w*GRAPH_SIZE;
			}

			cell.y += cell.h;
		}


		SDL_RenderPresent(renderer);
	}

}

int main(int argc, char* args[]) {
	tetoris::Tetoris game_Tetoris;
	if (game_Tetoris.initialize()) {
		game_Tetoris.runLoop();
		game_Tetoris.shutdown();
	}

	return 0;
}
