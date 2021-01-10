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
int lastTickKeypad = 0, lastTickADC12 = 0, lastTickADC4=0;
char pushedButton = 0;


void setKeypadInputs(bool set){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, set);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, set);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, set);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, set);
}

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc4;

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
* @brief This function handles ADC1 and ADC2 interrupts.
*/
void ADC1_2_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_2_IRQn 0 */
//	if(HAL_GetTick() - lastTickADC12 > 1000){
//		lastTickADC12 = HAL_GetTick();
//		int adc = HAL_ADC_GetValue(&hadc1);
//		int adc2 = HAL_ADC_GetValue(&hadc2);
//		
////		char data[100];
////		int n = sprintf(data, "%d  %d", adc, adc2);
////		setCursor(0,0);
////		print("                ");
////		setCursor(0,0);
////		print(data);
//		
//	}
//	HAL_ADC_Start_IT(&hadc1);
//	HAL_ADC_Start_IT(&hadc2);
  /* USER CODE END ADC1_2_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  HAL_ADC_IRQHandler(&hadc2);
  /* USER CODE BEGIN ADC1_2_IRQn 1 */

  /* USER CODE END ADC1_2_IRQn 1 */
}

/**
* @brief This function handles EXTI line[15:10] interrupts.
*/
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */
	uint16_t readPins[4] = {GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};
	char keys[16] = {
		'1', '2', '3', 'A', 
		'4', '5', '6', 'B', 
		'7', '8', '9', 'C', 
		'*', '0', '#', 'D', 
	};
	
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
	
	if(HAL_GetTick() - lastTickKeypad > 300){
		for(int i = 0; i<4 ; i++){
			if(HAL_GPIO_ReadPin(GPIOD, readPins[i])){
				lastTickKeypad = HAL_GetTick();
				pushedButton = 0;
				
				setKeypadInputs(false);
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
					print(&pushedButton);
				}

				break;
			}
		}
		setKeypadInputs(true);
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

/**
* @brief This function handles ADC4 interrupt.
*/
void ADC4_IRQHandler(void)
{
  /* USER CODE BEGIN ADC4_IRQn 0 */
//	if(HAL_GetTick() - lastTickADC4 > 300){
//		lastTickADC4 = HAL_GetTick();
//		int adc = HAL_ADC_GetValue(&hadc4);
//		
//		char data[100];
//		int n = sprintf(data, "%d", adc);
//		setCursor(0,1);
//		print(data);
//		
//	}
//	HAL_ADC_Start_IT(&hadc4);
  /* USER CODE END ADC4_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc4);
  /* USER CODE BEGIN ADC4_IRQn 1 */

  /* USER CODE END ADC4_IRQn 1 */
}

/* USER CODE BEGIN 1 */


/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
