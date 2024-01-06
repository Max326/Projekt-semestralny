#include "Game.h"

int main() {
    Game game;

	game.Start();

	return 0;
}

/* BUILDOWANIE I ODPALANIE:
jeśli nie ma folderu build:
(w głównym folderze projektu)
mkdir build && cd build
cmake ..
make
./MyExecutable

jeśli folder build istnieje
cd build
cmake ..
make
./MyExecutable
*/ 