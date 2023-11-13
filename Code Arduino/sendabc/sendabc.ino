#include <SPI.h>

// Define the SPI pins
#define SS_PIN 10 // Slave Select pin
#define MOSI_PIN 11 // MOSI pin
#define MISO_PIN 12 // MISO pin
#define SCK_PIN 13 // SCK pin

void setup() {
  // Initialize SPI communication
  SPI.begin();
  
  // Configure SPI settings
  SPI.setBitOrder(MSBFIRST); // Most Significant Bit First
  SPI.setDataMode(SPI_MODE0); // Clock Polarity 0, Clock Phase 0
  SPI.setClockDivider(SPI_CLOCK_DIV16); // Set SPI clock frequency to 4MHz
  
  // Configure SS pin as output (master mode)
  pinMode(SS_PIN, OUTPUT);
  
  // Initialize the Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Select the device (set SS pin low)
  digitalWrite(SS_PIN, LOW);
  
    // Wait for a moment before sending again
  delay(1000);

  // Send data to the device
 char data[]={"abc"};
  for (int i = 0; i < sizeof(data)-1; i++) {
    SPI.transfer(data[i]); // Send ASCII code of character
  }
  
  // Deselect the device (set SS pin high)
  digitalWrite(SS_PIN, HIGH);
  
  // Print the sent data to the Serial Monitor
  Serial.print("Sent: ");
  Serial.println(data);
  

}
