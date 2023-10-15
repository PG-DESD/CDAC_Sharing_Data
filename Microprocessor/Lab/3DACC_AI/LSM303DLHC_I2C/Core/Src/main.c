/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ai_platform.h"
#include "network.h"
#include "network_data.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define lsm303Address	0x32
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */
uint8_t i2cBuf[8];
uint8_t sensitivity = 1;
int16_t ax,ay,az;
float Xaccel,Yaccel,Zaccel;
ai_handle network;
float aiInData[AI_NETWORK_IN_1_SIZE];
float aiOutData[AI_NETWORK_OUT_1_SIZE];
uint8_t activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE];
const char* activities [AI_NETWORK_OUT_1_SIZE] = {"stationary", "walking", "running"};
uint32_t class_read;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_CRC_Init(void);
/* USER CODE BEGIN PFP */
static void AI_Init(ai_handle w_addr, ai_handle act_addr);
static void AI_Run(float *pIn, float *pOut);
static uint32_t argmax(const float * values, uint32_t len);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_I2C1_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */
   //1. Scan the I2C addresses
    	for(uint8_t i=0; i<255; i++)
    	{
    		if(HAL_I2C_IsDeviceReady(&hi2c1, i, 1, 10) == HAL_OK)
    		{
    			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
    			break;
    		}
    	}
    //2. I2C Write example
	//a)Configure MEMS: data rate, power mode, Enable X,Y,Z axes
	i2cBuf[0] = 0x20;			//Register address: CTRL_REG1_A (20h)
	i2cBuf[1] = 0x37;			//0x47 for Data rate 50 Hz, XYZ En, //0x37 for 25Hz ,XYZ En
	HAL_I2C_Master_Transmit(&hi2c1, lsm303Address, i2cBuf, 2, 10);
	//b) Configure MEMS: High Resolution Enable
	i2cBuf[0] = 0x23;			//Register address: CTRL_REG4_A (23h)
	i2cBuf[1] = 0x30;			//0x08 for 2g, High Resol. Enable//0x10 for 4g//0x30 for 16g
	HAL_I2C_Master_Transmit(&hi2c1, lsm303Address, i2cBuf, 2, 10);
	//c) Configure MEMS: Filter mode, cutoff frequency
	i2cBuf[0] = 0x21;			//Register address: CTRL_REG2_A (21h)
	i2cBuf[1] = 0x90;
	HAL_I2C_Master_Transmit(&hi2c1, lsm303Address, i2cBuf, 2, 10);

	AI_Init(ai_network_data_weights_get(), activations);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	uint32_t write_index = 0;
  while (1)
  {
	  //4. Read accelerometer data
	  	  		//Request to read from a register
	  	  		//Register address: X_axis L
	  	  		HAL_I2C_Mem_Read(&hi2c1, lsm303Address,0x28, 1, &i2cBuf[1], 1, 10);
				//Register address: X_axis H
	  	  		HAL_I2C_Mem_Read(&hi2c1, lsm303Address,0x29, 1, &i2cBuf[2], 1, 10);
	  	  		//Register address: Y_axis L
	  	  		HAL_I2C_Mem_Read(&hi2c1, lsm303Address,0x2A, 1, &i2cBuf[3], 1, 10);
				//Register address: Y_axis H
	  	  		HAL_I2C_Mem_Read(&hi2c1, lsm303Address,0x2B, 1, &i2cBuf[4], 1, 10);
	  	  		//Register address: Z_axis L
	  	  		HAL_I2C_Mem_Read(&hi2c1, lsm303Address,0x2C, 1, &i2cBuf[5], 1, 10);
				//Register address: Z_axis H
	  	  		HAL_I2C_Mem_Read(&hi2c1, lsm303Address,0x2D, 1, &i2cBuf[6], 1, 10);
	  	  		ax = ((int16_t)((uint16_t)i2cBuf[2]<<8) | i2cBuf[1]);
	  	  		ay = ((int16_t)((uint16_t)i2cBuf[4]<<8) | i2cBuf[3]);
	  	  		az = ((int16_t)((uint16_t)i2cBuf[6]<<8) | i2cBuf[5]);

	  	  		Xaccel = ax * sensitivity;
	  	  		Yaccel = ay * sensitivity;
	  	  		Zaccel = az * sensitivity;
	  	  		HAL_Delay(50);

	  	  	 //printf("% 5d, % 5d, % 5d\r\n",  (int) Xaccel, (int) Yaccel, (int) Zaccel);

	  	  	      /* Normalize data to [-1; 1] and accumulate into input buffer */
	  	  	      /* Note: window overlapping can be managed here */
	  	  	      aiInData[write_index + 0] = (float) Xaccel / 16000.0f;
	  	  	      aiInData[write_index + 1] = (float) Yaccel / 16000.0f;
	  	  	      aiInData[write_index + 2] = (float) Zaccel / 16000.0f;
	  	  	      write_index += 3;

	  	  	      if (write_index == AI_NETWORK_IN_1_SIZE) {
	  	  	        write_index = 0;

	  	  	        //printf("Running inference\n");
	  	  	        AI_Run(aiInData, aiOutData);

	  	  	        /* Output results */
	  	  	        for (uint32_t i = 0; i < AI_NETWORK_OUT_1_SIZE; i++) {
	  	  	          printf("%8.6f ", aiOutData[i]);
	  	  	        }
	  	  	        uint32_t class = argmax(aiOutData, AI_NETWORK_OUT_1_SIZE);
	  	  	        class_read=class;
	  	  	        printf(": %d - %s\n", (int) class, activities[class]);
	  	  	      }
	  	  	    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : PE8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
static void AI_Init(ai_handle w_addr, ai_handle act_addr)
{
  ai_error err;

  /* 1 - Create an instance of the model */
  err = ai_network_create(&network, AI_NETWORK_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    printf("ai_network_create error - type=%d code=%d\r\n", err.type, err.code);
    Error_Handler();
  }

  /* 2 - Initialize the instance */
  const ai_network_params params = AI_NETWORK_PARAMS_INIT(
    AI_NETWORK_DATA_WEIGHTS(w_addr),
    AI_NETWORK_DATA_ACTIVATIONS(act_addr)
  );

  if (!ai_network_init(network, &params)) {
    err = ai_network_get_error(network);
    printf("ai_network_init error - type=%d code=%d\r\n", err.type, err.code);
    Error_Handler();
  }
}

static void AI_Run(float *pIn, float *pOut)
{
  ai_i32 batch;
  ai_error err;

  /* 1 - Create the AI buffer IO handlers with the default definition */
  ai_buffer ai_input[AI_NETWORK_IN_NUM] = AI_NETWORK_IN;
  ai_buffer ai_output[AI_NETWORK_OUT_NUM] = AI_NETWORK_OUT;

  /* 2 - Update IO handlers with the data payload */
  ai_input[0].n_batches = 1;
  ai_input[0].data = AI_HANDLE_PTR(pIn);
  ai_output[0].n_batches = 1;
  ai_output[0].data = AI_HANDLE_PTR(pOut);

  batch = ai_network_run(network, ai_input, ai_output);
  if (batch != 1) {
    err = ai_network_get_error(network);
    printf("AI ai_network_run error - type=%d code=%d\r\n", err.type, err.code);
    Error_Handler();
  }
}

static uint32_t argmax(const float * values, uint32_t len)
{
  float max_value = values[0];
  uint32_t max_index = 0;
  for (uint32_t i = 1; i < len; i++) {
    if (values[i] > max_value) {
      max_value = values[i];
      max_index = i;
    }
  }
  return max_index;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

