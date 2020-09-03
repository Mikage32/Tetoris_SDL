#include "TetoriMino.hpp"

namespace tetoris {

	int mino_graph[8][5][5] = {
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 1, 1, 0, 0},
			{0, 0, 1, 1, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 1, 0},
			{0, 1, 1, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 1, 0},
			{0, 1, 1, 1, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 1, 0, 0, 0},
			{0, 1, 1, 1, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 1, 1, 1, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 1, 0},
			{0, 0, 1, 1, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 1, 1, 1, 1},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}
		}
	};

	void TetoriMino::init(MINO_ID id) {
		this->id = id;
		cordinate = pii(4, 0);

		rep(i, GRAPH_SIZE) {
			rep(j, GRAPH_SIZE) {
				graph[i][j] = mino_graph[id][i][j] * id;
			}
		}
	}

	pii TetoriMino::getCordiante() {
		return cordinate;
	}

	MINO_ID TetoriMino::getId() {
		return id;
	}

	void TetoriMino::getGraph(int graphBuf[GRAPH_SIZE][GRAPH_SIZE]) {
		rep(i, GRAPH_SIZE) {
			memcpy(graphBuf[i], graph[i], sizeof(int)*GRAPH_SIZE);
		}
	}

	void TetoriMino::move(int bitflag, Tetoris_board& Tetoboard) {
		int rotate_flag = (bitflag&MOVE_ROTATE_L ? -1 : 0) + (bitflag&MOVE_ROTATE_R ? 1 : 0);
		int rotate_graph[GRAPH_SIZE][GRAPH_SIZE];
		rep(i, GRAPH_SIZE) {
			rep(j, GRAPH_SIZE) {
				switch (rotate_flag) {
				case 0:
					rotate_graph[i][j] = graph[i][j];
					break;
				case 1:
					rotate_graph[i][j] = graph[j][GRAPH_SIZE - 1 - i];
					break;
				case -1:
					rotate_graph[i][j] = graph[GRAPH_SIZE - 1 - j][i];
					break;
				}
			}
		}

		int board[BOARD_MAX_SIZE_V][BOARD_SIZE_H];
		Tetoboard.get_board(board);

		bool ok = true;
		rep(i, GRAPH_SIZE) {
			if (cordinate.second - 2 + i < 0 || cordinate.second - 2 + i >= BOARD_MAX_SIZE_V) continue;
			rep(j, GRAPH_SIZE) {
				if (cordinate.first - 2 + j < 0 || cordinate.first - 2 + j >= BOARD_SIZE_H) continue;

				if (rotate_graph[i][j] != 0 && board[cordinate.second - 2 + i][cordinate.first - 2 + i] != 0) {
					ok = false;
					break;
				}
			}

			if (!ok) {
				break;
			}
		}

		if (ok) {
			rep(i, GRAPH_SIZE) {
				rep(j, GRAPH_SIZE) {
					graph[i][j] = rotate_graph[i][j];
				}
			}
		}

		int x = (bitflag&MOVE_L ? -1 : 0) + (bitflag&MOVE_R ? 1 : 0);
		int y = (bitflag&MOVE_SOFTDROP ? 1 : 0);

		rep(i, GRAPH_SIZE) {
			rep(j, GRAPH_SIZE) {
				if (BOARD_MAX_SIZE_V - BOARD_SIZE_V + cordinate.second + y - 2 + i >= 0 && BOARD_MAX_SIZE_V - BOARD_SIZE_V + cordinate.second + y - 2 + i < BOARD_MAX_SIZE_V
					&& cordinate.first + x - 2 + j >= 0 && cordinate.first + x - 2 + j < BOARD_SIZE_H) {

					if (graph[i][j] != 0 && board[BOARD_MAX_SIZE_V - BOARD_SIZE_V + cordinate.second + y - 2 + i][cordinate.first + x - 2 + i] != 0) {
						ok = false;
						break;
					}
				}
				else if(graph[i][j] != 0){
					ok = false;
					break;
				}
			}

			if (!ok) break;
		}

		if (ok) {
			cordinate.first += x;
			cordinate.second += y;
		}
	}

}