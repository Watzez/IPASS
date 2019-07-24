/// @file


#include "hwlib.hpp"
#include "max7219.hpp"
#include "variables.hpp"
#include <vector>

/// \brief
/// Max7219 class constructor
/// \details
/// The constructor puts the clock, data in and chip select into the variables.
/// This is needed to communicate with the max7219 led matrix.
max7219::max7219( hwlib::target::pin_out clk, hwlib::target::pin_out din, hwlib::target::pin_out cs ):
		clk( clk ),
		din( din ),
		cs( cs )
{}

/// \brief
/// Regulates the pulse of the clock
/// \details
/// This function makes sure the output bit of data in gets send to the ledmatrix.
/// To do this the clock value is set to low then it waits the needed miliseconds before making it high and waiting enough time for the databit on the output of data in to get through.
/// After this it will wait again before making the value low again so the data in value now is fully transfered onto the ledmatrix. 
void max7219::clk_pulse(){
	hwlib::wait_ms( 0.1 );
	clk.write( 0 );
	hwlib::wait_ms( 0.2 );
	clk.write( 1 );
	hwlib::wait_ms( 0.1 );
	clk.write( 0 );
}


// \brief
/// Sends one bit to the ledmatrix
/// \details 
/// This function writes the given data bit  1 or 0  to the data in pin and calls clk_pulse to push the bit through onto the ledmatrix.
/// This makes it easier to send 1 bit at a time instead of calling data in write and clk_pulse.
void max7219::send_bit( const bool data ){
	din.write( data );
	clk_pulse();
} 

/// \brief
/// Lights up the desired led on the matrix
/// \details
/// This function is given the row and column of the wanted led.
/// The row start at 1 and ends at 8.
/// The column starts at 1 and ends at 8 * the given amount of ledmatrices.
/// with this function you can write a wanted value to a specific led to make it light up or to turn  it off.
void max7219::set_pixel( int row, int column, bool data ){
	if( ( row <= 8 ) && ( row > 0 ) && ( column <= 8*max7219_Amount ) && ( column > 0 ) ){
		buffer[row-1][column-1] = data;
	}
}
/// \brief
/// Sets the private buffer
/// \details
/// This function is given an array with 8 rows and 8 * the given ledmatrices amount of columns.
/// The function sets the private array buffer individual values for each value of the given array.
void max7219::set_buffer( bool new_buffer[8][8*max7219_Amount] ){
	for( int  i = 0; i < 8; i++ ){
		for( int j = 0; j < 8*max7219_Amount; j++ ){	
			buffer[i][j] = new_buffer[i][j];
		}
	}
}

/// \brief
/// Returns a bool from the array
/// \details
/// This function returns a bool at a given place in the array.
/// Starting at 1for row and column.
bool max7219::get_bool_buffer( int row, int column ){ return buffer[row][column]; }

/// \brief
/// Flushes the buffer to the screen
/// \details
/// This function sends the databytes for each row of the ledmatrices. It starts every byte with 4 empty bits that are not required.
/// Then it send 4 addres bits to the ledmatrix to let it know for wich row were sending the next bits.
/// After this it sends the 8 final bits for the different leds as to wich to light up and wich to turn off.
/// It sends the entire row at once starting at the last column.
/// After every change this function needs to be called to show the desired result
void max7219::flush(){
	for( int row = 0; row < 8; row++ ){
		cs.write( 0 );
		for( int column = 8*max7219_Amount; column > 0; (column -= 8)){
			for( int no_data = 0; no_data < 4; no_data++ ){
				send_bit( 0 );
			}
	
			for( int addr_bits = 3; addr_bits >= 0; addr_bits-- ){
				send_bit( ( (row+1) & ( 1 << addr_bits ) ) != 0 );
			}
		
			for( int bit = column; bit > (column - 8); bit-- ){
				send_bit( buffer[7-row][bit-1] );
			}
		}
	
		cs.write( 1 );
		hwlib::wait_ms( 1 );
		cs.write( 0 );
		hwlib::wait_ms( 1 );
	}
}

/// \brief
/// inverts the leds
/// \details
/// The function goes through the buffer 1 boolean at a time and inverts the value from 1 to 0 or 0 to 1.
/// This makes the leds that were currently on turn off and those that were off turn on.
void max7219::invert(){
	for( int  i = 0; i < 8; i++ ){
		for( int j = 0; j < 8*max7219_Amount; j++ ){	
			buffer[i][j] = !buffer[i][j];
		}
	}

}

/// \brief
/// Clears the ledmatrix
/// \details
/// This function goes through the values of buffer and changes them to 0.
void max7219::clear(){
	for( int  i = 0; i < 8; i++ ){
		for( int j = 0; j < 8*max7219_Amount; j++ ){	
			buffer[i][j] = 0;
		}
	}
}

/// \brief
/// Fills the ledmatrix
/// \details
/// This function lights up the ledmatrix and puts all the values of buffer on 1.
void max7219::fill(){
	for( int  i = 0; i < 8; i++ ){
		for( int j = 0; j < 8*max7219_Amount; j++ ){	
			buffer[i][j] = 1;
		}
	}

}

