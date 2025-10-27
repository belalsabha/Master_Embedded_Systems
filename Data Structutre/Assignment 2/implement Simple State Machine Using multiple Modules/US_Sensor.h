/*
 * US_Sensor.h
 *
 * Created on: Oct 11 , 2025
 *      Author: Eng - Belal
 */

#ifndef US_SENSOR_H_
#define US_SENSOR_H_
#include"AC.h"
void US_Read_Distance();
void US_Init();
int generate_random_Distance(int l,int r,int count);
void (*Ptr_TO_US_State)();

enum{
	US_Is_Reading_Distance

}US_STATE;

#endif /* US_SENSOR_H_ */
