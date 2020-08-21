#pragma once

#include "Tetoris_board.hpp"
#include <map>

namespace tetoris {

	enum MINO_ID{ NONE, Z, S, L, J, T, O, I };

	class TetoriMino {
	private:
		MINO_ID id;
		pii cordinate;
		int graph[GRAPH_SIZE][GRAPH_SIZE];
	public:
		void init(MINO_ID id);
		pii getCordiante();
		MINO_ID getId();
		void getGraph(int graphBuf[GRAPH_SIZE][GRAPH_SIZE]);
		void move(int bitflag, Tetoris_board& board);
	};

}