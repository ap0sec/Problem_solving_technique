#ifndef _read_sensor_h
#define _read_sensor_h

void read_sensor();
int MPU6050_read(int start, uint8_t *buffer, int size);
int MPU6050_write(int start, const uint8_t *pData, int size);
int MPU6050_write_reg(int reg, uint8_t data);

#endif
