#pragma once

#include "Tetoris_util.h"
#include <memory>

namespace tetoris {

	class Tetoris_board {
	private:
		int board[BOARD_MAX_SIZE_V][BOARD_SIZE_H];
	public:
		Tetoris_board();
		void get_board(int board_buf[BOARD_MAX_SIZE_V][BOARD_SIZE_H]);
		int checkLine();
	};

}
