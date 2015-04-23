

int led = 3;           // the pin that the LED is attached to
int led1 = 5;           // the pin that the LED is attached to

int pir = 2; 

boolean playing = false;

int count =0;

int fnc = 0;
int i;
int on;
int off;
int pulses;
int cycles = 5;

void setup() {
  // put your setup code here, to run once:
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(pir,INPUT);
  randomSeed(analogRead(0));
}

void loop() {
  
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
  

}

void tube()
{
    const int delays[] = {10, 20, 20, 240, 20, 40, 20, 100, 20, 20, 20, 260, 80, 20, 240, 60, 160, 20, 240, 20, 1000, 20, 20, 40, 100, 20, 2740, 340, 860, 20, 1400, 20, 60, 20};

    for(int i=0; i<sizeof(delays)/sizeof(int); ++i) {
        digitalWrite(led, !(i&1));
        digitalWrite(led1, !(i&1));
        delay(delays[i]);
    }
   
}

void fire()
{
analogWrite(led, random(120)+135);
analogWrite(led1, random(120)+135);
delay(random(100)); 
}

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



