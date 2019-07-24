#include "hwlib.hpp"
#include "max7219.hpp"
#include "map.hpp"
#include "player.hpp"


int main(){
	/// Sets the different ports for the matrix and switches	
	auto clk = hwlib::target::pin_out( hwlib::target::pins::d8 );
	auto cs =  hwlib::target::pin_out( hwlib::target::pins::d9 );
	auto din = hwlib::target::pin_out( hwlib::target::pins::d10 );

	auto sw = hwlib::target::pin_in( hwlib::target::pins::d7 );
	auto sw2 = hwlib::target::pin_in( hwlib::target::pins::d6 );
	
	/// Constructs the matrix and makes it ready for use
	max7219 matrix( clk, din, cs );
	
	hwlib::wait_ms( 100 );
	matrix.startup();
	
	/// Constructs the different used classes
	player player1( matrix, sw, sw2 );
	obstacle obstacle1( matrix, 1, 8 );
	obstacle obstacle2( matrix, 2, 16 );
	obstacle obstacle3( matrix, 3, 24 );
	obstacle obstacle4( matrix, 4, 32 );
	map chopper( matrix, player1, obstacle1, obstacle2, obstacle3, obstacle4 );
	
	/// Prepares the game to run	
	chopper.startup();

	/// Generates random number and sets it to the diffferent obstacles.
	int random = 0;
	while( sw.read() ){
		random++;
		sw.refresh();
	}
	obstacle1.set_random( random );
	obstacle2.set_random( random*8 );
	obstacle3.set_random( random*3 );
	obstacle4.set_random( random*7 );

	/// Keeps updating and drawing the map so the game keeps running untill the voltage source is removed.
	for( ;; ){
		chopper.update();
		chopper.draw();
	}
}
	

