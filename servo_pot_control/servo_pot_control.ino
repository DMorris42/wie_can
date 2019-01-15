/**
 * servo_pot_control: Control the motion of a servo 
 * motor using a potentiometer.
 * 
 * This sketch reads in the voltage from a potentiometer (a pot)
 * and moves the servo motor to an angle between 0 and 180 degrees 
 * based upon the reading from the pot.
 * 
 * Text following a double forward slash (//) or in a section like this one 
 * are comments, and are ignored when we compile our code.
 * 
 * Author: WiE CAN, University of Canterbury
 * Last modified: 15 Jan 2019
 */


/* Include (import) the servo library
 * This library allows us to control servo motors 
 * without needing to manually generate the electrical signals
 * a servo motor expects.
 */
#include <Servo.h>

Servo myservo;  // Create a servo 'object' to control a servo

// These variables are integers; they can only be positive or negative whole numbers

int pot_pin = A7;   // Analog pin number that the potentiometer is connected to.
int val;            // Variable to store values read from the potentiometer.
int servo_pin = 6;  // Digital pin that the servo motor is connected to.

// Our code starts running from here
void setup() {
    myservo.attach(servo_pin);  // Indicates that the servo is connected to pin 9
                                // Links this pin to the servo object we created above.
                        
    pinMode(pot_pin, INPUT);    // Indicates that the pot pin is an input - the 
                                // microcontroller should read in electricity on this
                                // pin, rather than output an electrical signal.
}

// This is run after setup, and loops around forever
void loop() {
    val = analogRead(pot_pin);           // Read the value of the potentiometer (value between 0 and 1023)
    val = map(val, 0, 1023, 0, 180);     // Scale the readung to use it with the servo (value between 0 and 180)
    myservo.write(val);                  // Set the servo position according to the scaled value
    delay(5);                            // Wait for the servo to get to the desired position
}

/**
 * Why are the potentionmeter values between 0 and 1023? 
 * 
 * The microcontroller uses a device called an Analog to Digital Converter (ADC)
 * to read a voltage, and convert it to binary (1's and 0's). However it cannot use
 * an unlimited number of binary digits (a 'bit' is short for binary digit) to represent the voltage value.
 * More bits improves accuracy (specifically, it improves resolution), but is more complex and costs more.
 * 
 * Our microcontroller uses 10 bits to represent a voltage, so a voltage of 5 volts (the maximum voltage we 
 * can read) is represented as 1111111111 (10 1's). This value, converted back to base 10 (decimal numbers)
 * is 1023. Likewise, a voltage of zero volts is represented as 0000000000 (10 0's), which is also 0 in decimal.
 */
