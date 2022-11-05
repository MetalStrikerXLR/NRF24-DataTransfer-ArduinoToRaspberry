#include <SPI.h>
#include <RF24.h>

// Defining nRF24L01 pins and address
RF24 radio(9, 10);                                                // CE, CSN

// Radio pipe addresses
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };     // This address should be same on receiving side (Raspberry Pi)

// Defining Ultrasonic Pins
#define echoPin 2                                                 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3                                                 // attach pin D3 Arduino to pin Trig of HC-SR04

// define variables
long duration = 0;                                                // variable for the duration of sound wave travel
float distance;                                                  // variable for the distance measurement

void setup() 
{
  Serial.begin(9600);
  Serial.println("Initializing...");
  
  // Initialize the Ultrasonic Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize nRF24L01
  radio.begin();
  radio.enableDynamicPayloads();    // Set Dynamic Payload capability
  radio.setRetries(5, 15);          // Set Retries
  radio.openWritingPipe(pipes[0]);  // Setting the address
  radio.setPALevel(RF24_PA_MAX);    // Setting Transmission Power (Maximum)
  radio.stopListening();            // Enable Transmission mode

  Serial.println("Iniitialization Complete");
}

void loop() 
{
  // Clear the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin HIGH for 10 microseconds - transmit sound wave
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin and get sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2;        // Speed of sound wave divided by 2 (go and back)
  char stringBuffer[6];                   // Buffer big enough for 5-character float
  dtostrf(distance, 6, 2, stringBuffer);  // Leave room for too large numbers!
  
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send the distance value over nRF24L01 module
  radio.write(&stringBuffer, sizeof(stringBuffer));
  Serial.println("Data Transmitted");
  Serial.println("");
  
  // Wait 1s before next reading
  delay(1000);
}
