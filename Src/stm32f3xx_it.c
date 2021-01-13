/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2021 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

/* USER CODE BEGIN 0 */
#include <stdbool.h>
#include "LiquidCrystal.h"
#define MAX(a,b) ((a) > (b) ? (a) : (b))
const int FADE_INTERVAL = 10;
int lastTickKeypad = 0;
char pushedButton = 0;

enum Menu {MAIN, STATUS, ACTIVATE, PASSWORD, ABOUT};
enum Menu menu = STATUS;

int temp = 0;
float scaledTemp = 0;
int volume = 0;
float scaledVolume = 0;
int mixedTempVolume = 0, index7seg = 0;


bool isAlarmActive = true;
bool isAlarmRinging = false;


struct Room{
	bool isOn;
	int fade;
	uint16_t channel;
	uint16_t buttonPin;
	GPIO_TypeDef* buttonTypeDef;
};

extern struct Room rooms[4];

extern RTC_TimeTypeDef myTime;
extern RTC_DateTypeDef myDate;

extern ADC_HandleTypeDef hadc1,hadc2,hadc4;
extern RTC_HandleTypeDef hrtc;

void navigateToStatus(){
	menu = STATUS;
	clear();
}

void navigateToMainMenu(){
	menu = MAIN;
	clear();
	setCursor(7,0);
	print("Status");
	setCursor(5,1);
	if(isAlarmActive)
		print("Deactivate");
	else
		print("Activate");
	setCursor(3,2);
	print("Change password");
	setCursor(6,3);
	print("About us");
}

void navigateToAboutUs(){
	menu = ABOUT;
	clear();
	setCursor(10, 0);
  write(6);
  write(5);
  write(4);
  write(3);
  write(2);
	write(1);
	write(0);
}


void numberToBCD(int i){
	int x1 = i&1;
	int x2 = i&2;
	int x3 = i&4;
	int x4 = i&8;
	
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,x1 > 0);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,x2 > 0);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,x3 > 0);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,x4 > 0);
}

void turnOff7seg(){
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9| GPIO_PIN_10,1);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,1);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,0);
	
}

extern UART_HandleTypeDef huart3;
void sendUsart(int number){
	unsigned char data[2]="";
	int n=sprintf(data,"%d\r", number);
	HAL_UART_Transmit(&huart3,data,n,1000);	
}

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim16;
extern UART_HandleTypeDef huart3;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles EXTI line[9:5] interrupts.
*/
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

	if(HAL_GetTick() - lastTickKeypad > 300){
		lastTickKeypad = HAL_GetTick();
		
		for(int i=2; i<4; i++){
			if(HAL_GPIO_ReadPin(rooms[i].buttonTypeDef, rooms[i].buttonPin)){
				rooms[i].isOn = !rooms[i].isOn;
				return;
			}
		}
	}
	
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9)==1){
		if(isAlarmActive && myTime.Hours >=0 && myTime.Hours <7)
			isAlarmRinging = true;
	}
  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
* @brief This function handles TIM1 break and TIM15 interrupts.
*/
void TIM1_BRK_TIM15_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 0 */
	turnOff7seg();
	switch(index7seg){
		case 0: 
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, 0);
			numberToBCD(mixedTempVolume/1000);
			index7seg = 1;
			break;
		case 1: 
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, 0);
			numberToBCD((mixedTempVolume/100)%10);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,1);
			index7seg = 2;
			break;
		case 2: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
			numberToBCD((mixedTempVolume/10)%10);
			index7seg = 3;
			break;
		case 3: 
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, 0);
			numberToBCD(mixedTempVolume%10);
			index7seg = 0;
			break;
		
		
	}
  /* USER CODE END TIM1_BRK_TIM15_IRQn 0 */
  HAL_TIM_IRQHandler(&htim15);
  /* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 1 */

  /* USER CODE END TIM1_BRK_TIM15_IRQn 1 */
}

/**
* @brief This function handles TIM1 update and TIM16 interrupts.
*/
void TIM1_UP_TIM16_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM16_IRQn 0 */
	
	if(isAlarmRinging){
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
	}

  /* USER CODE END TIM1_UP_TIM16_IRQn 0 */
  HAL_TIM_IRQHandler(&htim16);
  /* USER CODE BEGIN TIM1_UP_TIM16_IRQn 1 */

  /* USER CODE END TIM1_UP_TIM16_IRQn 1 */
}

