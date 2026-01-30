/*
 * App.c
 *
 *  Created on: Jan 28, 2026
 *  Developer & Tester : Eng - Belal Hani Sabha
 */

//----------------------------------
//Includes
//----------------------------------
#include "App.h"

//----------------------------------
//Global Macros
//----------------------------------
#define Red_Led     GPIO_PIN0
#define Green_Led   GPIO_PIN11
#define PIR1	 	GPIO_PIN7
#define PIR2	 	GPIO_PIN1

//----------------------------------
//Global Variables
//----------------------------------
LCD_Configure_t Admin_LCD = {
		GPIOB,
		GPIO_PIN11,   		 								 // RS
		GPIO_PIN2,    										// RW
		GPIO_PIN10,  									   // EN
		LCD_MODE_4BIT, 									  //Mode
		{GPIO_PIN12, GPIO_PIN13, GPIO_PIN14, GPIO_PIN15} // D4-D7 , We enable 4 bit mode
};

LCD_Configure_t Driver_LCD = {
		GPIOA,
		GPIO_PIN5,  										 // RS
		GPIO_PIN4,  										// RW
		GPIO_PIN6,  									   // EN
		LCD_MODE_4BIT,  								  //Mode
		{GPIO_PIN12, GPIO_PIN13, GPIO_PIN14, GPIO_PIN15} // D4-D7 , We enable 4 bit mode
};


uint8_t Authorized_IDs[3] ;
uint8_t Available_Slots = 3;

volatile uint8_t Admin_flag = 0;

// System flags  , use volatile to avoid optimization if the IRQ is not triggered
volatile uint8_t entry_flag = 0;
volatile uint8_t exit_flag = 0;
volatile uint8_t received_car_ID = 0;

//----------------------------------
//Prototypes
//----------------------------------
void Clck_Init(void);											//  >> Test is Done
void USART_Init(void);											//  >> Test is Done
void LCDx_Init(void);											//  >> Test is Done
void Servo_Init(void);											//  >> Test is Done
void LEDs_Init(void);											//  >> Test is Done
void PIR_Init(void);											//  >> Test is Done

void Show_WelcomeScreen(void);									//  >> Test is Done
void Show_SlotsCount(void);										//  >> Test is Done

void Admin_UpdateIDs(void);										//  >> Test is Done
uint8_t GetValidCarID(void);									//  >> Test is Done
uint8_t Waitng_Until_GetData_KeyPad(void);						//  >> Test is Done

void USART1_IRQ_CallBack(void);									//  >> Test is Done
void USART2_IRQ_CallBack(void);									//  >> Test is Done


uint8_t IS_ID_Validate(uint8_t id);								//  >> Test is Done
void Flashing_LED(GPIOx_t* GPIOx, uint16_t pin, uint8_t times);	//  >> Test is Done
void Display_Access_Accepted(uint8_t id, uint8_t is_entry);		//  >> Test is Done
void Display_Access_Denied(uint8_t id);							//  >> Test is Done
void Process_Entry_Gate(void);									//  >> Test is Done
void Process_Exit_Gate(void);									//  >> Test is Done


//----------------------------------
//APIs IMPLEMENTATION
//----------------------------------
//------------------------------------------------------------------------------------------------------------
void APP_Init(void){

	//1- Enable MCAL Drivers
			// >>  Enable Clock , USART , TIMER2 Drivers
			Clck_Init();
			USART_Init();
			Timer2_init();
	//2- Enable HAL Drivers
			// >>  Enable LCD , KeyPad , Servo Drivers
			LCDx_Init();
			HAL_Keypad_Init();
			Servo_Init();
	//3- Enable APP Local Functions
			// >>  Enable LED , PIR , Admin
			LEDs_Init();
			PIR_Init();
			Admin_UpdateIDs();
}
//------------------------------------------------------------------------------------------------------------
void APP_Start(void){

		// Check Admin flag
		if(Admin_flag){
			Admin_flag = 0 ; // Clear flag
			Show_WelcomeScreen(); // then call this function to make driver interface with system
		}
		// Check entry  flag
		if(entry_flag) {
			entry_flag = 0; // Clear flag
			Process_Entry_Gate(); // then call this function to process on  enter gate
		}

		// Check exit  flag
		if(exit_flag) {
			exit_flag = 0; // Clear flag
			Process_Exit_Gate(); // then call this function to process on exit gate
		}

}
//------------------------------------------------------------------------------------------------------------

