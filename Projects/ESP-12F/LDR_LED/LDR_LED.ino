/*
 * The following program takes values from the LDR (0~1023)
 * with 0 being detecting no light at all and 1023  the brightest
 * intensity, from the value of the LDR, outputs the same brightness
 * level onto the RGB LEDs placed at the pins (numbers in global vars)
 * The LEDs are turned on first one at a time, then twice then all at once
 */
 
const int LDR = A0;
const int RED = 15;
const int BLUE = 13;
const int GREEN = 12;

void setup() {
  pinMode(LDR,INPUT);
  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);
}

void loop() {
  // turn on one LED, turn off all, turn on two, turn of all, then turn on all
  byebye2(RED,GREEN);
  byebye(BLUE);
  delay(500);
  one_at_a_time();
  byebye2(RED,GREEN);
  byebye(BLUE);
  delay(500);
  two_at_a_time();
  byebye2(RED,GREEN);
  byebye(BLUE);
  delay(500);  
  pump_up_the_lights();
}

//<-------Function that turns off a respective LED------->\\

void byebye(int a)
{
  analogWrite(a,0);  
}

//<-------Function that turns off two respective LEDs------->\\

void byebye2(int a, int b)
{
  analogWrite(a, 0);
  analogWrite(b, 0);  
}

//<-------Function that turns on an LED------->\\

void lightup(int a)
{
  analogWrite(a,analogRead(LDR));
}

//<-------Function that turns on two LEDs------->\\

void lightup2(int a, int b)
{
  analogWrite(a,analogRead(LDR));
  analogWrite(b,analogRead(LDR));      
}

/*
 * The following functions use the helper functions above
 * to light up one LED each first, then two at a time and
 * then finally turns on all the LEDs. Note that at all 
 * times the brightness of the LEDs depend on the ambient
 * lighting conditions of the room since we are using the
 * LDR to control the brightness
 */
 
void one_at_a_time(void)
{
  byebye2(GREEN,BLUE);  
  lightup(RED);
  delay(1000);
  byebye2(RED,BLUE);
  lightup(GREEN);
  delay(1000);
  byebye2(RED,GREEN);
  lightup(BLUE);
  delay(1000);  
}

void two_at_a_time(void)
{
  byebye(BLUE);
  lightup2(RED,GREEN);
  delay(1000);
  byebye(GREEN);
  lightup2(RED,BLUE);
  delay(1000);
  byebye(RED);
  lightup2(GREEN,BLUE);
  delay(1000);    
}

void pump_up_the_lights()
{
  int i=0;
  byebye2(GREEN,BLUE);
  i=analogRead(LDR);
  analogWrite(RED,i);
  analogWrite(GREEN,i);
  analogWrite(BLUE,i);
  delay(1000);  
}
