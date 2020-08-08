#include "Tetoris_util.h"
#include <memory>

namespace tetoris {

	class Tetoris_board {
	private:
		int board[BOARD_SIZE_V][BOARD_SIZE_H];
	public:
		Tetoris_board();
	};

	Tetoris_board::Tetoris_board() {
		rep(i, BOARD_SIZE_V) {
			memset(board[i], 0, sizeof(int)*BOARD_SIZE_H);
		}
	}

}