/*******************************************************************************
 * @file      main.c
 * @author    Eng - Belal Hani Abu Sabha
 * @brief     toggle led
 * @Created on  Sep 17, 2025

 ******************************************************************************
 */
#include <stdint.h>

typedef volatile unsigned int vuint32_t;

#define RCC_BASE_ 0x40021000
#define GPIO_PORTA_BASE 0x40010800
#define RCC_APB2ENR_ *(volatile uint32_t*) (RCC_BASE_ + 0x18)
#define GPIO_PORTA_CHR *(volatile uint32_t*) (GPIO_PORTA_BASE + 0x04)
#define GPIO_PORTA_ODR *(volatile uint32_t*) (GPIO_PORTA_BASE + 0x0c)

#define RCC_IO_PortA_EN (1<<2)
#define GPIO_portA13 (1UL<<13)

typedef union {
    vuint32_t all_bits;

    struct {
        vuint32_t reserved:13;
        vuint32_t PIN13:1;
    } Pin;
} R_ODR_T;

int main(void) {
    volatile R_ODR_T* _ODR = (volatile R_ODR_T*) (GPIO_PORTA_BASE + 0x0c);

    RCC_APB2ENR_ |= RCC_IO_PortA_EN;
    GPIO_PORTA_CHR &= 0xFF0FFFFF;
    GPIO_PORTA_CHR |= 0x00200000;

    while(1) {
        _ODR->Pin.PIN13 = 1;
        for(int i = 0; i < 5000; i++);

        _ODR->Pin.PIN13 = 0;
        for(int i = 0; i < 5000; i++);
    }

    return 0;
}
