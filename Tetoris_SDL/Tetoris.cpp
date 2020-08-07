#include "Tetoris.hpp"

int main() {
	tetoris::Tetoris game_Tetoris;
	if (game_Tetoris.initialize()) {
		game_Tetoris.runLoop();
		game_Tetoris.shutdown();
	}

	return 0;
}