/// \brief
/// Shiftst the display to the left once
/// \details
/// This function goes through the buffer and puts the values of the next columns in the columns before it.
/// The result you get from this is that the entire display/array gest shifted 1 column to the left.
/// It also puts the values in the last column on 0 so you could use set_pixel to write something you want to appear from the right.
void max7219::shift_left(){
	for( int  i = 0; i < 8; i++ ){
		for( int j = 0; j < (8*max7219_Amount -1); j++ ){	
			buffer[i][j] = buffer[i][j+1];
		}
		buffer[i][8*max7219_Amount-1] = 0;
	}
}

/// \brief
/// Shiftst the display to the right once
/// \details
/// This function goes through the buffer and puts the values of the before columns in the columns after it.
/// The result you get from this is that the entire display/array gets shifted 1 column to the right.
/// It also puts the values in the first column on 0 so you coul use set_pixel to write something you want to appear from the left.
void max7219::shift_right(){
	for( int  i = 0; i < 8; i++ ){
		for( int j = (8*max7219_Amount-1); j > 0; j-- ){	
			buffer[i][j] = buffer[i][j-1];
		}
		buffer[i][0] = 0;
	}
}

/// \brief
/// Loops the buffer from right to left
/// \details
/// This function puts the values in column 1 into temp so it later could be put into the last column.
/// In between this it puts every value of the column after it into the column before it.
/// The result of this is a function that shifts everything to the left once and puts the values that leave the screen on the left back at the end on the righside.
void max7219::shift_left_loop(){
	bool temp[8][1];
	for( int  i = 0; i < 8; i++ ){
		temp[i][0] = buffer[i][0];
		for( int j = 0; j < (8*max7219_Amount-1); j++ ){	
			buffer[i][j] = buffer[i][j+1];
		}
		buffer[i][8*max7219_Amount-1] = temp[i][0];
	}
}

/// \brief
/// Loops the buffer from left to right
/// \details
/// This function puts the values in the last column into temp so it later could be put into the first column.
/// In between this it puts every value of the column before it into the column after it.
/// The result of this is a function that shifts everything to the right once and puts the values that leave the screen on the right back at the start on the leftside.
void max7219::shift_right_loop(){
	bool temp[8][1];
	for( int i = 0; i < 8; i++ ){
		temp[i][0] = buffer[i][8*max7219_Amount-1];
		for( int j = (8*max7219_Amount-1); j > 0; j-- ){	
			buffer[i][j] = buffer[i][j-1];
		}
		buffer[i][0] = temp[i][0];
	}
}

/// \brief
/// A loop that keeps shifting left
/// \details
/// This function is given a desired array with x amount of columns declared in the variables.hpp a button to break the loop and an integer to control the scroll speed.
/// This function works similar to the shift_left_loop function.
/// It only adds the option of giving an array of your desired length  and its able to be stopped by a button.
void max7219::infinite_loop_left( bool loop[8][infinite_loop_size], hwlib::target::pin_in break_loop, int wait ){
	bool temp[8][1];	
	for( ;; ){
		for( int i = 0; i < 8; i++){
			temp[i][0] = loop[i][0];				
			for( unsigned int j = 0; j < (8*max7219_Amount); j++ ){
				buffer[i][j] = loop[i][j];
			}
			for( unsigned int k = 0; k < infinite_loop_size; k++ ){
				loop[i][k] = loop[i][k+1];
			}
			loop[i][infinite_loop_size-1] = temp[i][0];
		}
		flush();
		hwlib::wait_ms( wait );
		break_loop.refresh();
		if( !break_loop.read() ){
			break;
		}
	}
}

/// \brief
/// Starts the matrix
/// \details
/// This function should be called at the start after declaring the matrix.
/// It goes through the different functions of the max7219 and checks if everything is in order by lighting up the matrix.
/// It prepares the matrix to me programmable and clears the screen after.
void max7219::startup(){
	repeat_data( max7219_Displaytest | 1 );
	repeat_data( max7219_Displaytest | max7219_No_Op );
	repeat_data( max7219_Shutdown | max7219_Normal_Op );
	repeat_data( max7219_Scan_Limit | max7219_Scan_Limit_All );
	repeat_data( max7219_Decode | max7219_Decode_Mode );
	repeat_data( max7219_Intensity | max7219_Duty_Cycle );
	clear();
	flush();
}

/// \brief
/// Repeats the data at startup
/// \details
/// this function sends the desired byte that is given and repeats this matrix amount of times.
/// This is so every matrix chained receives the same startup data.
void max7219::repeat_data( const uint16_t data){	
	cs.write( 0 );
	for( int rep_count = 0; rep_count < max7219_Amount; rep_count++ ){
		for( int bit_count = 15; bit_count >= 0; bit_count-- ){
			send_bit( ( data & ( 1 << bit_count ) ) != 0 );
		}
	}
	cs.write( 1 );
	hwlib::wait_ms( 1 );
	cs.write( 0 );
	hwlib::wait_ms( 1 );
}


