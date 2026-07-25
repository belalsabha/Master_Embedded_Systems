/*
 * keyPad.c
 *
 *  Created on: Dec 10, 2025
 *  Author: Belal Hani Sabha
 */

#include "KeyPad.h"

// Rows and Columns arrays
uint16_t Rows_KeyPad[] = {R0, R1, R2, R3};
uint16_t Cols_KeyPad[] = {C0, C1, C2, C3};

// Simple delay
void S_delay(uint32_t time) {
    volatile uint32_t i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 255; j++);
}

// Initialize keypad pins
void Keypad_Init() {
    GPIO_Configure_Pin_t PinCfg;

    // Initialize Rows as Output
    for (int i = 0; i < 4; i++) {
        PinCfg.GPOI_Pin_Number = Rows_KeyPad[i];
        PinCfg.GPIO_Mode = output_push_pull;
        PinCfg.GPIO_Output_Frequency = Frequency_10MHz;
        MCAL_GPIO_Init(KEYPAD_PORT , &PinCfg);
    }

    // Initialize Columns as OUTPUT push-pull
    for (int i = 0; i < 4; i++) {
        PinCfg.GPOI_Pin_Number = Cols_KeyPad[i];
        PinCfg.GPIO_Mode = output_push_pull;
        PinCfg.GPIO_Output_Frequency = Frequency_10MHz;
        MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);
    }

        MCAL_GPIO_WritePort(KEYPAD_PORT, 0xFF);

}

// Get pressed key
uint8_t GetData_FromKeyPad() {
    for (int col = 0; col < 4; col++) {
        // Set all columns HIGH
        for (int c = 0; c < 4; c++) {
            MCAL_GPIO_WritePin(KEYPAD_PORT, Cols_KeyPad[c], SET_PIN);
        }

        MCAL_GPIO_WritePin(KEYPAD_PORT, Cols_KeyPad[col], RESET_PIN);


        for (int row = 0; row < 4; row++) {
            if (MCAL_GPIO_ReadPin(KEYPAD_PORT, Rows_KeyPad[row]) == 0) {
                while (MCAL_GPIO_ReadPin(KEYPAD_PORT, Rows_KeyPad[row]) == 0); // waiting

                switch (col) {
                    case 0:
                        if (row == 0) return '7';
                        if (row == 1) return '4';
                        if (row == 2) return '1';
                        if (row == 3) return '?';
                        break;
                    case 1:
                        if (row == 0) return '8';
                        if (row == 1) return '5';
                        if (row == 2) return '2';
                        if (row == 3) return '0';
                        break;
                    case 2:
                        if (row == 0) return '9';
                        if (row == 1) return '6';
                        if (row == 2) return '3';
                        if (row == 3) return '=';
                        break;
                    case 3:
                        if (row == 0) return '/';
                        if (row == 1) return '*';
                        if (row == 2) return '-';
                        if (row == 3) return '+';
                        break;
                }
            }
        }
    }
    return 'N'; // no key pressed
}
