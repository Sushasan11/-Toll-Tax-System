#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int trigPin = 5;
int echoPin = 3;
int ledPin = 13;
int buzzerPin = 11;
int servoPosition = 0;

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  myServo.attach(A3);

  lcd.begin();
  lcd.backlight();
}

void loop() {
  long duration, distance;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <=5) 
  {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000); // Adjust tone frequency for buzzer sound
    delay(300); // Increase the duration of the buzzer sound
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);

    myServo.write(90);
    servoPosition = 90;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance:");
    lcd.setCursor(0, 1);
    lcd.print(distance);
    lcd.print(" cm");
    
    delay(2000); // Display the distance for 2 seconds
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    myServo.write(0);
    servoPosition = 0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WAIT !");
  }

  delay(200);
}
