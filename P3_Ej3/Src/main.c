
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_debounce.h"
#include "API_delay.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

#define TIMEOUTLED1 100
#define TIMEOUTLED2 500
#define TIMEOUTLED3 1000
#define TIMEOUTLED 500


static delay_t timerLED1;
static delay_t timerLED2;
static delay_t timerLED3;
bool_t status = true;



static void Period1()
{	delayWrite(&timerLED1,TIMEOUTLED1 );
	delayWrite(&timerLED2,TIMEOUTLED2 );
	delayWrite(&timerLED3,TIMEOUTLED3 );
	delayInit(&timerLED1,TIMEOUTLED1);
	delayInit(&timerLED2, TIMEOUTLED2);
	delayInit(&timerLED3, TIMEOUTLED3);

}

static void Period2()
{	delayWrite(&timerLED1,TIMEOUTLED);
	delayWrite(&timerLED2,TIMEOUTLED);
	delayWrite(&timerLED3,TIMEOUTLED);
	delayInit(&timerLED1,TIMEOUTLED);
	delayInit(&timerLED2, TIMEOUTLED);
	delayInit(&timerLED3, TIMEOUTLED);

}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{


  HAL_Init();

  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);


  BSP_LED_On(LED1);
  BSP_LED_On(LED2);
  BSP_LED_On(LED3);


  setButtomPressedCBK(Period1);
  setButtomReleasedCBK(Period2);

  debounceInit();
  delayInit(&timerLED1,TIMEOUTLED1);
  delayInit(&timerLED2, TIMEOUTLED2);
  delayInit(&timerLED3, TIMEOUTLED3);

  /* Infinite loop */
  while (1)
  {


	  debounceUpdate();

	  if (delayRead(&timerLED1)){
		  BSP_LED_Toggle(LED1);
	  }
	  if (delayRead(&timerLED2)){
	  	  BSP_LED_Toggle(LED2);
	  }
	  if (delayRead(&timerLED3)){
	  	  BSP_LED_Toggle(LED3);
	  }
  }
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED3);
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
