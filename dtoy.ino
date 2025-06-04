

//
// Simple sketch to drive a pair of LEDs in the eyes of a T800 Terminator
// desk toy.  A PIR sensor triggers a random animation when motion is
// detected.  The animations are implemented below in several helper
// functions.
//

// LED pins (PWM capable)
int led = 3;   // left eye LED
int led1 = 5;  // right eye LED

// PIR motion sensor input pin
int pir = 2;

// Control flags and counters used while an animation is playing
boolean playing = false; // set when an animation is active
int count = 0;           // counts cycles within the current animation

// Randomly selected animation function index
int fnc = 0;

// Variables used by some of the animations
int i;
int on;
int off;
int pulses;
int cycles = 5;          // number of breathing cycles

void setup() {
  // Initialize the hardware once at power up
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(pir,INPUT);
  randomSeed(analogRead(0));
}

void loop() {
  // Check the PIR sensor and start a random animation when motion is detected
  if(digitalRead(pir) ==HIGH)
  {
  fnc = random (7);
  playing = true;
  }
 while(playing)
 {
  count +=1;
  
  switch(fnc) {
   case 0:
   police();
   break; 
   
   case 1:
   pulsesame();
   break;
   
   case 2:
   pulsealt();
   break;

   case 3:
   risefall();
   break;  
   
   case 4:
   breath();
   break; 

   case 5:
   fire();
   break; 

  case 6:
   tube();
   break;
  }
   
 if(count >=5)
  {
    count = 0;
    playing = false;
      digitalWrite(led, LOW);
      digitalWrite(led1, LOW);
  }
 }
  // wait for the next motion trigger
}

// Rapid on/off pattern used for the "tube" effect
void tube()
{
    const int delays[] = {10, 20, 20, 240, 20, 40, 20, 100, 20, 20, 20, 260, 80, 20, 240, 60, 160, 20, 240, 20, 1000, 20, 20, 40, 100, 20, 2740, 340, 860, 20, 1400, 20, 60, 20};

    for(int i=0; i<sizeof(delays)/sizeof(int); ++i) {
        digitalWrite(led, !(i&1));
        digitalWrite(led1, !(i&1));
        delay(delays[i]);
    }
   
}

// Flickering fire effect using random brightness
void fire()
{
    analogWrite(led, random(120)+135);
    analogWrite(led1, random(120)+135);
    delay(random(100));
}

// Smooth breathing animation that slowly fades LEDs in and out
void breath()
{
  pulses = 8;
  for (on = 1; on <= cycles; on++) {
    for (i = 0; i < pulses; i++) {
      digitalWrite(led, HIGH);
      digitalWrite(led1, HIGH);
      delay(on);
      digitalWrite(led, LOW);
      digitalWrite(led1, LOW);
      delay(cycles - on);
    }
    //  on  off  pu  cy
    // (1 + 4) * 8 * 5 = 200ms
  }

  pulses = 8;
  for (off = cycles; off > 1; off--) {
    for (i = 0; i < pulses; i++) {
      digitalWrite(led, HIGH);   
      digitalWrite(led1, HIGH); 
      delay(off);               
      digitalWrite(led, LOW);   
      digitalWrite(led1, LOW);  
      delay(cycles - off);               
    }
    //  on  off  pu  cy
    // (5 + 1) * 8 * 5 = 200ms
  }
 
  digitalWrite(led, LOW);    
    digitalWrite(led1, LOW);  
  delay(2000);  
}

// LEDs gradually rise to full brightness and then fall
void risefall()
{ 
  float in, out;
  for (in = 4.712; in < 7.854; in = in + 0.001)
  {
    out = sin(in) * 127.5 + 127.5;
    analogWrite(led,out);
    analogWrite(led1,out);
    delay(1);
  }

  delay(500); // pause at peak brightness

  // falling
  for (in = 1.570; in < 4.712; in = in + 0.001)
  {
    out = sin(in) * 127.5 + 127.5;
    analogWrite(led,out);
    analogWrite(led1,out);
    delay(1);
  }

  delay(1000); // pause while dark
}


// Alternate LEDs pulsing using sine wave
void pulsealt()
{
  float in, out;
for (in = 0; in < 6.283; in = in + 0.001)
{
  out = sin(in) * 127.5 + 127.5;
  analogWrite(led,out);
  out = sin(in + 2.094) * 127.5 + 127.5;
  analogWrite(led1,out);
}
}


// Both LEDs pulse together using a sine wave
void pulsesame()
{
  float in, out;
 
  for (in = 0; in < 6.283; in = in + 0.00628)
  {
    out = sin(in) * 127.5 + 127.5;
    analogWrite(led,out);
    analogWrite(led1,out);
    delay(2);
  }
}

// Classic police lights effect flashing red and blue
void police()
{
int ledDelay = 50; // delay by 50ms
int redPin = led;
int bluePin = led1;

digitalWrite(redPin, HIGH); // turn the red light on
delay(ledDelay); // wait 50 ms

digitalWrite(redPin, LOW); // turn the red light off
delay(ledDelay); // wait 50 ms

digitalWrite(redPin, HIGH); // turn the red light on
delay(ledDelay); // wait 50 ms

digitalWrite(redPin, LOW); // turn the red light off
delay(ledDelay); // wait 50 ms

digitalWrite(redPin, HIGH); // turn the red light on
delay(ledDelay); // wait 50 ms

digitalWrite(redPin, LOW); // turn the red light off
delay(ledDelay); // wait 50 ms

delay(100); // delay midpoint by 100ms

digitalWrite(bluePin, HIGH); // turn the blue light on
delay(ledDelay); // wait 50 ms

digitalWrite(bluePin, LOW); // turn the blue light off
delay(ledDelay); // wait 50 ms

digitalWrite(bluePin, HIGH); // turn the blue light on
delay(ledDelay); // wait 50 ms

digitalWrite(bluePin, LOW); // turn the blue light off
delay(ledDelay); // wait 50 ms

digitalWrite(bluePin, HIGH); // turn the blue light on
delay(ledDelay); // wait 50 ms

digitalWrite(bluePin, LOW); // turn the blue light off
delay(ledDelay); // wait 50 ms
}



