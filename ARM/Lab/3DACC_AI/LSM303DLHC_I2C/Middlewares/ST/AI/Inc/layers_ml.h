/**
  ******************************************************************************
  * @file    layers_ml.h
  * @author  AST Embedded Analytics Research Platform
  * @date    31-Marzo-2021
  * @brief   header file of AI platform ml layers datatypes
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
#ifndef __LAYERS_ML_H_
#define __LAYERS_ML_H_



#pragma once

#include "layers_common.h"

/*!
 * @defgroup layers_generic ML Layers Definitions
 * @brief definition
 *
 */

AI_API_DECLARE_BEGIN

/*!
 * @struct ai_layer_ArrayFeatureExtractor
 * @ingroup layers_ml
 * @brief ai_layer_ArrayFeatureExtractor layer definition
 *
 * This layer select elements of the input tensor based on the indices passed. It is intended to be used
 * by his associated forward function @ref forward_arrayfeatureextractor
 */
typedef AI_ALIGNED_TYPE(struct, 4) ai_layer_arrayfeatureextractor_ {
  AI_LAYER_COMMON_FIELDS_DECLARE
  ai_tensor* indices;  /*!< Indices of corrisponding axis in axes*/
} ai_layer_arrayfeatureextractor;


/*!
 * @struct ai_layer_ZipMap
 * @ingroup layers_ml
 * @brief ai_layer_ZipMap layer definition
 *
 * This layer creates a map from the input and the attributes.
 * The values are provided by the input tensor, while the keys are specified by the attributes.
 * The user must provide keys in either classlabels_strings or classlabels_int64s (but not both).
 * The columns of the tensor correspond one-by-one to the keys specified by the attributes.
 * There must be as many columns as keys.
 * It is intended to be used by his associated forward function @ref forward_zipmap.
 */
typedef AI_ALIGNED_TYPE(struct, 4) ai_layer_zipmap_ {
  AI_LAYER_COMMON_FIELDS_DECLARE
  ai_bool has_classlabels_int;
} ai_layer_zipmap;


/******************************************************************************/
/* Forward Functions Section                                                  */
/******************************************************************************/


/*!
 * @brief select elements of the input tensor based on the indices passed.
 * @ingroup layers_ml
 * @param layer array feture extractor
 */
AI_INTERNAL_API
void forward_arrayfeatureextractor(ai_layer* layer);


/*!
 * @brief creates a map from the inputs and the attributes
 * @ingroup layers_ml
 * @param layer zipmap
 */
AI_INTERNAL_API
void forward_zipmap(ai_layer* layer);



AI_API_DECLARE_END

#endif    /*__LAYERS_ML_H_*/
