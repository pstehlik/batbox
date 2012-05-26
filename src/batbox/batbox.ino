/**
 * BatBox - Signaling distance measurements via LEDs using Arduino
 * 
 * Allows connecting 3-pin and 4-pin ultrasonic distance sensors and translating the distance into 
 * LEDs that light up when certain thresholds are hit.
 *
 * For the 3-pin ultrasonic sensor I used a parallax PING))
 *    http://www.parallax.com/StoreSearchResults/tabid/768/txtSearch/PING/List/0/SortField/4/ProductID/92/Default.aspx
 * 
 * For the 4-pin ultrasonic sensor I used a HC-SR04 (much cheaper than the PING)
 *    http://www.amazon.com/gp/product/B004U8TOE6
 *
 * 
 * Variable amount of LEDs can be set up by adding the LED pins to the led array and maintaining the distance (in inch) 
 * that triggers the LEDs pin to turn on.
 *
 * If the LEDs should blink, the blinkDelay can be set to the blink frequency (in msec)
 *
 * To debug your distance measurements you can attach the serial monitor.
 *
 * Copyright May 26th 2012 - Philip Stehlik
 * No warranties given - use as is.
 * 
 */
const int pingPin4 = 4;
const int inPin4 = 12;

const int sigPin3 = 13;

// The LED pins and the distance that triggers the pin to go HIGH
const int leds[4] = {3,2,7,8};
const int dist[4] = {180,60,35,20};
const int ledCount = 4;

const int blinkDelay = 0;

const long loopDelay = 100;

// Stores the distance from the last distance measurement
// Using two sequential measurements to avoid mis-measurement and too much blinking LEDs
long lastDistance4 = -1;
long lastDistance3 = -1;

void setup() { 
  Serial.begin(9600);
  int i;
  for (i = 0; i < ledCount; i = i + 1) {
    pinMode(leds[i], OUTPUT);
  } 
}

void loop() { 
  long duration4, duration3, inches, cm;

  //collecting distance measurement
  duration4 = measure4PinDistance(pingPin4, inPin4);
  duration3 = measure3PinDistance(sigPin3);
  long dist4 = microsecondsToInches(duration4);
  long dist3 = microsecondsToInches(duration3);
  Serial.print(dist4); 
  Serial.print("dist4, "); 
  Serial.print(dist3); 
  Serial.print("dist3"); 
  Serial.println();
  
  int i;
  //blink the LEDs (turn them all off)
  for (i = 0; i < ledCount; i = i + 1) {
    digitalWrite(leds[i], LOW);
  }
  delay(blinkDelay);
  
  // if last measurement and current measurement are below thresholds
  // turn on the respective LEDs 
  for (i = 0; i < ledCount; i = i + 1) {
    if( (lastDistance4 >= 0 && lastDistance4 <= dist[i] && dist4 <= dist[i] )
    ||  (lastDistance3 >= 0 && lastDistance3 <= dist[i] && dist3 <= dist[i] ) 
    ){
      digitalWrite(leds[i], HIGH);
    }
  } 
    
  lastDistance3 = dist3;
  lastDistance4 = dist4;
  delay(loopDelay);
}

/**
 * Measures the distance using a 4-pin ultrasonic distance sensor.
 * pingPin - Trigger pin on sensor
 * inPin   - Echo pin on sensor
 * Returning the measurement in 'raw' format as coming from sensor.
 */
long measure4PinDistance(int pingPin, int inPin){
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(pingPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(pingPin, LOW); 

  pinMode(inPin, INPUT); 

  return pulseIn(inPin, HIGH);;
}

/**
 * Measures the distance using a 3-pin ultrasonic distance sensor.
 * sigPin - Trigger and echo pin on sensor (switching write and read)
 * Returning the measurement in 'raw' format as coming from sensor.
 */
long measure3PinDistance(int sigPin){
  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(sigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(sigPin, LOW); 

  pinMode(sigPin, INPUT); 
  return pulseIn(sigPin, HIGH);  
}


long microsecondsToInches(long microseconds) { 
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf  
  return microseconds / 74 / 2; 
}

long microsecondsToCentimeters(long microseconds) { 
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object take half of the distance travelled.
  return microseconds / 29 / 2; 
}
