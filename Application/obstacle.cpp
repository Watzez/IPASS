#include "hwlib.hpp"
#include "max7219.hpp"
#include "variables.hpp"
#include "obstacle.hpp"

obstacle::obstacle( max7219 & matrix, int obstacle_number, int column, int random ):
	matrix( matrix ),			/// The matrix in wich the changes are made
	obstacle_number( obstacle_number ),	/// An integer used to make the random function more random
	column( column ),			/// Column of obstacle
	random( random ),			/// Random number for new obstacle generation
	row1( 0 ),				/// Row 1-3 of object
	row2( 0 ),
	row3( 0 )
{}

/// Updates obstacle to check if it has left the screen ifso it generates a new random number and writes the new obstacle to the screen
void obstacle::update(){
	if( column > 0 ){	
		column--;
	}else if( column <= 0 ){
		column = 32;
		row1 = make_random();
		row2 = row1+1;
		row3 = row1+2;
		matrix.set_pixel( row1, column, 1 );
		matrix.set_pixel( row2, column, 1 );
		matrix.set_pixel( row3, column, 1 );
	}
}

/// Checks for collision with the player by checken the column number because player is always in column 5 then it checks the obstacles row numbers to the ones of player and returns true if collision is detected
bool obstacle::interact( int player_row ){
	if( column == 5 ){
		if( row1 == player_row || row2 == player_row || row3 == player_row ){
			return true;
		}
	}
	return false;
}

/// Draws the obstacle to the matrix
void obstacle::draw(){
	matrix.set_pixel( row1, column, 1 );
	matrix.set_pixel( row2, column, 1 );
	matrix.set_pixel( row3, column, 1 );
}

/// Returns the current column of obstacle
int obstacle::get_column(){ return column; }

/// Is used to set the rows of obstacle used when reset is called
void obstacle::set_rows( int new_row1, int new_row2, int new_row3 ){
	row1 = new_row1;
	row2 = new_row2;
	row3 = new_row3;
}

/// Sets the random number.
void obstacle::set_random( int new_random ){ random = new_random; }

/// Generates a new random number based on the random class member
int obstacle::make_random(){
	for( int i  = obstacle_number; i > 0; i-- ){
		random_count++;
		random += random_count;
		random = (random % 4);
	}	
	return random+2;
}
