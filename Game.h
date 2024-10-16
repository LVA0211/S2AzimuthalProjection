#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include<GLFW/glfw3.h>

static class Game {
private:
	static double lastTime;
	static double currentTime;
public:
	static double dt;
	static void updateDT();
};

#endif