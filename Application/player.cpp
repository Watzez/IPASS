#include "hwlib.hpp"
#include "max7219.hpp"
#include "variables.hpp"
#include "player.hpp"

player::player( max7219 & matrix, hwlib::target::pin_in up, hwlib::target::pin_in down ):
	matrix( matrix ),	/// The matrix to wich the player data is writen
	up( up ),		/// Used to move the player up or left depending on the screen orientation
	down( down ),		/// Used to move the player down or right depending on the screen orientation
	row( 5 ),		/// Players startposition
	column( 5 )		/// Players startposition column wont change
{}

/// Used to check the users input and move the player 1pixel up or down every move.
/// It also removes the last position of the player making sure it doesnt become a snake of pixels.
void player::move(){
	matrix.set_pixel( row, column, 0 );
	up.refresh();
	down.refresh();
	if( !down.read() ){
		if( row < 8 ){
			row++;
		}
	}
	else if( !up.read() ){
		if( row > 1 ){
			row--;
		}
	}
}

/// Draws the player onto the screen and removes the old position again this is because when you're gameover the program doesnt go from update to draw but from draw to update.
void player::draw(){
	matrix.set_pixel( row, column, 0 );
	matrix.set_pixel( row, column+1, 1 );
}

/// Returns row for collision detection
int player::get_row(){ return row; }

/// Set desired row for player
void player::set_row( int new_row ){ row = new_row; }

/// Returns the down button to reset the game
hwlib::target::pin_in player::get_down(){ return down; }
