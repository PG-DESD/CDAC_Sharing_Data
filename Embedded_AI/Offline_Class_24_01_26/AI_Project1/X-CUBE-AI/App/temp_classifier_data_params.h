/**
  ******************************************************************************
  * @file    temp_classifier_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-01-23T22:32:45+0530
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef TEMP_CLASSIFIER_DATA_PARAMS_H
#define TEMP_CLASSIFIER_DATA_PARAMS_H

#include "ai_platform.h"

/*
#define AI_TEMP_CLASSIFIER_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_temp_classifier_data_weights_params[1]))
*/

#define AI_TEMP_CLASSIFIER_DATA_CONFIG               (NULL)


#define AI_TEMP_CLASSIFIER_DATA_ACTIVATIONS_SIZES \
  { 96, }
#define AI_TEMP_CLASSIFIER_DATA_ACTIVATIONS_SIZE     (96)
#define AI_TEMP_CLASSIFIER_DATA_ACTIVATIONS_COUNT    (1)
#define AI_TEMP_CLASSIFIER_DATA_ACTIVATION_1_SIZE    (96)



#define AI_TEMP_CLASSIFIER_DATA_WEIGHTS_SIZES \
  { 780, }
#define AI_TEMP_CLASSIFIER_DATA_WEIGHTS_SIZE         (780)
#define AI_TEMP_CLASSIFIER_DATA_WEIGHTS_COUNT        (1)
#define AI_TEMP_CLASSIFIER_DATA_WEIGHT_1_SIZE        (780)



#define AI_TEMP_CLASSIFIER_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_temp_classifier_activations_table[1])

extern ai_handle g_temp_classifier_activations_table[1 + 2];



#define AI_TEMP_CLASSIFIER_DATA_WEIGHTS_TABLE_GET() \
  (&g_temp_classifier_weights_table[1])

extern ai_handle g_temp_classifier_weights_table[1 + 2];


#endif    /* TEMP_CLASSIFIER_DATA_PARAMS_H */
