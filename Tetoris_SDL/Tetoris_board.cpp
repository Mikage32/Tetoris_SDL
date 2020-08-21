#include "Tetoris_board.hpp"

namespace tetoris {
	
	Tetoris_board::Tetoris_board() {
		rep(i, BOARD_MAX_SIZE_V) {
			memset(board[i], 0, sizeof(int)*BOARD_SIZE_H);
		}
	}

	void Tetoris_board::get_board(int board_buf[BOARD_MAX_SIZE_V][BOARD_SIZE_H]) {
		rep(i, BOARD_MAX_SIZE_V) {
			memcpy(board_buf[i], board[i], sizeof(int)*BOARD_SIZE_H);
		}
	}

	int Tetoris_board::checkLine() {
		int counter = 0;
		REP(i, BOARD_MAX_SIZE_V - BOARD_SIZE_V, BOARD_MAX_SIZE_V) {
			bool flag = true;
			rep(j, BOARD_SIZE_H) {
				if (board[i][j] == 0) {
					flag = false;
					break;
				}
			}

			if (flag) {
				++counter;
				rrep(j, BOARD_MAX_SIZE_V - 1) {
					if (j != 0) memcpy(board[j], board[j - 1], sizeof(int)*BOARD_SIZE_H);
					else memset(board[j], 0, sizeof(int)*BOARD_SIZE_H);
				}
			}
		}

		return counter;
	}

}