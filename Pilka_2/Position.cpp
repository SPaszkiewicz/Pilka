#include "Position.h"

Position::Position(LineTypes types[8])
{
	this->up_line = types[0];
	this->up_right_line = types[1];
	this->right_line = types[2];
	this->down_right_line = types[3];
	this->down_line = types[4];
	this->down_left_line = types[5];
	this->left_line = types[6];
	this->up_left_line = types[7];
	this->is_ball = false;
	this->was_used = false;
	this->x_pos = 0.0f;
	this->y_pos = 0.0f;
}

Position::Position(LineTypes types[8], bool wall, float x, float y)
{
	this->up_line = types[0];
	this->up_right_line = types[1];
	this->right_line = types[2];
	this->down_right_line = types[3];
	this->down_line = types[4];
	this->down_left_line = types[5];
	this->left_line = types[6];
	this->up_left_line = types[7];
	this->is_ball = false;
	this->was_used = wall;
	this->x_pos = x;
	this->y_pos = y;
}


Position::Position()
{
	this->up_line = NONE;
	this->up_right_line = NONE;
	this->right_line = NONE;
	this->down_right_line = NONE;
	this->down_line = NONE;
	this->down_left_line = NONE;
	this->left_line = NONE;
	this->up_left_line = NONE;
	this->is_ball = false;
	this->was_used = false;
}

LineTypes Position::get_position_type(Orientation pos) const
{
	switch (pos) {
	case UP:
		return this->up_line;
	case DOWN:
		return this->down_line;
	case LEFT:
		return this->left_line;
	case RIGHT:
		return this->right_line;
	case UP_LEFT:
		return this->up_left_line;
	case UP_RIGHT:
		return this->up_right_line;
	case DOWN_LEFT:
		return this->down_left_line;
	case DOWN_RIGHT:
		return this->down_right_line;
	default:
		return this->up_line;
	}
}

void Position::set_position_type(Orientation pos, LineTypes new_type)
{
	switch (pos) {
	case UP:
		this->up_line = new_type;
		break;
	case DOWN:
		this->down_line = new_type;
		break;
	case LEFT:
		this->left_line = new_type;
		break;
	case RIGHT:
		this->right_line = new_type;
		break;
	case UP_LEFT:
		this->up_left_line = new_type;
		break;
	case UP_RIGHT:
		this->up_right_line = new_type;
		break;
	case DOWN_LEFT:
		this->down_left_line = new_type;
		break;
	case DOWN_RIGHT:
		this->down_right_line = new_type;
		break;
	default:
		this->up_line = new_type;
		break;
	}
}

bool Position::can_escape() const
{
	return (this->up_line == FREE || this->down_line == FREE || this->right_line == FREE || this->left_line == FREE || 
		   this->up_right_line == FREE || this->up_left_line == FREE || this->down_right_line == FREE || this->down_left_line == FREE);
}

//Position* Position::get_neigh(Orientation pos) const
//{
//	switch (pos) {
//	case UP:
//		return this->up_neigh;
//	case DOWN:
//		return this->down_neigh;
//	case LEFT:
//		return this->left_neigh;
//	case RIGHT:
//		return this->right_neigh;
//	case UP_LEFT:
//		return this->up_left_neigh;
//	case UP_RIGHT:
//		return this->up_right_neigh;
//	case DOWN_LEFT:
//		return this->down_left_neigh;
//	case DOWN_RIGHT:
//		return this->down_right_neigh;
//	default:
//		return nullptr;
//	}
//}
