#include <Servo.h>
Servo myservo;

void setup() {
  myservo.attach(9);
}

void loop() {
  tournerServoLentement(0);
  tournerServoLentement(180);
}

void tournerServoLentement(int angle) {
  int increment = 1; // pas de mouvement
  int delayTime = 18; // temps de pause entre chaque mouvement (plus le temps est long, plus le mouvement est lent)

  int currentPosition = myservo.read();
  if (angle < currentPosition) {
    increment = -1; // mouvement dans le sens inverse si l'angle cible est inférieur à la position actuelle
  }
  
  for (int i = currentPosition; i != angle; i += increment) {
    myservo.write(i);
    delay(delayTime);
  }
  
  myservo.write(angle);
  delay(delayTime);
}
