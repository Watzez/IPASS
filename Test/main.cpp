#include "ostream"
#include "max7219.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

auto clk = hwlib::target::pin_out( hwlib::target::pins::d8 );
auto cs =  hwlib::target::pin_out( hwlib::target::pins::d9 );
auto din = hwlib::target::pin_out( hwlib::target::pins::d10 );

max7219 matrix( clk, din, cs );

TEST_CASE( " set_pixel " ){
	matrix.clear();
	matrix.set_pixel( 3, 3, 1 );
	REQUIRE(get_bool_buffer( 2, 2 ) == 1);
}

TEST_CASE( " set_pixel2 " ){
	matrix.clear();	
	matrix.set_pixel( 3, 3, 1 );
	REQUIRE(!(get_bool_buffer( 3, 3 ) == 1));
}

TEST_CASE( " set_buffer " ){
	matrix.clear();
	bool new_buffer[8][32];
	for( i = 0; i < 8; i++ ){
		for( j = 0; j < 32; j++ ){
			new_buffer[i][j] = 1;
		}
	}
	matrix.set_buffer( new_buffer );
	REQUIRE(get_bool_buffer( 5, 29 ) == 1);
}

TEST_CASE( " get_bool_buffer " ){
	matrix.clear();
	matrix.set_pixel( 3, 3, 1 );
	REQUIRE(!(get_bool_buffer( 2, 2 ) == 0) && (get_bool_buffer( 3, 3 ) == 0));
}

TEST_CASE( " invert " ){
	matrix.clear();
	matrix.invert();
	REQUIRE((get_bool_buffer( 5, 3 ) == 1 ) && !(get_bool_buffer( 7, 12 ) == 0));
}

TEST_CASE( " clear " ){
	matrix.fill();
	matrix.clear();
	REQUIRE((get_bool_buffer( 5, 3 ) == 0 ) && !(get_bool_buffer( 7, 12 ) == 1));
}

TEST_CASE( " fill " ){
	matrix.clear();
	matrix.fill();
	REQUIRE((get_bool_buffer( 5, 11 ) == 1 ) && !(get_bool_buffer( 7, 22 ) == 0));
}

TEST_CASE( " shift_left " ){
	matrix.clear();
	matrix.set_pixel( 3, 6, 1 );
	matrix.shift_left();
	REQUIRE((get_bool_buffer( 2, 4 ) == 1) && (get_bool_buffer( 3, 6 ) == 0));
}

TEST_CASE( " shift_right " ){
	matrix.clear();
	matrix.set_pixel( 3, 6, 1 );
	matrix.shift_right();
	REQUIRE((get_bool_buffer( 2, 6 ) == 1) && (get_bool_buffer( 2, 5 ) == 0));
}

TEST_CASE( " shift_left_loop " ){
	matrix.clear();
	matrix.set_pixel( 1, 1, 1 );
	matrix.shift_left_loop();
	REQUIRE((get_bool_buffer( 0, 31 ) == 1) && (get_bool_buffer( 0, 0 ) == 0));
}

TEST_CASE( " shift_left_loop " ){
	matrix.clear();
	matrix.set_pixel( 1, 32, 1 );
	matrix.shift_right_loop();
	REQUIRE((get_bool_buffer( 0, 0 ) == 1) && (get_bool_buffer( 0, 31 ) == 0));
}
