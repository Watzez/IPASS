///@file

#ifndef MAX7219_HPP
#define MAX7219_HPP
#include "hwlib.hpp"
#include <vector>
#include "variables.hpp"

/// \brief
/// A class to control the max7219
/// \details
/// The class has 4 variables.
/// The pin_out clk wich is used to control the clock and write desired data to it.
/// The pin_out din wich is used to control the data in and write desired data to it.
/// The pin_ou cs wich is used to control the chip select and write desired data to it.
/// The array buffer wich is used to store the desired values of the specific leds.
class max7219{
private:
	hwlib::target::pin_out clk;
	hwlib::target::pin_out din;
	hwlib::target::pin_out cs;
	bool buffer[8][8*max7219_Amount];
public:
	max7219( hwlib::target::pin_out clk, hwlib::target::pin_out din, hwlib::target::pin_out cs );
	void clk_pulse();
	void send_bit( bool data );
	void set_pixel( int row, int column, bool data );
	void set_buffer( bool new_buffer[8][8*max7219_Amount] );
	bool get_bool_buffer(int row, int column );
	void flush();
	void invert();
	void clear();
	void fill();
	void shift_left();
	void shift_right();
	void shift_left_loop();
	void shift_right_loop();
	void infinite_loop_left( bool loop[8][infinite_loop_size], hwlib::target::pin_in break_loop, int wait = 200 );
	void startup();
	void repeat_data(const uint16_t data);
};

#endif
