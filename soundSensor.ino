const int soundSensorPin = A0;    // Analog pin connected to the sound sensor
const int redPin = 9;             // PWM pin for red LED channel
const int greenPin = 10;          // PWM pin for green LED channel
const int bluePin = 11;           // PWM pin for blue LED channel

int threshold = 100;               // Sound level threshold to trigger change
unsigned long lastTime = 0;       // Timestamp of the last state change
unsigned long debounceDelay = 300; // Minimum interval between triggers (ms)

int state = 0;                    // Current LED state: 0=red, 1=green, 2=blue, 3=off

void setup() {
  pinMode(redPin, OUTPUT);        // Set red LED pin as output
  pinMode(greenPin, OUTPUT);      // Set green LED pin as output
  pinMode(bluePin, OUTPUT);       // Set blue LED pin as output
  Serial.begin(9600);             // Start serial for debugging sound readings
}

void loop() {
  int soundValue = analogRead(soundSensorPin);  // Read sound sensor value
  Serial.println(soundValue);                   // Print value for monitoring

  // If sound exceeds threshold and debounce time has passed...
  if (soundValue > threshold && (millis() - lastTime) > debounceDelay) {
    state = (state + 1) % 4;    // Cycle through 0→1→2→3→0
    lastTime = millis();        // Update last trigger time
    updateColor();              // Apply new LED color based on state
  }
}

void updateColor() {
  switch (state) {
    case 0: // RED state
      digitalWrite(redPin, HIGH);   // Turn red LED on
      digitalWrite(greenPin, LOW);  // Ensure green LED is off
      digitalWrite(bluePin, LOW);   // Ensure blue LED is off
      break;
    case 1: // GREEN state
      digitalWrite(redPin, LOW);    // Ensure red LED is off
      digitalWrite(greenPin, HIGH); // Turn green LED on
      digitalWrite(bluePin, LOW);   // Ensure blue LED is off
      break;
    case 2: // BLUE state
      digitalWrite(redPin, LOW);    // Ensure red LED is off
      digitalWrite(greenPin, LOW);  // Ensure green LED is off
      digitalWrite(bluePin, HIGH);  // Turn blue LED on
      break;
    case 3: // OFF state
      digitalWrite(redPin, LOW);    // Turn red LED off
      digitalWrite(greenPin, LOW);  // Turn green LED off
      digitalWrite(bluePin, LOW);   // Turn blue LED off
      break;
  }
}
