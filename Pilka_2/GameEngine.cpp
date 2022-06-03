#include "GameEngine.h"


GameEngine::GameEngine(std::string lab1, std::string lab2)
{
	this->game_map = new Map();
	this->player_1_label = lab1;
	this->player_2_label = lab2;
	this->player = this->get_game_map()->get_player();

}

GameEngine::~GameEngine() {
	delete this->game_map;
}

GameStage GameEngine::react_on_move(Orientation pos)
{
	GameStage situation = this->get_game_map()->move_ball(pos);
	switch (situation) {
	case DEFEAT:
		return DEFEAT;
	case WIN:
		return WIN;
	case SWITCH:
		this->get_game_map()->switch_players();
		this->player = this->get_game_map()->get_player();
		return SWITCH;
	case CONT:
		return CONT;
	}
}