//----------------------------------
// Local Functions IMPLEMENTATION
//----------------------------------
//------------------------------------------------------------------------------------------------------------
void Clck_Init(void){
	RCC_AFIO_CLK_EN();
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
}
//------------------------------------------------------------------------------------------------------------
void USART_Init(void){
	// ....................USART1...............................
	USART_Config_t usart1_Config;
	usart1_Config.BaudRate     = USART_BaudRate_115200;
	usart1_Config.DataSize     = USART_DataSize_8bit;
	usart1_Config.FlowCtrl     = USART_CTS_RTS_Disable;
	usart1_Config.IRQ_Enable   = USART_IRQ_Enable_RXNEIE;
	usart1_Config.Parity       = USART_Parity_Disable;
	usart1_Config.Ptr_ISR_Func = USART1_IRQ_CallBack;
	usart1_Config.StopBitNo    = USART_StopBitNo_1;
	usart1_Config.USART_Mode   = USART_Mode_TX_RX_Enable;

	MCAL_USART_GPIO_Set_Pins(USART1);
	MCAL_USART_Init(USART1, &usart1_Config);

	// ....................USART2...............................
	USART_Config_t usart2_Config;
	usart2_Config.BaudRate     = USART_BaudRate_115200;
	usart2_Config.DataSize     = USART_DataSize_8bit;
	usart2_Config.FlowCtrl     = USART_CTS_RTS_Disable;
	usart2_Config.IRQ_Enable   = USART_IRQ_Enable_RXNEIE;
	usart2_Config.Parity       = USART_Parity_Disable;
	usart2_Config.Ptr_ISR_Func = USART2_IRQ_CallBack;
	usart2_Config.StopBitNo    = USART_StopBitNo_1;
	usart2_Config.USART_Mode   = USART_Mode_TX_RX_Enable;

	MCAL_USART_GPIO_Set_Pins(USART2);
	MCAL_USART_Init(USART2, &usart2_Config);
}
//------------------------------------------------------------------------------------------------------------
void LCDx_Init(void){
	HAL_LCD_Init(&Admin_LCD);
	HAL_LCD_Init(&Driver_LCD);
	dms(50);
}
//------------------------------------------------------------------------------------------------------------
void Servo_Init(void){
	Servo1_Entry_Gate_Init();
	Servo2_Exit_Gate_Init();
}
//------------------------------------------------------------------------------------------------------------
void LEDs_Init(void){
	GPIO_Configure_Pin_t Pin;
	Pin.GPIO_Mode = output_push_pull;
	Pin.GPIO_Output_Frequency = Frequency_10MHz;

	//Red LED
	Pin.GPOI_Pin_Number = Red_Led;
	MCAL_GPIO_Init(GPIOA, &Pin);
	MCAL_GPIO_WritePin(GPIOA, Red_Led, SET_PIN);

	//Green LED
	Pin.GPOI_Pin_Number = Green_Led;
	MCAL_GPIO_Init(GPIOA, &Pin);
	MCAL_GPIO_WritePin(GPIOA, Green_Led, SET_PIN);
}
//------------------------------------------------------------------------------------------------------------
void PIR_Init(void){
	GPIO_Configure_Pin_t Pin;
	Pin.GPIO_Mode = GPIO_Floating_Input;

	//PIR1
	Pin.GPOI_Pin_Number = PIR1;
	MCAL_GPIO_Init(GPIOA, &Pin);

	//PIR2
	Pin.GPOI_Pin_Number = PIR2;
	MCAL_GPIO_Init(GPIOA, &Pin);
}
//------------------------------------------------------------------------------------------------------------


