#include "Tetoris_util.h"
#include <map>

namespace tetoris {

	enum MINO_ID{ NONE, Z, S, L, J, T, O, I };

	class TetoriMino {
	private:
		int x, y;
		int rotate;
		int graph[GRAPH_SIZE][GRAPH_SIZE];

		static std::map<MINO_ID, int> mino_graph;
		
	public:
		TetoriMino(MINO_ID id);

	};

	TetoriMino::TetoriMino(MINO_ID) {
		x = 4;
		y = 0;
		rotate = 0;
	}
}