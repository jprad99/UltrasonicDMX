#include <DmxSimple.h>

// defines pins numbers
const int trigPin = 8;
const int echoPin = 7;
// defines variables
int time_on = 2; //time on in seconds
long duration;
int distance = 0;
int last_distance = 0;
int counter = 0;
int trigdist = 120;
int trigcount = 3;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  Serial.begin(9600); // Starts the serial communication
}
int check_dist() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  return distance;
}
void DMX_standby() {
  DmxSimple.write(1, 0);
}
void DMX_on() {
  DmxSimple.write(1,255);
}

void loop() {
  distance = check_dist();
  if (distance <= trigdist) {
    counter = counter +1;
  }
  if (counter <= trigcount - 1 && distance > trigdist) {
    counter = 0;
  }
  if (counter >= trigcount) {
    DMX_on();
    delay(time_on*1000);
    DMX_standby();
    counter = 0;
  }
}