//----------------------------------
//Admin Functions
//----------------------------------
//------------------------------------------------------------------------------------------------------------
uint8_t GetValidCarID(void)
{
	uint8_t id = 0;

	HAL_Clear_LCD_Screen(&Admin_LCD);
	dms(50);

	HAL_Write_String_onLCD(&Admin_LCD,"Enter Car ID");
	HAL_Control_LCD_Lines_And_Cursor(&Admin_LCD, 2, 0);
	dms(50);

	while(id == 0)
	{
		id = Waitng_Until_GetData_KeyPad() - '0';

		if(id > 0)
		{
			HAL_Display_Number_onLCD(&Admin_LCD, id);
			dms(100);
		}
	}

	return id;
}
//------------------------------------------------------------------------------------------------------------
void Admin_UpdateIDs(void)
{
	uint8_t Admin_ID = 0;

	HAL_Clear_LCD_Screen(&Admin_LCD);
	dms(50);

	HAL_Write_String_onLCD(&Admin_LCD,"Enter Admin ID");
	HAL_Control_LCD_Lines_And_Cursor(&Admin_LCD, 2, 0);
	dms(50);

	while(Admin_ID == 0)
	{
		Admin_ID = Waitng_Until_GetData_KeyPad() - '0';

		if(Admin_ID > 0)
		{
			HAL_Display_Number_onLCD(&Admin_LCD, Admin_ID);
			dms(100);
		}
	}

	if(Admin_ID == 7)
	{
		HAL_Clear_LCD_Screen(&Admin_LCD);
		dms(50);

		HAL_Write_String_onLCD(&Admin_LCD, "Valid Login");
		dms(500);

		for(uint8_t i = 0; i < 3; i++)
		{
			HAL_Clear_LCD_Screen(&Admin_LCD);
			dms(50);

			HAL_Write_String_onLCD(&Admin_LCD,"Enter ID ");
			HAL_Display_Number_onLCD(&Admin_LCD, i + 1);
			dms(100);

			Authorized_IDs[i] = GetValidCarID();

			HAL_Clear_LCD_Screen(&Admin_LCD);
			dms(50);

			HAL_Write_String_onLCD(&Admin_LCD, "ID Added: ");
			HAL_Display_Number_onLCD(&Admin_LCD, Authorized_IDs[i]);
			dms(500);
		}

		HAL_Clear_LCD_Screen(&Admin_LCD);
		dms(50);

		HAL_Write_String_onLCD(&Admin_LCD,"IDs Stored:");
		dms(500);

		HAL_Control_LCD_Lines_And_Cursor(&Admin_LCD, 2, 0);
		HAL_Display_Number_onLCD(&Admin_LCD, Authorized_IDs[0]);
		HAL_Write_Character_onLCD(&Admin_LCD, ' ');
		dms(50);

		HAL_Display_Number_onLCD(&Admin_LCD, Authorized_IDs[1]);
		HAL_Write_Character_onLCD(&Admin_LCD, ' ');
		dms(50);

		HAL_Display_Number_onLCD(&Admin_LCD, Authorized_IDs[2]);
		dms(500);

		Admin_flag = 1 ;
	}
	else
	{
		HAL_Clear_LCD_Screen(&Admin_LCD);
		dms(50);

		HAL_Write_String_onLCD(&Admin_LCD,"Invalid Login");
		HAL_Control_LCD_Lines_And_Cursor(&Admin_LCD, 2, 0);
		HAL_Write_String_onLCD(&Admin_LCD,"Try Again");
		dms(2000);
		HAL_Clear_LCD_Screen(&Admin_LCD);
		HAL_Write_String_onLCD(&Admin_LCD,"You Must");
		HAL_Control_LCD_Lines_And_Cursor(&Admin_LCD, 2, 0);
		HAL_Write_String_onLCD(&Admin_LCD,"Reset System...");
		dms(3000);
	}

	HAL_Clear_LCD_Screen(&Admin_LCD);
	dms(50);
}
//------------------------------------------------------------------------------------------------------------
uint8_t Waitng_Until_GetData_KeyPad(void)
{
	uint8_t key = 0;

	while(key == 0 || key == 'N')
	{
		key = HAL_GetData_FromKeyPad();
		dms(10);
	}

	dms(10);
	return key;
}
//------------------------------------------------------------------------------------------------------------

