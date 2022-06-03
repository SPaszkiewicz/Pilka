// Pilka_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Position.h"
#include "Map.h"
#include "GameEngine.h"
#include "GameVision.h"

using namespace sf;
using namespace std;

int main() {
	auto t = GameVision();
	t.start_game();
}
