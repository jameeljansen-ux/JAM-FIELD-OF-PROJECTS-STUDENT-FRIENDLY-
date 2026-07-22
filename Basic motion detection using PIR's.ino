// Pin mapping for hardware components
const int pirPin = 2;
const int ledPin = 13;
const int buzzerPin = 8;

// System state variables
int motionState = LOW; 
int sensorValue = 0;   

void setup() {
  // Configure I/O pins
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Initialize serial monitor for system logging
  Serial.begin(9600); 
}

void loop() {
  // Poll the current sensor data
  sensorValue = digitalRead(pirPin);

  if (sensorValue == HIGH) {
    // --- Active Alarm State ---
    
    // Create rapid visual and audio pulse
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000);
    delay(100);
    
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    delay(100); 

    // Log intrusion once per continuous event
    if (motionState == LOW) {
      Serial.println("INTRUDER ALERT: Motion detected!");
      motionState = HIGH; 
    }
    
  } else {
    // --- System Idle State ---
    
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    
    // Log secure state when motion stops
    if (motionState == HIGH) {
      Serial.println("Area secure: No motion.");
      motionState = LOW; 
    }
  }
}