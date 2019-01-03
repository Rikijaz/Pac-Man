// main.cpp : Defines the entry point for the program

#include "Game.h"
#include "Debug.h"

int main(int argc, char* args[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;

	//_CrtDumpMemoryLeaks();

	return 0;
}