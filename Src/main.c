
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
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
#include "main.h"
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
typedef volatile uint32_t TimerRegister;
typedef struct GeneralTimerRegs GeneralTimerRegs;
struct GeneralTimerRegs{
	TimerRegister cr1;		// control register 1
	TimerRegister cr2;		// control register 2
	TimerRegister smcr;		// slave mode control register
	TimerRegister dier;		// DMA/ Interrupt enable register
	TimerRegister sr;		// status register
	TimerRegister egr;		// event generation register
	TimerRegister ccmr1;	// capture/ compare mode register 1
	TimerRegister ccmr2;	// capture/ compare mode register 2
	TimerRegister ccer;		// capture/compare enable register
	TimerRegister cnt;		// counter
	TimerRegister psc;		// prescaler
	TimerRegister arr;		// auto-reload register
	TimerRegister ccr1;		// capture/compare register 1
	TimerRegister ccr2;		// capture/compare register 2
	TimerRegister ccr3;		// capture/compare register 3
	TimerRegister ccr4;		// capture/compare register 4
	TimerRegister dcr;		// DMA control register
	TimerRegister dmar;		// DMA address for full transfer
	TimerRegister or;		// option register
};

typedef enum
{
  TIM_STATE_RESET             = 0x00U,    /*!< Peripheral not yet initialized or disabled  */
  TIM_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
  TIM_STATE_BUSY              = 0x02U,    /*!< An internal process is ongoing              */
  TIM_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
  TIM_STATE_ERROR             = 0x04U     /*!< Reception process is ongoing                */
}TIM_State_TypeDef;

typedef enum
{
  Ok       = 0x00U,
  Error    = 0x01U,
  Busy     = 0x02U,
  Timeout  = 0x03U
} Status_TypeDef;


typedef struct TIM_Handle_Type TIM_Handle_Type;
struct TIM_Handle_Type{
	GenerralTimerRegs *Instance;
	volatile TIM_State_TypeDef State;
};
#define TIMER_CHANNEL_1                      0x00000000U
#define TIMER_CHANNEL_2                      0x00000004U
#define TIMER_CHANNEL_3                      0x00000008U
#define TIMER_CHANNEL_4                      0x0000000CU
#define TIMER_CHANNEL_ALL                    0x00000018U

#define TIMER_CCx_ENABLE                   0x00000001U
#define TIMER_CCx_DISABLE                  0x00000000U
#define TIMER_CCxN_ENABLE                  0x00000004U
#define TIMER_CCxN_DISABLE                 0x00000000U

#define timer1   ((TimerRegister*)0x40010000);
#define timer2   ((TimerRegister*)0x40000000);
#define timer3   ((TimerRegister*)0x40000400);
#define timer4   ((TimerRegister*)0x40000800);
#define timer5   ((TimerRegister*)0x40000c00);
#define timer6   ((TimerRegister*)0x40001000);
#define timer7   ((TimerRegister*)0x40001400);
#define timer8   ((TimerRegister*)0x40010400);
#define timer9   ((TimerRegister*)0x40014000);
#define timer10  ((TimerRegister*)0x40014400);
#define timer11  ((TimerRegister*)0x40014800);
#define timer12  ((TimerRegister*)0x40001800);
#define timer13  ((TimerRegister*)0x40001c00);
#define timer14  ((TimerRegister*)0x40002000);


Status_TypeDef TIM_BASE_START(TIM_Handle_Type *tim){
	tim->State = TIM_STATE_BUSY;
    tim->Instance->cr1 |= 1;
	tim->State = TIM_STATE_READY;

	return Ok;
}

TIM_Handle_Type tim2;

void Timer2init(TIM_Handle_Type *timer){
	timer->Instance = timer2;
}

void TIMER_CCxChannelCmd(GeneralTimerRegs* TIMx, uint32_t Channel, uint32_t ChannelState)
{
	 uint32_t tmp = 0U;


	 tmp = TIM_CCER_CC1E << Channel;

	 /* Reset the CCxE Bit */
	 TIMx->ccer &= ~tmp;

	 /* Set or reset the CCxE Bit */
	 TIMx->ccer |= (uint32_t)(ChannelState << Channel);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  MX_GPIO_Init();
  MX_TIM2_Init();

  Timer2init(&tim2);
  TIM_BASE_START(&tim2);

  /* USER CODE BEGIN 2 */

  //HAL_TIM_Base_Start(&htim2);
  //HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_3);

  //HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 0);
  //HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 0);

  //__HAL_TIM_SET_COUNTER(&htim2, 0);
  //__HAL_TIM_CLEAR_FLAG(&htim2, TIM_IT_UPDATE);
  //__HAL_TIM_CLEAR_FLAG(&htim2, TIM_IT_CC3);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	 // if(__HAL_TIM_GET_FLAG(&htim2,TIM_FLAG_UPDATE)){
		//  __HAL_TIM_CLEAR_FLAG(&htim2,TIM_IT_UPDATE);
	//	  HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
	 // }

//  if(__HAL_TIM_GET_FLAG(&htim2,TIM_FLAG_CC3)){
	//	  __HAL_TIM_CLEAR_FLAG(&htim2,TIM_FLAG_CC3);
	//	  HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
	//  }

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }

  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Activate the Over-Drive mode 
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = TIMER2_DIVIDER;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = TIMER2_ARR;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_INACTIVE;
  sConfigOC.Pulse = ( TIMER2_ARR / 3 );
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, LED3_Pin|LED4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED3_Pin LED4_Pin */
  GPIO_InitStruct.Pin = LED3_Pin|LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
