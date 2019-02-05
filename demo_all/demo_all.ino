/**
 * demo_all: Demonstrates all features of the 
 * circuit board.
 * 
 * This program uses the two push buttons, the four LEDs, 
 * the potentiometer (pot) and a single servo motor. Two of 
 * the LEDs are flashed on and off, while the other two are 
 * controlled by the push buttons. The position of the 
 * servo motor is controlled by the pot.
 * 
 * Author: Daniel Morris, University of Canterbury for WiE CAN
 * Last modified: 16 Jan 2019
 */


/* Include (import) the servo library
 * This library allows us to control servo motors 
 * without needing to manually generate the electrical signals
 * a servo motor expects.
 */
#include <Servo.h>

Servo myservo;  // Create a servo 'object' to control a servo.

// These variables are integers; they can only be positive or negative whole numbers.

int pot_pin = A7;     // Analog pin number that the potentiometer is connected to.
                      // Note that on the PCB it says A6; this is a typo.
int pot_val;          // Variable to store values read from the potentiometer.
int servo_pin = 6;    // Digital pin that the servo motor is connected to.
int button_1_pin = 3; // Digital pin that the first button is connected to.
int button_2_pin = 4; // Digital pin that the second button is connected to.


// These variables are booleans; they are either 'true' or 'false'.
// This often corresponds to something being on or off; in our case, 
// they indicate whether a button has been pressed.

bool b1, b2 = true;   // Variables to store the values read from each button
                      // Note that two variables, b1 and b2, have been created on
                      // the same line.

// This is an 'array' of integers (also known as a list). In this case, it stores 
// four integers, which are the digital pins that the LEDs are connected to.
int leds[4] = {7,8,9,A0};

// A 'long' is similar to an integer; it is a whole number that can be 
// larger than an integer.
// 'unsigned' means that it can only be positive. We are using these variables
// to store times, which cannot be negative. 
// Making them unsigned means they can store larger positive numbers.
unsigned long t_now, t_1, t_2;

// Our code starts running from here
void setup() {
    Serial.begin(9600);             // Start the USB serial port. This allows us to print out
                                    // information on the computer.
                                    
    Serial.println("Starting...");  // Print out the text "Starting..." on the serial monitor 
                                    // (the magnifying glass in the top-right corner).
                                    // The 'ln' at the end of 'println' means that a newline will
                                    // be added, so that the next print/println command will print 
                                    // on a new line in the serial monitor. If you don't want a newline
                                    // added, you can use Serial.print() instead.
    
    myservo.attach(servo_pin);    // Indicates that the servo is connected to pin 9
                                  // Links this pin to the servo object we created above
                        
    pinMode(pot_pin, INPUT);      // Indicates that the pot pin is an input - the 
                                  // microcontroller should read in electricity on this
                                  // pin, rather than output an electrical signal
    pinMode(button_1_pin, INPUT); // Set up button 1 as an input
    pinMode(button_2_pin, INPUT); // Set up button 2 as an input

    // Here we 'loop' over a counter running from 1 to 3
    // Note that the first item in an array has an index of 0! So to get the first item
    // out of the LEDs array, we would need to put leds[0].
    // Using a loop is a neater way of doing this for all LEDs.
    for (int i = 0; i < 4; ++i) {
        pinMode(leds[i], OUTPUT); // Set up each LED as an output
    }
    
    t_now = millis(); // Read the current time, in milliseconds
    t_1 = t_now;      // Copy this to the other two timing variables, so they
    t_2 = t_now;      // all start at the same point in time.
}

// This is run after setup, and loops around forever
void loop() {
    pot_val = analogRead(pot_pin);           // Read the value of the potentiometer (value between 0 and 1023)
    pot_val = map(pot_val, 0, 1023, 0, 180);     // Scale the readung to use it with the servo (value between 0 and 180)
    myservo.write(pot_val);                  // Set the servo position according to the scaled value
    delay(5);                            // Wait for the servo to get to the desired position

    b1 = digitalRead(button_1_pin);      // Read the value of button 1
    b2 = digitalRead(button_2_pin);      // Read the value of button 2
    
    //Serial.println(b1);                  // We can also print out variables. In this case we will get either 1 
                                         // or 0 printed out. A 1 indicates that the voltage on the button is 
                                         // 'high' (around 5 volts), and a 0 indicates that the voltage is low 
                                         // (around 0 volts). Our buttons are set up so that, when they are not 
                                         // pressed, the voltage across them is high.
                                         //
                                         // This line of printing is commented out, as this will print the state of 
                                         // the button every time this loop runs, which means a lot of printing! If you 
                                         // want to try it out, delete the two forward slashes at the start of the line.

    // Note that our buttons are 'active low'. When they are pressed, they read 'false', and 
    // when not pressed, they read 'true'. So to make our LEDs turn on when the button is pressed,
    // we need to 'invert' (flip) whatever we read from the button - this is what the ! does.
    // Try running this without the ! and see what happens!
    digitalWrite(leds[0], !b1);          // Turn the 1st LED on or off
    digitalWrite(leds[1], !b2);          // Turn the 2nd LED on or off

    t_now = millis();                    // Read the current time
    
    // Flash the other two LEDs.
    // If a certain amount of time has passed, change the state of the LED - 
    // if it is off, turn it on. Likewise, if it is on, turn it off.
    //
    // The time difference is in milliseconds. The LED will take twice as long 
    // as the time difference to flash fully, as it needs to turn on, then off.
    // For example, a time difference of 500 milliseconds (half a second) will cause the 
    // LED to flash once every second.

    // Flash the third LED once per second.
    if ((t_now - t_1) >= 500) {                        // Check if the time difference is large enough
        t_1 = t_now;                                   // Update the recording of the last time we flashed this LED
        digitalWrite(leds[2], !digitalRead(leds[2])); // Read whether the LED is on or off, and write the opposite to it
        Serial.println("Flash!");                     // Print out the word "Flash!" every time the LED is turned on or off
    }

    // Flash the fourth LED five times a second
    if ((t_now - t_2) >= 100) {
        t_2 = t_now;
        digitalWrite(leds[3], !digitalRead(leds[3]));
    }
}
