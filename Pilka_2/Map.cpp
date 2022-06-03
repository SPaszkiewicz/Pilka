#include "Map.h"
#include <iostream>

Map::Map()
{

	this->player = true;
	this->ball_x = 4;
	this->ball_y = 6;
	this->field = new Position* [this->height];
	for (int i = 0; i < this->height; i++) {
		this->field[i] = new Position[this->width];
	}
	this->field[6][4].set_is_ball(true);

	LineTypes empty_field[8] = { FREE, FREE, FREE, FREE, FREE, FREE, FREE, FREE };
	LineTypes right_wall[8] = {LINE, NONE, NONE, NONE, LINE, FREE, FREE, FREE};
	LineTypes left_wall[8] = {LINE, FREE, FREE, FREE, LINE, NONE, NONE, NONE};
	LineTypes upper_wall[8] = { NONE, NONE, LINE, FREE, FREE, FREE, LINE, NONE };
	LineTypes lower_wall[8] = { FREE, FREE, LINE, NONE,  NONE, NONE, LINE, FREE };

	LineTypes left_upper_corner[8] = { NONE, NONE, LINE, FREE, LINE, NONE, NONE, NONE };
	LineTypes right_upper_corner[8] = { NONE, NONE, NONE, NONE, LINE, FREE, LINE, NONE };
	LineTypes left_lower_corner[8] = { LINE, FREE, LINE, NONE, NONE, NONE, NONE, NONE };
	LineTypes right_lower_corner[8] = { LINE, NONE, NONE, NONE, NONE, NONE, LINE, FREE };

	LineTypes left_upper_post[8] = { LINE, FREE, FREE, FREE, FREE, FREE, LINE, NONE };
	LineTypes right_upper_post[8] = { LINE, NONE, LINE, FREE, FREE, FREE, FREE, FREE };
	LineTypes left_lower_post[8] = { FREE, FREE, FREE, FREE, LINE, NONE, LINE, FREE };
	LineTypes right_lower_post[8] = { FREE, FREE, LINE, NONE, LINE, FREE, FREE, FREE };

	int x_index = 12;
	this->field[x_index][0] = Position(empty_field, false, 50, 50);
	this->field[x_index][1] = Position(empty_field, false, 100, 50);
	this->field[x_index][2] = Position(empty_field, false, 150, 50);
	this->field[x_index][3] = Position(left_upper_corner, true, 200, 50);
	this->field[x_index][4] = Position(upper_wall, true, 250, 50);
	this->field[x_index][5] = Position(right_upper_corner, true, 300, 50);
	this->field[x_index][6] = Position(empty_field, false, 350, 50);
	this->field[x_index][7] = Position(empty_field, false, 400, 50);
	this->field[x_index][8] = Position(empty_field, false, 450, 50);

	this->field[11][0] = Position(left_upper_corner, true, 50, 100);
	this->field[11][1] = Position(upper_wall, true, 100, 100);
	this->field[11][2] = Position(upper_wall, true, 150, 100);
	this->field[11][3] = Position(left_upper_post, true, 200, 100);
	this->field[11][4] = Position(empty_field, false, 250, 100);
	this->field[11][5] = Position(right_upper_post, true, 300, 100);
	this->field[11][6] = Position(upper_wall, true, 350, 100);
	this->field[11][7] = Position(upper_wall, true, 400, 100);
	this->field[11][8] = Position(right_upper_corner, true, 450, 100);

	this->field[0][0] = Position(empty_field, false, 50, 650);
	this->field[0][1] = Position(empty_field, false, 100, 650);
	this->field[0][2] = Position(empty_field, false, 150, 650);
	this->field[0][3] = Position(left_lower_corner, true, 200, 650);
	this->field[0][4] = Position(lower_wall, true, 250, 650);
	this->field[0][5] = Position(right_lower_corner, true, 300, 650);
	this->field[0][6] = Position(empty_field, false, 350, 650);
	this->field[0][7] = Position(empty_field, false, 400, 650);
	this->field[0][8] = Position(empty_field, false, 450, 650);

	this->field[1][0] = Position(left_lower_corner, true, 50, 600);
	this->field[1][1] = Position(lower_wall, true, 100, 600);
	this->field[1][2] = Position(lower_wall, true, 150, 600);
	this->field[1][3] = Position(left_lower_post, true, 200, 600);
	this->field[1][4] = Position(empty_field, false, 250, 600);
	this->field[1][5] = Position(right_lower_post, true, 300, 600);
	this->field[1][6] = Position(lower_wall, true, 350, 600);
	this->field[1][7] = Position(lower_wall, true, 400, 600);
	this->field[1][8] = Position(right_lower_corner, true, 450, 600);

	for (int i = 2; i < this->height - 2; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (j == this->width - 1) {
				this->field[i][j] = Position(right_wall, true, (j+1)*50, 700 - (i + 1) * 50);
			}
			else if (j == 0) {
				this->field[i][j] = Position(left_wall, true, (j + 1) * 50, 700 - (i + 1) * 50);
			}
			else {
				this->field[i][j] = Position(empty_field, false, (j + 1) * 50, 700 - (i + 1) * 50);
			}
		}
	}
}

