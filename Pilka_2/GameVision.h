#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Position.h"
#include "Map.h"
#include "GameEngine.h"

using namespace sf;
using namespace std;

class GameVision
{
private:
	GameEngine * game;
	RenderWindow * window;

public:
	GameVision();

	void draw_dot(Position const p);

	void draw_line(Position const p1, Position  const p2);

	void init_background();

	void init_map();

	void start_game();

	void one_tick();

	void prepare_label();

	void eng_game(GameStage situation);

	void starting_screen();
};

