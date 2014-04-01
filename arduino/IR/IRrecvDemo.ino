/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

// Settings
int RECV_PIN = 11;
int OUT_PIN = 2;

// Globals
bool seen_code = false;


IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
	Serial.begin(9600);
	irrecv.enableIRIn(); // Start the receiver
	pinMode(OUT_PIN, OUTPUT);
	digitalWrite(OUT_PIN, LOW);
}

void loop() {
	if (irrecv.decode(&results)) {
		Serial.println(results.value, HEX);
		if(results.value == 0x20DFA25D){ //large play button in the middle
				seen_code = true;
		}
		if(seen_code){
				digitalWrite(OUT_PIN, HIGH);
				// delay(500);
				// digitalWrite(OUT_PIN, LOW);
				// seen_code = false;
		}
		irrecv.resume(); // Receive the next value
	}
}
