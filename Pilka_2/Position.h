#pragma once
enum LineTypes {
	LINE, 
	NONE,
	FREE,
};

enum Orientation {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_RIGHT,
	UP_LEFT,
	DOWN_LEFT,
	DOWN_RIGHT
};


class Position
{
public:
	Position(LineTypes types[8]);

	Position(LineTypes types[8], bool wall, float x=0.0f, float y = 0.0f);

	Position();

	bool get_is_ball() const {
		return this->is_ball;
	}

	bool get_was_used() const {
		return this->was_used;
	}

	void set_is_ball(bool opt){
		this->is_ball = opt;
	}

	void set_was_used(bool opt){
		this->was_used = opt;
	}

	float get_x_pos() const {
		return this->x_pos;
	}

	float get_y_pos() const {
		return this->y_pos;
	}

	LineTypes get_position_type(Orientation pos) const;

	void set_position_type(Orientation pos, LineTypes new_type);

	bool can_escape() const;

	//Position * get_neigh(Orientation pos) const;

private:
	LineTypes up_line;
	LineTypes down_line;
	LineTypes left_line;
	LineTypes right_line;
	LineTypes up_right_line;
	LineTypes up_left_line;
	LineTypes down_left_line;
	LineTypes down_right_line;

	float x_pos, y_pos;
	
	//Position *left_neigh;
	//Position* right_neigh;
	//Position* up_neigh;
	//Position* down_neigh;
	//Position* up_right_neigh;
	//Position* down_right_neigh;
	//Position* up_left_neigh;
	//Position* down_left_neigh;

	bool is_ball;
	bool was_used;
};

