#ifndef MAP_HPP
#define MAP_HPP
#include "hwlib.hpp"
#include "variables.hpp"
#include "player.hpp"
#include "obstacle.hpp"

class map{
private:
	max7219 & matrix;
	player & player1;
	obstacle & obstacle1;
	obstacle & obstacle2;
	obstacle & obstacle3;
	obstacle & obstacle4;
public:
	map( max7219 & matrix, player & player1, obstacle & obstacle1, obstacle & obstacle2, obstacle & obstacle3, obstacle & obstacle4 );
	void startup();
	void reset();
	void update();
	void draw();
	void interact();
	void gameover();
};

#endif // MAP_HPP
