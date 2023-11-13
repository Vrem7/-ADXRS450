#include "SoftwareSerial.h"
SoftwareSerial mySerial(2, 3); // broshes RX, TX

char junk;
String inputString = "";

void setup() {
  mySerial.begin(9600); pinMode(13, OUTPUT);
}

void loop() {
  if (mySerial.available()) {
    while (mySerial.available()) {
      char inChar = (char) mySerial.read();
      inputString = inChar;
    }
    // Echo vers le terminal
    mySerial.println(inputString);

    // On jette les caractères suivants, si arrivés entre-temps, de façon à avoir un seul caractère dans inputString
    while (mySerial.available() > 0) {
      junk = mySerial.read() ;
    }
    if (inputString == "a") {
      digitalWrite(13, HIGH);
    }
    else if (inputString == "b") {
      digitalWrite(13, LOW);
    }
    inputString = "";
  }
}  // put your setup code here, to run once:
