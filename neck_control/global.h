#ifndef _global_h
#define _global_h

#include <Servo.h>

extern Servo sv_h;
extern Servo sv_l;

// Register address for MPU6050
#define MPU6050_ACCEL_XOUT_H 0x3B  // R  
#define MPU6050_WHO_AM_I     0x75  // R
#define MPU6050_PWR_MGMT_1   0x6B  // R/W
#define MPU6050_I2C_ADDRESS  0x68

extern accel_t_gyro_union accel_t_gyro;

#endif
