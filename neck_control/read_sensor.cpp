#include <MsTimer2.h>
#include <Wire.h> //Access to I2C
#include "read_sensor.h"
#include "struct.h"
#include "global.h"

void read_sensor() {

  int error;
  // 加速度、角速度の読み出し
  // accel_t_gyroは読み出した値を保存する構造体、その後ろの引数は取り出すバイト数
  error = MPU6050_read(MPU6050_ACCEL_XOUT_H, (uint8_t *)&accel_t_gyro, sizeof(accel_t_gyro));  
}

// MPU6050_read
int MPU6050_read(int start, uint8_t *buffer, int size) {
  int i, n, error;
  Wire.beginTransmission(MPU6050_I2C_ADDRESS);
  n = Wire.write(start);
  if (n != 1) {
    return (-10);
  }
  n = Wire.endTransmission(false);// hold the I2C-bus
  if (n != 0) {
    return (n);
  }
  // Third parameter is true: relase I2C-bus after data is read.
  Wire.requestFrom(MPU6050_I2C_ADDRESS, size, true);
  i = 0;
  while (Wire.available() && i < size) {
    buffer[i++] = Wire.read();
  }
  if ( i != size) {
    return (-11);
  }
  return (0); // return : no error
}

// MPU6050_write
int MPU6050_write(int start, const uint8_t *pData, int size) {
  int n, error;
  Wire.beginTransmission(MPU6050_I2C_ADDRESS);
  n = Wire.write(start);// write the start address
  if (n != 1) {
    return (-20);
  }
  n = Wire.write(pData, size);// write data bytes
  if (n != size) {
    return (-21);
  }
  error = Wire.endTransmission(true); // release the I2C-bus
  if (error != 0) {
    return (error);
  }

  return (0);// return : no error
}

// MPU6050_write_reg
int MPU6050_write_reg(int reg, uint8_t data) {
  int error;
  error = MPU6050_write(reg, &data, 1);
  return (error);
};
