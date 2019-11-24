/*
Overview:
Start moving forward when pushbutton is pressed
Check hints page on Learn for comments on how to power the motors properly
Use “available sensors” (photodiodes) to follow line marked in black electrical tape
Stop when hall effect sensor detects magnet (only detect those within 5cm)
Blink LED depending on polarity of magnet
*/

#include “mte220.c”
#define MAX_POLARITY 0x99 // 3V, Change these after testing?
#define MIN_POLARITY 0x66 // 2V

void start_driving(void){
	// Ramp up motor speed, this will be dependent on the motor values we measured a few labs back
	// 0 -> 25% -> 50% -> 75% -> 100%?
}

void stop_driving(void){
	// Opposite process of start_driving()
}

// Our program
void main(void){
	// Declare vars here
	uns8 analog_value;
	uns8 diode_value; // Values of left and right photodiodes (will help signal direction)
	uns8 time_count = 0;	

	Initialization();
	
	// Wait until button is pressed
	WaitForButton();

	start_driving();
	while(1){
		// Drive until magnet sensed, need to correct direction based on input from photodiodes
		analog_value = AnalogConvert(ADC_HALL_EFFECT);
		// If sensed, stop, and go through LED process, and start again
		// Double check this value somehow
		if(analog_value > MAX_POLARITY || analog_value < MIN_POLARITY){
			stop_driving();
			// Turn on LED for 7 seconds when below 0 Gauss threshold
			if(analog_value > MAX_POLARITY){
				OnLED
				Delay(7);
				OffLED
			}
			// Blink LED for 7 seconds when below 0 Gauss threshold
			else{
				while(time_count < 7){
					OnLED
					Delay(0.5);
					OffLED
					Delay(0.5);
					time_count += 1;
				}
			}
			start_driving();
		}
		// Else, read in photodiode values and alter direction if necessary
		else {
			diode_value = AnalogConvert(ADC_IR_SENSOR);
			if ( diode_value < 0x66 )  // 0x66 is 2V for 10-bit ADC with 2 LSB dropped
			{
				// left servo only
				LeftServoOn
				RightServoOff
			}
			else if ( diode_value > 0x99 )  // 0x99 is 3V for 10-bit ADC with 2 LSB dropped
			{
				// right servo only
				RightServoOn
				LeftServoOff
			}
			else
			{
				// both servos on
				BothServosOn
			}

		}

	}
}
