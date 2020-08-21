#pragma once

#include <SDL.h>
#include <deque>
#include <vector>
#include <map>
#include <random>
#include "Tetoris_util.h"
#include "Tetoris_board.hpp"
#include "TetoriMino.hpp"

namespace tetoris {
	
	struct seed {
		int l_0;
		int k;
		int i;
	};

	struct color {
		Uint8 r;
		Uint8 g;
		Uint8 b;
		Uint8 a;
	};

	class Tetoris {
	private:
		SDL_Window* gameWindow;
		SDL_Renderer* renderer;

		Tetoris_board mainBoard;
		std::vector<Tetoris_board> subboards;
		TetoriMino MainMino, holdMino;
		std::deque<int> NextQue;
		seed MinoSeed;
		std::random_device rnd;

		std::map<int, int> keymap;
		std::map<MINO_ID, color> colorMap;
		unsigned int bitflag;
		bool isRunning;

		void processInput();
		void popNext();
		int next_mino();
		void update();
		void generateOutput();
	public:
		bool initialize();
		void shutdown();
		void runLoop();
	};

}