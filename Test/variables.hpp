#ifndef VARIABLES_HPP
#define VARIABLES_HPP


/// OPTIONAL 
/// Register address
const uint16_t max7219_No_Op = ( 0x00 << 8 );

/// Different rows you want to program
const uint16_t max7219_Digit0 = ( 0x01 << 8 );
const uint16_t max7219_Digit1 = ( 0x02 << 8 );
const uint16_t max7219_Digit2 = ( 0x03 << 8 );
const uint16_t max7219_Digit3 = ( 0x04 << 8 );
const uint16_t max7219_Digit4 = ( 0x05 << 8 );
const uint16_t max7219_Digit5 = ( 0x06 << 8 );
const uint16_t max7219_Digit6 = ( 0x07 << 8 );
const uint16_t max7219_Digit7 = ( 0x08<< 8 );


const uint16_t max7219_Decode = ( 0x09 << 8 );
const uint16_t max7219_Decode_Mode = 0x00;

/// Screen brightness
const uint16_t max7219_Intensity = ( 0x0A << 8 );
const uint16_t max7219_Duty_Cycle = 0x05;


const uint16_t max7219_Scan_Limit = ( 0x0B << 8 );
const uint16_t max7219_Scan_Limit_All = ( 0x07 );

/// Used for booting the devicce
const uint16_t max7219_Shutdown = ( 0x0C << 8 );
const uint16_t max7219_Normal_Op = 0x01;

/// Used for checking if all leds work
const uint16_t max7219_Displaytest = ( 0x0F << 8 );


/// MANDATORY
/// ledmatrixes
const int max7219_Amount = 4;

/// At least 8*max7219_Amount used for the infinite loop
const int infinite_loop_size = 72;







#endif
