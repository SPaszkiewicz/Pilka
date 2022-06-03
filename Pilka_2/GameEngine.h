#pragma once
#include "Map.h"
#include "Position.h"
#include <iostream>

class GameEngine
{
private:
	Map * game_map;
	std::string player_1_label;
	std::string player_2_label;
	bool player;

public:
	GameEngine(std::string lab1="P1", std::string lab2 = "P2");

	~GameEngine();

	Map* get_game_map() const {
		return this->game_map;
	}
	
	GameStage react_on_move(Orientation pos);

	std::string get_player_1_label() const {
		return player_1_label;
	}

	std::string get_player_2_label() {
		return player_2_label;
	}

	bool get_player() {
		return this->player;
	}
};

