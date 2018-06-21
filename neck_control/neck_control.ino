#include <Wire.h>
#include <Servo.h>

//i2c master port
//SDA -> A4
//SCL -> A5

//Class servo
Servo sv_h;
Servo sv_l;



void setup()
{
  sv_h.attach(9, 800, 2300);
  sv_l.attach(10, 800, 2300);
}

void loop()
{
  sv.write(0);  // 0度に設定
  delay(5000);  // 5秒待つ
}