/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

	
	temp = HAL_ADC_GetValue(&hadc1);
	scaledTemp = (float)temp*3300/4095/10;
	volume = HAL_ADC_GetValue(&hadc2);
	scaledVolume = MAX(0,(float)(volume-1150)/2800 * 60);
	mixedTempVolume = (int)scaledTemp*100 + scaledVolume;
	int light = HAL_ADC_GetValue(&hadc4);
	int scaledLight = (light - 980)*100/1100;
	HAL_RTC_GetTime(&hrtc, &myTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &myDate, RTC_FORMAT_BIN);
	HAL_ADC_Start_IT(&hadc2);
	HAL_ADC_Start_IT(&hadc1);
	HAL_ADC_Start_IT(&hadc4);
	
	if(menu==STATUS){
		//date and time
		char str[20];
		sprintf(str, "20%02d/%02d/%02d  %02d:%02d:%02d", myDate.Year, myDate.Month, myDate.Date, myTime.Hours, myTime.Minutes, myTime.Seconds);
		setCursor(0,0);
		print(str);
		
		// adc
		setCursor(0,2);
		sprintf(str, "%.2f%cC   light:%d", scaledTemp, 0xDF, scaledLight);
		print(str);
		
	}
	
	if(scaledLight < 50 && myTime.Hours >= 17 && myTime.Hours < 24){
		rooms[2].isOn = true;
	}		
	
	if(myTime.Hours >= 7 && rooms[0].isOn)
		rooms[0].isOn = false;
	
	if(scaledTemp > scaledVolume){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1);
		if(scaledTemp > scaledVolume + 10)
			isAlarmRinging = true;
		else
			isAlarmRinging = false;
	}
	else
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
	

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
* @brief This function handles TIM3 global interrupt.
*/
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
	
  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
* @brief This function handles TIM4 global interrupt.
*/
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

	for(int i=0; i<4; i++){
		if(rooms[i].isOn * 100 > rooms[i].fade){
			rooms[i].fade = rooms[i].fade + 10;
			__HAL_TIM_SET_COMPARE(&htim3, rooms[i].channel, rooms[i].fade);
		}
		else if(rooms[i].isOn * 100 < rooms[i].fade){
			rooms[i].fade = rooms[i].fade - 10;
			__HAL_TIM_SET_COMPARE(&htim3, rooms[i].channel, rooms[i].fade);
		}
	}
	
  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/**
* @brief This function handles USART3 global interrupt / USART3 wake-up interrupt through EXTI line 28.
*/
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}

/**
* @brief This function handles EXTI line[15:10] interrupts.
*/
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */
	
	if(HAL_GetTick() - lastTickKeypad > 300){
		lastTickKeypad = HAL_GetTick();
		
		
		if(HAL_GPIO_ReadPin(rooms[1].buttonTypeDef, rooms[1].buttonPin)){
				rooms[1].isOn = !rooms[1].isOn;
				if(myTime.Hours >= 0 && myTime.Hours < 7){
					if(rooms[1].isOn){
						rooms[0].isOn = false;
					}
					else{
						rooms[0].isOn = true;
					}
				}
				return;
		}
		else if(HAL_GPIO_ReadPin(rooms[0].buttonTypeDef, rooms[0].buttonPin)){
			rooms[0].isOn = !rooms[0].isOn;
				return;
		}
			
		
		uint16_t readPins[4] = {GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};
		char keys[16] = {
			'1', '2', '3', 'A', 
			'4', '5', '6', 'B', 
			'7', '8', '9', 'C', 
			'*', '0', '#', 'D', 
		};
		
		for(int i = 0; i<4 ; i++){
			if(HAL_GPIO_ReadPin(GPIOD, readPins[i])){
				pushedButton = 0;
				
				
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11, 0);
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 1);
				if(HAL_GPIO_ReadPin(GPIOD, readPins[i]))
					pushedButton = keys[i];
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 0);
				
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 1);
				if(HAL_GPIO_ReadPin(GPIOD, readPins[i]))
					pushedButton = keys[4+i];
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 0);
				
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, 1);
				if(HAL_GPIO_ReadPin(GPIOD, readPins[i]))
					pushedButton = keys[8+i];
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, 0);
				
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, 1);
				if(HAL_GPIO_ReadPin(GPIOD, readPins[i]))
					pushedButton = keys[12+i];
			
				if(pushedButton!=0){
//					setCursor(0,1);
//					print(&pushedButton);
					if(pushedButton=='1' && menu==MAIN){
						navigateToStatus();
					}
					else if(pushedButton=='A' && menu!=MAIN){
						navigateToMainMenu();
					}
					else if(pushedButton=='4' && menu==MAIN){
						navigateToAboutUs();
					}
				}
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11, 1);
				break;
			}
		}
	}

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */


/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