Map::~Map()
{
	for (int i = 0; i < this->height; i++) {
		delete[] this->field[i];
	}
	delete[] this->field;
}

void Map::print_map_state() const
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (this->ball_x == j && this->ball_y == i) {
				std::cout << "2" << " ";
			}
			else {
				std::cout << this->field[i][j].get_was_used() << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << this->ball_x << " " << this->ball_y << std::endl;
}

GameStage Map::move_ball(Orientation move)
{
	int x, y;
	Orientation diff_pos;
	switch (move) {
	case UP:
		x = 0; y = 1;
		diff_pos = DOWN;
		break;
	case DOWN:
		x = 0; y = -1;
		diff_pos = UP;
		break;
	case LEFT:
		x = -1; y = 0;
		diff_pos = RIGHT;
		break;
	case RIGHT:
		x = 1; y = 0;
		diff_pos = LEFT;
		break;
	case UP_LEFT:
		x = -1; y = 1;
		diff_pos = DOWN_RIGHT;
		break;
	case UP_RIGHT:
		x = 1; y = 1;
		diff_pos = DOWN_LEFT;
		break;
	case DOWN_LEFT:
		x = -1; y = -1;
		diff_pos = UP_RIGHT;
		break;
	case DOWN_RIGHT:
		x = 1; y = -1;
		diff_pos = UP_LEFT;
		break;
	default:
		x = 0; y = 0;
		diff_pos = UP;
		break;
	}

	switch (this->field[this->ball_y][this->ball_x].get_position_type(move)) {
	case NONE:
		std::cout << "Cannot reach none" << std::endl;
		return CONT;
	case LINE:
		std::cout << "Cannot reach line" << std::endl;
		return CONT;
	case FREE:
		this->field[this->ball_y][this->ball_x].set_position_type(move, LINE);
		this->field[this->ball_y][this->ball_x].set_is_ball(false);
		this->ball_y += y;
		this->ball_x += x;
		this->field[this->ball_y][this->ball_x].set_position_type(diff_pos, LINE);
		this->field[this->ball_y][this->ball_x].set_is_ball(true);

		if (this->field[this->ball_y][this->ball_x].get_was_used() == false) 
		{
			this->field[this->ball_y][this->ball_x].set_was_used(true);
			return SWITCH;
		}
		else 
		{
			if (this->is_win() == true) {
				return WIN;
			}
			else if (this->field[this->ball_y][this->ball_x].can_escape() == false) {
				return DEFEAT;
			}
			else {
				return CONT;
			}
		}
	}

}

bool Map::is_win() const
{
	if (this->ball_y == this->height - 1 || this->ball_y == 0) {
		return true;
	}
	return false;
}

void Map::switch_players()
{
	if (this->player == true) {
		this->player = false;
	}
	else {
		this->player = true;
	}
}

bool Map::get_player()
{
	return this->player;
}

Position Map::get_point(int x, int y)
{
	return this->field[y][x];
}

int Map::get_ball_y() const
{
	return this->ball_y;
}
