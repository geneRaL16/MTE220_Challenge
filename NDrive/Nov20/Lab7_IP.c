#include "mte220.c"  // C functions needed for labs

/*
;**********************************************************************
;
;    Filename:	    lab6.c
;    Date:          Nov 12/05
;    File Version:  3.1
;
;    Author:        C.C.W. Hulls & D.L. Wight
;
;    Copyright (c) C.C.W. Hulls, P.Eng and D.L. Wight, 2005.
;    This software can be used and modified by students, staff and
;    faculty members at the University of Waterloo for teaching or
;    research purposes, provided the authors are acknowledged.
;
;**********************************************************************
;
;    Files required:
;
;**********************************************************************
;
;    History:
;
;    3.1  Nov 12/05  use new functions and macros;
;    3.0  Nov  7/05  main code split into separate file that loads the
;                    functions needed for MTE 220
;
;    2.0  Nov  5/05  ported to C;
;
;    1.1  Oct 25/05  changed the phase of right servo to be midway
;                    through the entire cycle; enable peripheral interrupts
;                    as part of interrupt initialization
;    1.0  Oct 24/05  original release
;
;**********************************************************************
;**********************************************************************
;
;    Description:
;
;   The lab 6 code reads the IR sensors difference amplifier.  The IR
;   sensors are used for line following, so when a noticeable difference
;   is detected, the appropriate servo is turned off.
;
;**********************************************************************
*/

//;**********************************************************************

#define MAX_POLARITY 0x99 // 3V, Change these after testing?
#define MIN_POLARITY 0x66 // 2V

void main(void)
{
    uns8 diode_value;
    uns8 analog_value;  // current ADC value
    uns8 hall_effect_count = 0;
    uns8 time_count = 0;

    Initialization();

    // Wait until button is pressed
    WaitForButton();

    // initially both servos are on
    UseServos         // (syntax of "call" is correct without () or ;)
    BothServosOn

    while (1)  // loop forever
    {
        diode_value = AnalogConvert(ADC_IR_SENSOR);  // get analog value from IR sensor diff amp
	analog_value = AnalogConvert(ADC_HALL_EFFECT); // get analog hall effect
	
	if(analog_value > MAX_POLARITY || analog_value < MIN_POLARITY && hall_effect_count == 0){
		BothServosOff
		LongDelay(800); // input * 0.125ms is approximate delay - 100ms here
		analog_value = AnalogConvert(ADC_HALL_EFFECT);
		if(analog_value > MAX_POLARITY || analog_value < MIN_POLARITY && hall_effect_count == 0){
			hall_effect_count = 500;
			// Turn on LED for 7 seconds when below 0 Gauss threshold
			if(analog_value > MAX_POLARITY){
				OnLED
				LongDelay(56000); // input * 0.125ms is approximate delay - 7s here
				OffLED
			}
			// Blink LED for 7 seconds when below 0 Gauss threshold
			else{
				while(time_count < 7){
					OnLED
					LongDelay(4000); // input * 0.125ms is approximate delay - 0.5s here
					OffLED
					LongDelay(4000); // input * 0.125ms is approximate delay - 0.5s here
					time_count += 1;
				}
			}
			BothServosOn
		}
		else
		{
			BothServosOn
		}
	} else {
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
	if (hall_effect_count > 0) {
		hall_effect_count--;
	}
    }
}

