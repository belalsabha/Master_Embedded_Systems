/*
 * App.c
 *
 * Created: 28/12/2025
 * Author : Belal Hani Sabha
 */

#include "I2C.h"
#include "IO.h"
#include "PLATFORM_TYPES.h"

uint8_t data = 0;

#define I2C_MODE_MASTER
//#define I2C_MODE_SLAVE

/* Simple delay */
void Delay_ms(uint16_t ms)
{
    volatile uint16_t i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<1000; j++);
}

/* ================= App Initialization ================= */
void App_Init(void)
{
    I2C_Config_t I2C_Config;

#ifdef I2C_MODE_MASTER
    I2C_Config.Slave_Address = 0x00; // Master's target slave address
    I2C_Config.Speed = Speed_100;
    I2C_Config.Prescaler = Prescaler_1;
    I2C_Config.IRQ_Enable = I2C_IRQ_Disable;
    I2C_Config.Ptr_ISR_Func = 0;

    IOA->DDR = 0xFF; // Port A as output for LEDs or display

#endif

#ifdef I2C_MODE_SLAVE
    I2C_Config.Slave_Address = 0xD0 >> 1; // 7-bit address
    I2C_Config.Speed = Speed_100;
    I2C_Config.Prescaler = Prescaler_1;
    I2C_Config.IRQ_Enable = I2C_IRQ_Disable;
    I2C_Config.Ptr_ISR_Func = 0;

    IOA->DDR = 0xFF; // optional: output to show received data
#endif

    MCAL_I2C_Init(I2C, &I2C_Config);
}

/* ================= App Main Loop ================= */
void App_Run(void)
{
#ifdef I2C_MODE_MASTER
    uint8_t Received_data = MCAL_I2C_Master_Recieve(0xD0);
    IOA->PORT = Received_data; // display received byte
    Delay_ms(500);

#endif

#ifdef I2C_MODE_SLAVE
    MCAL_I2C_Slave_Send(data); // send incrementing byte
    data++;
    Delay_ms(500);
#endif
}
