/**
  ******************************************************************************
  * @file    layers_custom.h
  * @author  Marco Lattuada
  * @date    14-Dec-2020
  * @brief   header file of AI platform custom layers datatype
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
#ifndef LAYERS_CUSTOM_H
#define LAYERS_CUSTOM_H
#pragma once

#include "layers_common.h"

/*!
 * @defgroup layers_custom Custom layer definitions
 * @brief Definition of structures custom layers
 */

AI_API_DECLARE_BEGIN

/*!
 * @struct ai_layer_custom
 * @ingroup layers_custom
 * @brief Custom layer wrapper
 *
 * The custom layer wrapper
 */
typedef ai_layer_stateful ai_layer_custom;


AI_API_DECLARE_END

#endif /*LAYERS_CUSTOM_H*/
