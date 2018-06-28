// MPU-6050 Accelerometer + Gyro

/*----i2c master port-----*/
//SDA -> A4
//SCL -> A5
/*------------------------*/

#include <Wire.h> //Access to I2C
#include <Servo.h> //Control servo
#include <MsTimer2.h>
#include "struct.h"
#include "read_sensor.h"
#include "global.h"

void setup()
{
  sv_h.attach(9, 800, 2300);
  sv_l.attach(10, 800, 2300);

  int error;
  uint8_t c;

  Wire.begin();

  // baud rate 9600bps
  Serial.begin(9600);
  Serial.print("InvenSense MPU-6050");
  Serial.print("June 2012");

  // 初回の読み出し
  error = MPU6050_read(MPU6050_WHO_AM_I, &c, 1);
  Serial.print("WHO_AM_I : ");
  Serial.print(c, HEX);
  Serial.print(", error = ");
  Serial.println(error, DEC);

  // 動作モードの読み出し
  error = MPU6050_read(MPU6050_PWR_MGMT_1, &c, 1);
  Serial.print("PWR_MGMT_1 : ");
  Serial.print(c, HEX);
  Serial.print(", error = ");
  Serial.println(error, DEC);

  // MPU6050動作開始
  MPU6050_write_reg(MPU6050_PWR_MGMT_1, 0);

  MsTimer2::set(100, read_sensor);
  MsTimer2::start();

}

void loop() {

  // 取得できるデータはビッグエンディアンなので上位バイトと下位バイトの入れ替え（AVRはリトルエンディアン）
  uint8_t swap;
#define SWAP(x,y) swap = x; x = y; y = swap
  SWAP (accel_t_gyro.reg.x_accel_h, accel_t_gyro.reg.x_accel_l);
  SWAP (accel_t_gyro.reg.y_accel_h, accel_t_gyro.reg.y_accel_l);
  SWAP (accel_t_gyro.reg.z_accel_h, accel_t_gyro.reg.z_accel_l);
  SWAP (accel_t_gyro.reg.t_h, accel_t_gyro.reg.t_l);
  SWAP (accel_t_gyro.reg.x_gyro_h, accel_t_gyro.reg.x_gyro_l);
  SWAP (accel_t_gyro.reg.y_gyro_h, accel_t_gyro.reg.y_gyro_l);
  SWAP (accel_t_gyro.reg.z_gyro_h, accel_t_gyro.reg.z_gyro_l);

  // 取得した加速度値を分解能で割って加速度(G)に変換する
  float acc_x = accel_t_gyro.value.x_accel / 16384.0; //FS_SEL_0 16,384 LSB / g
  float acc_y = accel_t_gyro.value.y_accel / 16384.0;
  float acc_z = accel_t_gyro.value.z_accel / 16384.0;

  Serial.print(acc_x, 2);
  Serial.print("\t");
  Serial.print(acc_y, 2);
  Serial.print("\t");
  Serial.print(acc_z, 2);
  Serial.print("\t");

  // 加速度からセンサ対地角を求める
  float acc_angle_x = atan2(acc_x, acc_z) * 360 / 2.0 / PI;
  float acc_angle_y = atan2(acc_y, acc_z) * 360 / 2.0 / PI;
  float acc_angle_z = atan2(acc_x, acc_y) * 360 / 2.0 / PI;

  Serial.print(acc_angle_x, 2);
  Serial.print("\t");
  Serial.print(acc_angle_y, 2);
  Serial.print("\t");
  Serial.print(acc_angle_z, 2);
  Serial.print("\t");

  // 取得した角速度値を分解能で割って角速度(degrees per sec)に変換する
  float gyro_x = accel_t_gyro.value.x_gyro / 131.0;//FS_SEL_0 131 LSB / (°/s)
  float gyro_y = accel_t_gyro.value.y_gyro / 131.0;
  float gyro_z = accel_t_gyro.value.z_gyro / 131.0;

  Serial.print(gyro_x, 2);
  Serial.print("\t");
  Serial.print(gyro_y, 2);
  Serial.print("\t");
  Serial.print(gyro_z, 2);
  Serial.println("");

  
}


