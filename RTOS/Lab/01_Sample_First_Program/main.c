/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "SEGGER_SYSVIEW.h"
/* USER CODE END Includes */

/* USER CODE BEGIN PFP */
void Task1(void *argument);
void Task2(void *argument);
void Task3(void *argument);
void lookBusy( void );
/* USER CODE END PFP */

  /* USER CODE BEGIN 1 */
	const static uint32_t stackSize = 128;

  /* USER CODE END 1 */

  
  /* USER CODE BEGIN 2 */
  SEGGER_SYSVIEW_Conf();
  if (xTaskCreate(Task1, "task1", stackSize, NULL, tskIDLE_PRIORITY + 2, NULL) == pdPASS)
    	{
    		if (xTaskCreate(Task2, "task2", stackSize, NULL, tskIDLE_PRIORITY + 1, NULL) == pdPASS)
    		{
    			if (xTaskCreate(Task3, "task3", stackSize, NULL, tskIDLE_PRIORITY + 1, NULL) == pdPASS)
    			{
    				//start the scheduler - shouldn't return unless there's a problem
    				vTaskStartScheduler();
    			}
    		}
    	}
  /* USER CODE END 2 */


/* USER CODE BEGIN 4 */
void Task1(void *argument)
{
  while(1)
  {
	  SEGGER_SYSVIEW_PrintfHost("hey there!\n");
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, SET);
	  vTaskDelay(105/ portTICK_PERIOD_MS);
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, RESET);
	  vTaskDelay(100/ portTICK_PERIOD_MS);
  }
}

void Task2( void* argument )
{
	while(1)
	{
		SEGGER_SYSVIEW_PrintfHost("task 2 says 'Hi!'\n");
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, SET);
		vTaskDelay(200 / portTICK_PERIOD_MS);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, RESET);
		vTaskDelay(200 / portTICK_PERIOD_MS);
	}
}

void Task3( void* argument )
{
	while(1)
	{
		lookBusy();

		SEGGER_SYSVIEW_PrintfHost("task3\n");
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, SET);
		vTaskDelay(500/ portTICK_PERIOD_MS);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, RESET);
		vTaskDelay(500/ portTICK_PERIOD_MS);
	}
}

void lookBusy( void )
{
	volatile uint32_t __attribute__((unused)) dontCare = 0;
	for(int i = 0; i < 50E3; i++)
	{
		dontCare = i % 4;
	}
	SEGGER_SYSVIEW_PrintfHost("looking busy\n");
}
/* USER CODE END 4 */