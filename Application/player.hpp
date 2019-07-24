#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "hwlib.hpp"
#include "variables.hpp"
#include "max7219.hpp"

class player{
protected:
	max7219 & matrix;
	hwlib::target::pin_in up;
	hwlib::target::pin_in down;
	int row;
	const int column;
public:
	player( max7219 & matrix, hwlib::target::pin_in up, hwlib::target::pin_in down );
	void move();
	void draw();
	void interact();
	int get_row();
	void set_row( int new_row );
	hwlib::target::pin_in get_down();
	void gameover();
};

#endif // PLAYER_HPP
