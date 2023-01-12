#define BLYNK_TEMPLATE_ID           "YOUR_TEMPLATE_ID"
#define BLYNK_DEVICE_NAME           "Water Tank"
#define BLYNK_AUTH_TOKEN            "YOUR_AUTH_TOKEN"

const int RELAY_PIN = 18;  // the Arduino pin, which connects to the IN pin of relay

#include <NewPing.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_PRINT Serial

// Hook up HC-SR04 with Trig to Arduino Pin 17, Echo to Arduino pin 16
#define TRIGGER_PIN 17
#define ECHO_PIN 16
// Maximum and Zero Levels of water tank (in centimeters)
#define TANK_ZERO 30
#define TANK_MAX 8
// Maximum distance we want to ping for (in centimeters)
#define MAX_DISTANCE 400	

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SSID";
char pass[] = "PASSWORD";

int motor = 1;
double percentage = 0;
BlynkTimer timer;

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

BLYNK_WRITE(V0)   // Switches relay ON/OFF via Dashboard
{
  int pinValue = param.asInt(); // assigning incoming value from pin V0 to a variable
  if(pinValue == 0){
    if(percentage >= 100){
      Blynk.notify("Tank Full"); // Solution to condition not checked after one loop
      Blynk.virtualWrite(V0, 1);
    }
    else{
  digitalWrite(RELAY_PIN, pinValue);
  motor = 1;
  }
  }
  else{
  digitalWrite(RELAY_PIN, pinValue);
  motor = 0;
  }
}


void setup() {
	Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, magic);  // initialize timer to an interval of 1 second
}

void magic(){
  double distance = sonar.ping(); // gets distance from sensor
  distance = distance/100; // convert to centimeters
  percentage = ((TANK_ZERO - TANK_MAX) - (distance - TANK_MAX)) / (TANK_ZERO - TANK_MAX) * 100;
  if (percentage <= 100) {    // Pushes water level to Dashboard
    Blynk.virtualWrite(V4, percentage);
  } else {
    Blynk.virtualWrite(V4, 100);
  }
  if(percentage >= 100 && motor==1)   // Water Pump switch off when Tank is full
  {
    digitalWrite(RELAY_PIN, HIGH);
    motor = 0;
    Blynk.virtualWrite(V0, 1);
  }
}
void loop() {
  Blynk.run();
  timer.run();
}
