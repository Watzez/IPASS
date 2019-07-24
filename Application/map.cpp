#include "hwlib.hpp"
#include "max7219.hpp"
#include "variables.hpp"
#include "map.hpp"

map::map( max7219 & matrix, player & player1, obstacle & obstacle1, obstacle & obstacle2, obstacle & obstacle3, obstacle & obstacle4 ):
	matrix( matrix ),		/// Matrix in wich changes are made
	player1( player1 ),		/// Player1 check player class
	obstacle1( obstacle1 ),		/// Obstacles check obstacle class
	obstacle2( obstacle2 ),
	obstacle3( obstacle3 ),
	obstacle4( obstacle4 ),
{}

/// Clears the matrix at statup and draws the player so the screen can be seen before starting the game
void map::startup(){
	matrix.clear();
	player1.draw();
	matrix.shift_left();
	for( int i = 1; i <= 8; i += 7 ){
		for( int j = 32; j > 0; j-- ){
			matrix.set_pixel( i, j, 1 );
		}
	}
	matrix.flush();
}

/// Is used to restart the game when you died it resets everything to the start
void map::reset(){
	player1.set_row( 5 );
	obstacle1.set_rows( 0, 0, 0 );
	obstacle2.set_rows( 0, 0, 0 );
	obstacle3.set_rows( 0, 0, 0 );
	obstacle4.set_rows( 0, 0, 0 );
	startup();
}

/// Calls the different classes to do their next update/move and then checks if any of them interact with each other
void map::update(){
	player1.move();
	obstacle1.update();	
	obstacle2.update();	
	obstacle3.update();	
	obstacle4.update();
	interact();
}

/// Draws all the objects on the map and shifts it one to the left
void map::draw(){
	player1.draw();
	obstacle1.draw();
	obstacle2.draw();
	obstacle3.draw();
	obstacle4.draw();
	matrix.shift_left();
	matrix.set_pixel( 1, 8*max7219_Amount, 1 );
	matrix.set_pixel( 8, 8*max7219_Amount, 1 );
	matrix.flush();
	hwlib::wait_ms( 50 );
}

/// Checks for collision with the sides and with 1 of the obstacles by checking if they reach the same column number as player
void map::interact(){
	if( player1.get_row() == 8 || player1.get_row() == 1 ){
		gameover();
		reset();
	}else if( obstacle1.get_column() == 5 || obstacle2.get_column() == 5 || obstacle3.get_column() == 5 || obstacle4.get_column() == 5 ){
		if( 	obstacle1.interact( player1.get_row() ) || 
			obstacle2.interact( player1.get_row() ) || 		
			obstacle3.interact( player1.get_row() ) ||
			obstacle4.interact( player1.get_row() ) ){
				gameover();
				reset();
		}
	}
}

/// Is called when collision is detected and shows the message GAME OVER on screen if you want to restart you could push the down button to exit and reset the game
void map::gameover(){
	bool gameover[8][72] ={ {1,1,1,1,1,1,1,1, 0, 0,1,1,1,1,1,1,0, 0, 1,1,0,0,0,0,1,1, 0, 1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1,1, 0, 1,1,0,0,0,0,1,1, 0, 1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1,1, 0 }, 
				{1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1,1, 0, 1,1,1,0,0,1,1,1, 0, 1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1,1, 0, 1,1,0,0,0,0,1,1, 0, 1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1,1, 0 },	
				{1,1,0,0,0,0,0,0, 0, 1,1,0,0,0,0,1,1, 0, 1,1,1,1,1,1,1,1, 0, 1,1,0,0,0,0,0,0, 0, 1,1,0,0,0,0,1,1, 0, 1,1,0,0,0,0,1,1, 0, 1,1,0,0,0,0,0,0, 0, 1,1,0,0,0,0,1,1, 0 },
				{1,1,0,0,0,0,0,0, 0, 1,1,0,0,0,0,1,1, 0, 1,1,0,1,1,0,1,1, 0, 1,1,1,1,1,1,0,0, 0, 1,1,0,0,0,0,1,1, 0, 1,1,0,0,0,0,1,1, 0, 1,1,1,1,1,0,0,0, 0, 1,1,0,0,0,0,1,1, 0 },
				{1,1,0,0,0,1,1,1, 0, 1,1,0,0,0,0,1,1, 0, 1,1,0,0,0,0,1,1, 0, 1,1,1,1,1,1,0,0, 0, 1,1,0,0,0,0,1,1, 0, 1,1,0,0,0,0,1,1, 0, 1,1,1,1,1,0,0,0, 0, 1,1,1,1,1,1,1,1, 0 },
				{1,1,0,0,0,0,1,1, 0, 1,1,1,1,1,1,1,1, 0, 1,1,0,0,0,0,1,1, 0, 1,1,0,0,0,0,0,0, 0, 1,1,0,0,0,0,1,1, 0, 0,1,1,0,0,1,1,0, 0, 1,1,0,0,0,0,0,0, 0, 1,1,0,0,1,1,0,0, 0 },
				{1,1,1,1,1,1,1,1, 0, 1,1,0,0,0,0,1,1, 0, 1,1,0,0,0,0,1,1, 0, 1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1,1, 0, 0,0,1,1,1,1,0,0, 0, 1,1,1,1,1,1,1,1, 0, 1,1,0,0,0,1,1,0, 0 },
				{1,1,1,1,1,1,1,1, 0, 1,1,0,0,0,0,1,1, 0, 1,1,0,0,0,0,1,1, 0, 1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1,1, 0, 0,0,0,1,1,0,0,0, 0, 1,1,1,1,1,1,1,1, 0, 1,1,0,0,0,0,1,1, 0 } };	
	matrix.infinite_loop_left( gameover, player1.get_down(), 100 );
	startup();
}
