/**
  ******************************************************************************
  * @file    layers_formats_converters.h
  * @author  AST Embedded Analytics Research Platform
  * @date    10-Mar-2021
  * @brief   header file of formats converters layers
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
#ifndef LAYERS_FORMATS_CONVERTERS_H
#define LAYERS_FORMATS_CONVERTERS_H
#pragma once

#include "layers_common.h"

/*!
 * @defgroup layers_formats_converters Formats Converters Layers Definition
 * @brief this group implements formats converter layers (cast, etc.)
 *
 */

AI_API_DECLARE_BEGIN

/*!
 * @struct ai_layer_cast
 * @ingroup layers_formats_converters
 * @brief C Implementation of cast layer
 */
typedef AI_ALIGNED_TYPE(struct, 4) ai_layer_cast_ {
  AI_LAYER_COMMON_FIELDS_DECLARE
  ai_array_format     to_format;    /*!< cast output format */
} ai_layer_cast;


/*****************************************************************************/
/*  Forward Functions Section                                                */
/*****************************************************************************/

/*!
 * @brief forward function for cast layer.
 * @ingroup layers_
 * @param layer template layer as an opaque pointer
 */
AI_INTERNAL_API
void forward_cast(ai_layer* layer);


AI_API_DECLARE_END

#endif    /*LAYERS_FORMATS_CONVERTERS_H*/