//----------------------------------
//Driver Functions
//----------------------------------
//------------------------------------------------------------------------------------------------------------
void Show_WelcomeScreen(void){
	HAL_Clear_LCD_Screen(&Driver_LCD);
	dms(50);

	HAL_Write_String_onLCD(&Driver_LCD, "Welcome in");
	HAL_Control_LCD_Lines_And_Cursor(&Driver_LCD, 2,0);
	HAL_Write_String_onLCD(&Driver_LCD, "Belal's Parking");
	dms(500);

	HAL_Clear_LCD_Screen(&Driver_LCD);
	dms(50);

	if(Available_Slots > 0){
		HAL_Write_String_onLCD(&Driver_LCD, "Empty Slots: ");
		Show_SlotsCount();
		dms(500);

		HAL_Clear_LCD_Screen(&Driver_LCD);
		dms(50);

		HAL_Write_String_onLCD(&Driver_LCD, "Put Your ID");
		HAL_Control_LCD_Lines_And_Cursor(&Driver_LCD, 2,0);
		HAL_Write_String_onLCD(&Driver_LCD, "in Card Reader");
		dms(100);
	}else{
		HAL_Write_String_onLCD(&Driver_LCD, "Parking Full");
		HAL_Control_LCD_Lines_And_Cursor(&Driver_LCD, 2,0);
		HAL_Write_String_onLCD(&Driver_LCD, "No Empty Slots");
		dms(500);
	}
}
//------------------------------------------------------------------------------------------------------------
void Show_SlotsCount(void){
	HAL_Display_Number_onLCD(&Driver_LCD,Available_Slots);
	dms(50);
}


//----------------------------------
//  Process Functions Will Called When ISR Flags Enabled
//----------------------------------

