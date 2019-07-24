#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP
#include "hwlib.hpp"
#include "variables.hpp"
#include "max7219.hpp"

class obstacle{
protected:
	max7219 & matrix;
	int obstacle_number;
	int column;
	int random;
	int row1;
	int row2;
	int row3;
	int random_count = 0;
public:
	obstacle( max7219 & matrix, int obstacle_nummber, int column = 32, int random=0 );
	void update();
	bool interact( int player_row );
	void draw();
	int get_column();
	void set_rows( int new_row1, int new_row2, int new_row3 );
	void set_random( int new_random );
	int make_random();
};

#endif // OBSTACLE_HPP
