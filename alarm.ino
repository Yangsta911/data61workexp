#include <Servo.h>
#include <TimeAlarms.h>
#include <TimeLib.h>

Servo servo;
AlarmId id;

void setup() {
  Serial.begin(9600);
  servo.attach(8);
  servo.write(0);
  Alarm.delay(2000);
  setTime(15,20,0,1,1,11);
  Alarm.alarmRepeat(11,00,0, MorningAlarm);
 
}
void loop(){
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display

}

void MorningAlarm() {
  servo.write(0);
  Alarm.delay(250);
  servo.write(250);
  Alarm.delay(250);
  servo.write(0);
  Alarm.delay(250);
  servo.write(250);
  Alarm.delay(250);
  servo.write(0);
  Alarm.delay(250);
  servo.write(250);
  Alarm.delay(250);
    servo.write(0);
  Alarm.delay(250);
  servo.write(250);
  Alarm.delay(250);
}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