//------------------------------------------------------------------------------------------------------------
uint8_t IS_ID_Validate(uint8_t id) {

	return (id == Authorized_IDs[0]) || (id == Authorized_IDs[1]) || (id == Authorized_IDs[2]);
}
//------------------------------------------------------------------------------------------------------------
void Flashing_LED(GPIOx_t* GPIOx, uint16_t pin, uint8_t times) {
	for(uint8_t i = 0; i < times; i++) {
		MCAL_GPIO_WritePin(GPIOx, pin, RESET_PIN);
		dms(150);
		MCAL_GPIO_WritePin(GPIOx, pin, SET_PIN);
		dms(100);
	}
}
//------------------------------------------------------------------------------------------------------------
void Display_Access_Accepted(uint8_t id, uint8_t is_entry) {
	HAL_Clear_LCD_Screen(&Driver_LCD);
	dms(50);
	HAL_Write_String_onLCD(&Driver_LCD, "Correct ID: ");
	HAL_Display_Number_onLCD(&Driver_LCD, id);
	HAL_Control_LCD_Lines_And_Cursor(&Driver_LCD, 2, 0);
	HAL_Write_String_onLCD(&Driver_LCD, is_entry ? "Entry Gate Opens" : "Exit Gate Opens");
	dms(250);
	Flashing_LED(GPIOA, Green_Led, 2);
}
//------------------------------------------------------------------------------------------------------------
void Display_Access_Denied(uint8_t id) {
	HAL_Clear_LCD_Screen(&Driver_LCD);
	dms(50);
	HAL_Write_String_onLCD(&Driver_LCD, "Wrong ID: ");
	HAL_Display_Number_onLCD(&Driver_LCD, id);
	HAL_Control_LCD_Lines_And_Cursor(&Driver_LCD, 2, 0);
	HAL_Write_String_onLCD(&Driver_LCD, "Access Denied");
	dms(250);
	Flashing_LED(GPIOA, Red_Led, 2);
	dms(200);
}
//------------------------------------------------------------------------------------------------------------
void Process_Entry_Gate(void) {
	uint8_t id = received_car_ID;
	if(Available_Slots == 0) {
		HAL_Clear_LCD_Screen(&Driver_LCD);
		dms(50);
		HAL_Write_String_onLCD(&Driver_LCD, "No Empty Slots");
		HAL_Control_LCD_Lines_And_Cursor(&Driver_LCD, 2, 0);
		HAL_Write_String_onLCD(&Driver_LCD, "Parking Full");
		dms(300);
		Show_WelcomeScreen();
		return;
	}

	if(MCAL_GPIO_ReadPin(GPIOA, PIR1) == 1) {
		HAL_Clear_LCD_Screen(&Driver_LCD);
		dms(50);
		HAL_Write_String_onLCD(&Driver_LCD, "Plz Wait Gate");
		HAL_Control_LCD_Lines_And_Cursor(&Driver_LCD, 2, 0);
		HAL_Write_String_onLCD(&Driver_LCD, "Is Still Open ");
		dms(1000);
		Show_WelcomeScreen();
		return;
	}

	if(!IS_ID_Validate(id)) {
		Display_Access_Denied(id);
		Show_WelcomeScreen();
		return;
	}

	Available_Slots--;
	Display_Access_Accepted(id, 1);

	HAL_Clear_LCD_Screen(&Driver_LCD);
	dms(50);
	HAL_Write_String_onLCD(&Driver_LCD, "Gate Opening...");
	dms(30);
	Servo1_Entry_Gate(UP);

	HAL_Control_LCD_Lines_And_Cursor(&Driver_LCD, 2, 0);
	HAL_Write_String_onLCD(&Driver_LCD, "Please Enter");

	while(MCAL_GPIO_ReadPin(GPIOA, PIR1) == 1);
	dms(50);

	HAL_Clear_LCD_Screen(&Driver_LCD);
	dms(50);
	HAL_Write_String_onLCD(&Driver_LCD, "Gate Closing...");
	dms(30);
	Servo1_Entry_Gate(Down);
	dms(800);

	Show_WelcomeScreen();
}
//------------------------------------------------------------------------------------------------------------
void Process_Exit_Gate(void) {
	uint8_t id = received_car_ID;
	if(Available_Slots == 3) {
		HAL_Clear_LCD_Screen(&Driver_LCD);
		dms(50);
		HAL_Write_String_onLCD(&Driver_LCD, "Parking Is Empty");
		HAL_Control_LCD_Lines_And_Cursor(&Driver_LCD, 2, 0);
		HAL_Write_String_onLCD(&Driver_LCD, "No Cars Inside");
		dms(500);
		Show_WelcomeScreen();
		return;
	}

	if(MCAL_GPIO_ReadPin(GPIOA, PIR2) == 1) {
		HAL_Clear_LCD_Screen(&Driver_LCD);
		dms(50);
		HAL_Write_String_onLCD(&Driver_LCD, "Please Wait  Gate");
		HAL_Control_LCD_Lines_And_Cursor(&Driver_LCD, 2, 0);
		HAL_Write_String_onLCD(&Driver_LCD, "Is Still Open");
		dms(500);
		Show_WelcomeScreen();
		return;
	}

	if(!IS_ID_Validate(id)) {
		Display_Access_Denied(id);
		Show_WelcomeScreen();
		return;
	}

	Available_Slots++;
	Display_Access_Accepted(id, 0);

	HAL_Clear_LCD_Screen(&Driver_LCD);
	dms(50);
	HAL_Write_String_onLCD(&Driver_LCD, "Gate Opening...");
	dms(30);
	Servo2_Exit_Gate(UP);

	HAL_Control_LCD_Lines_And_Cursor(&Driver_LCD, 2, 0);
	HAL_Write_String_onLCD(&Driver_LCD, "Please Exit");

	while(MCAL_GPIO_ReadPin(GPIOA, PIR2) == 1);
	dms(50);

	HAL_Clear_LCD_Screen(&Driver_LCD);
	dms(50);
	HAL_Write_String_onLCD(&Driver_LCD, "Gate Closing...");
	dms(30);
	Servo2_Exit_Gate(Down);
	dms(500);

	Show_WelcomeScreen();
}
//------------------------------------------------------------------------------------------------------------

//----------------------------------
//USART ISR >> Use ISRs Just Enable Flags
//----------------------------------
//------------------------------------------------------------------------------------------------------------
void USART1_IRQ_CallBack(void){
	uint16_t carID;

	MCAL_USART_ReceiveData(USART1, &carID, 0);
	carID = carID - '0';

	uint8_t Terminal_Data = carID + '0';
	MCAL_USART_SendData(USART1, &Terminal_Data, 1);

	received_car_ID = carID;
	entry_flag = 1;
}
//------------------------------------------------------------------------------------------------------------
void USART2_IRQ_CallBack(void){
	uint16_t carID;

	MCAL_USART_ReceiveData(USART2, &carID, 0);
	carID = carID - '0';

	uint8_t Terminal_Data = carID + '0';
	MCAL_USART_SendData(USART2, &Terminal_Data, 1);

	received_car_ID = carID;
	exit_flag = 1;
}
