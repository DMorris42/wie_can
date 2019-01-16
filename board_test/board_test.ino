/**
 * board_test: Test all servos, LEDs, buttons and pot on board
 * If more than a couple of servos are connected (or connected to any 
 * servo header except pins 5 or 6), an external power source should be used.
 * A 6V supply (with enough current) seems to be fine.
 * 
 * If Serial USB is used, the servos connected to pins 0 and 1 probably won't work, 
 * and may do strange stuff.
 * 
 * Note that this doesn't test the I2C breakout. 
 * 
 * Author: Daniel Morris
 * Last modified: 16 Jan 2019
 */

#include <Servo.h>

#define NUM_SERVOS 10
#define NUM_LEDS 4

Servo s0, s1, s2, s3, s4, s5, s6, s7, s8, s9; // 10 Servo pins in total
static const Servo servos[NUM_SERVOS] = {s0, s1, s2, s3, s4, s5, s6, s7, s8, s9};
static const int servo_pins[NUM_SERVOS] = {A1, 13, A3, A2, 6, 5, 0, 1, 12, 11}; 
static const int pot_pin = A7; // Note silkscreen says A6; this is a typo
int pot_val = 0;
static const int button_1_pin = 3;
static const int button_2_pin = 4;
static const int led_pins[NUM_LEDS] = {7, 8, 9, A0};

static bool b1, b2;
unsigned long t_now, t_1, t_2;

void setup() {
    for (int i = 0; i < NUM_SERVOS; ++i) {
        servos[i].attach(servo_pins[i]);
        servos[i].write(0);
        delay(500);
        servos[i].write(180);
        delay(1000);
        servos[i].detach();
    }
    
    pinMode(pot_pin, INPUT);
    pinMode(button_1_pin, INPUT);
    pinMode(button_2_pin, INPUT);
    for (int i = 0; i < NUM_LEDS; ++i) {
        pinMode(led_pins[i], OUTPUT);
    }

    servos[0].attach(servo_pins[0]);
    
    t_now = millis();
    t_1 = t_now;
    t_2 = t_now;
}

void loop() {
    // Control a servo via the pot
    // Choice of servo is arbitrary
    // Note attachment above
    pot_val = analogRead(pot_pin);       
    pot_val = map(pot_val, 0, 1023, 0, 180);    
    servos[0].write(pot_val);                 
    delay(5);                            

    // Control LEDs 1 and 2 via buttons
    b1 = digitalRead(button_1_pin);  
    b2 = digitalRead(button_2_pin);   

    digitalWrite(led_pins[0], !b1);         
    digitalWrite(led_pins[1], !b2);          

    t_now = millis();           

    // Flash the third LED
    if ((t_now - t_1) >= 500) {                      
        t_1 = t_now;                                  
        digitalWrite(led_pins[2], !digitalRead(led_pins[2])); 
    }

    // Flash the fourth LED
    if ((t_now - t_2) >= 100) {
        t_2 = t_now;
        digitalWrite(led_pins[3], !digitalRead(led_pins[3]));
    }
}
