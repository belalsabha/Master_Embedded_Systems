/*
 * Pressure_Sensor_Driver.h
 *
 *  Created on: 31 Oct 2025
 *      Author: Belal
 */

#ifndef PRESSURE_SENSOR_DRIVER_H_
#define PRESSURE_SENSOR_DRIVER_H_

void PSensor_Init();
void PSensor_waiting();
void PSensor_Read_Pressure();
extern unsigned int Pressure;
extern void (*Ptr_TO_PSensor_State)();








#endif /* PRESSURE_SENSOR_DRIVER_H_ */


