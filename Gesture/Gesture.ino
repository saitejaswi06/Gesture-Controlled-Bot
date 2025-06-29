#include <ESP8266WiFi.h>

// Wi-Fi credentials
const char* ssid = "wifi name";          // Replace with your Wi-Fi SSID
const char* password = "password";    // Replace with your Wi-Fi password

WiFiServer server(80);                 // Create a server listening on port 80

// Motor control pins (L293D)
const int EN1 = D5;          // Enable for Motor A
const int motorA_in1 = D1;   // IN1 for Motor A
const int motorA_in2 = D2;   // IN2 for Motor A

const int EN2 = D6;          // Enable for Motor B
const int motorB_in3 = D3;   // IN3 for Motor B
const int motorB_in4 = D4;   // IN4 for Motor B

void setup() {
  Serial.begin(115200);

  // Initialize motor control pins as OUTPUT
  pinMode(EN1, OUTPUT);
  pinMode(motorA_in1, OUTPUT);
  pinMode(motorA_in2, OUTPUT);

  pinMode(EN2, OUTPUT);
  pinMode(motorB_in3, OUTPUT);
  pinMode(motorB_in4, OUTPUT);

  // Enable both motors by setting Enable pins HIGH initially (PWM duty cycle can be adjusted)
  analogWrite(EN1, 255);   // Full speed (255 = max PWM)
  analogWrite(EN2, 255);   // Full speed (255 = max PWM)

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to Wi-Fi...");
  }

  Serial.print("Connected to Wi-Fi. IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Check for incoming clients
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected");

    while (client.connected()) {
      if (client.available()) {
        // Read the gesture index sent by the client
        String gesture = client.readStringUntil('\n');
        gesture.trim(); // Remove any extra spaces or newlines

        Serial.print("Received Gesture Index: ");
        Serial.println(gesture);

        // Convert the received gesture to an integer
        int gestureIndex = gesture.toInt();

        // Execute motor actions based on the gesture index
        executeMotorAction(gestureIndex);
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}

// Function to control motors based on gesture index
void executeMotorAction(int gestureIndex) {
  switch (gestureIndex) {
    case 0:
      moveForward();
      break;
    case 1:
      moveBackward();
      break;
    case 2:
      turnLeft();
      break;
    case 3:
      turnRight();
      break;
    case 4:
      stopMotors();
      break;
    default:
      Serial.println("Unknown gesture, stopping motors");
      stopMotors();
      break;
  }
}

// Motor control functions
void moveForward() {
  analogWrite(EN1, 255);
  analogWrite(EN2,255);
  digitalWrite(motorA_in1,HIGH);
  digitalWrite(motorA_in2,LOW);
  digitalWrite(motorB_in3,HIGH);
  digitalWrite(motorB_in4,LOW);
}

void moveBackward() {
analogWrite(EN1, 255);
  analogWrite(EN2,255);
  digitalWrite(motorA_in1,LOW);
  digitalWrite(motorA_in2,HIGH);
  digitalWrite(motorB_in3,LOW);
  digitalWrite(motorB_in4,HIGH);
   // Full speed
}

void turnLeft() {
  
  analogWrite(EN1, 150);
  analogWrite(EN2,150);
  digitalWrite(motorA_in1,LOW);
  digitalWrite(motorA_in2,HIGH);
  digitalWrite(motorB_in3,HIGH);
  digitalWrite(motorB_in4,LOW);
 
}

void turnRight() {
    analogWrite(EN1, 150);
  analogWrite(EN2,150);
  digitalWrite(motorA_in1,HIGH);
  digitalWrite(motorA_in2,LOW);
  digitalWrite(motorB_in3,LOW);
  digitalWrite(motorB_in4,HIGH);
  
}

void stopMotors() {
  analogWrite(EN1, 0);
  analogWrite(EN2,0);
  digitalWrite(motorA_in1,LOW);
  digitalWrite(motorA_in2,LOW);
  digitalWrite(motorB_in3,LOW);
  digitalWrite(motorB_in4,LOW);
  
  
}