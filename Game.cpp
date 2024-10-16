#include "Game.h"

double Game::currentTime = 0.0;
double Game::lastTime = 0.0;

double Game::dt = 1.0 / 60.0;

void Game::updateDT() {
	currentTime = glfwGetTime();
	dt = currentTime - lastTime;
	lastTime = currentTime;
}