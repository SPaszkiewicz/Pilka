#pragma once
#include "Position.h"

enum GameStage {
	BEGIN,
	CONT,
	SWITCH,
	DEFEAT,
	WIN
};


class Map
{
public:
	Map();

	~Map();

	void print_map_state() const;

	GameStage move_ball(Orientation move);

	bool is_win() const;

	void switch_players();

	bool get_player();

	Position get_point(int x, int y);

	int get_ball_y() const;

private:
	Position ** field;
	int const height = 13;
	int const width = 9;
	int ball_x;
	int ball_y;
	bool player;
};

