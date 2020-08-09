#include "Tetoris_util.h"
#include <memory>

namespace tetoris {

	class Tetoris_board {
	private:
		int board[BOARD_MAX_SIZE_V][BOARD_SIZE_H];
	public:
		Tetoris_board();
		void get_board(int board_buf[BOARD_SIZE_V][BOARD_SIZE_H]);
	};

	Tetoris_board::Tetoris_board() {
		rep(i, BOARD_MAX_SIZE_V) {
			memset(board[i], 0, sizeof(int)*BOARD_SIZE_H);
		}
	}

	void Tetoris_board::get_board(int board_buf[BOARD_SIZE_V][BOARD_SIZE_H]) {
		rep(i, BOARD_SIZE_V) {
			memcpy(board_buf[i], board[i + BOARD_MAX_SIZE_V - BOARD_SIZE_V], sizeof(int)*BOARD_SIZE_H);
		}
	}
}