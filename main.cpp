#include "Game.h"

int main(int argc, char* argv[])
{
	if (argc == 1) {
		Game(GameMode::Standard).start();
	}
	else if ((argc == 2 && strcmp(argv[1],"-save") == 0) || (argc == 3 && strcmp(argv[1], "-save") == 0 && strcmp(argv[2], "-silent") == 0)) {
		Game(GameMode::Record).start();
	}
	else if (argc == 2 && strcmp(argv[1],"-load") == 0) {
		Game(GameMode::Standard).startLoadedGame();
	}
	else if (argc == 3 && strcmp(argv[1], "-load") == 0 && strcmp(argv[2], "-silent") == 0) {
		Game(GameMode::Standard).startSilentGame();
	}
	else {
		//Usage print of the command
		std::cout << "Usage Case: ThunderBirds.exe -load|-save [ -silent ]";
	}
	return 0;
}