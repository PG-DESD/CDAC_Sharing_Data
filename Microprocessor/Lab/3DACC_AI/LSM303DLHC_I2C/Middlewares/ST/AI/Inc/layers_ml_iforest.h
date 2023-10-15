/**
  ******************************************************************************
  * @file    layers_iforest.h
  * @author  AIS
  * @date    11-April-2021
  * @brief   header file of AI platform iForest layers datatypes
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
#ifndef __LAYERS_IFOREST_H_
#define __LAYERS_IFOREST_H_
#pragma once

#include "layers_common.h"

/*!
 * @defgroup layers_ml Layers Definitions
 * @brief definition 
 *
 */

AI_API_DECLARE_BEGIN


/* Allowed tests branch in the iTrees */
typedef enum
{
  AI_IFOREST_BRANCH_LT_IDX = 0,
  AI_IFOREST_BRANCH_LEQ_IDX,
  AI_IFOREST_BRANCH_EQ_IDX,
  AI_IFOREST_BRANCH_END,
} ai_iforest_branch_e;


/*!
 * @struct ai_layer_iforest
 * @ingroup layers_iforest
 * @brief iForest layer
 *
 * The type of iforest function is handled by the specific forward function
 * @ref forward_iforest
 */
typedef AI_ALIGNED_TYPE(struct, 4) ai_layer_iforest_ {
  AI_LAYER_COMMON_FIELDS_DECLARE
  ai_float global_average_path_length;  /*!< global average path length used to normalized average path length*/
  ai_float score_threshold;             /*!< score threshold used to center the score around 0 */
} ai_layer_iforest;



/******************************************************************************/
/*  Forward Functions Section                                                 */
/******************************************************************************/

/*!
 * @brief Decodes the iforest ML algorithm.
 * @ingroup layers_iforest
 * @param layer iforest layer
 */
AI_INTERNAL_API
void forward_iforest(ai_layer *pLayer);



AI_API_DECLARE_END

#endif    /*__LAYERS_IFOREST_H_*/
