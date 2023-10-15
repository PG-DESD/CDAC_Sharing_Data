/**
  ******************************************************************************
  * @file    layers.h
  * @author  AST Embedded Analytics Research Platform
  * @date    01-May-2017
  * @brief   header file of AI platform layers datatypes
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#ifndef LAYERS_H
#define LAYERS_H
#pragma once

#include "layers_common.h"
#include "layers_conv2d.h"
#include "layers_custom.h"
#include "layers_formats_converters.h"
#include "layers_generic.h"
#include "layers_nl.h"
#include "layers_norm.h"
#include "layers_pool.h"
#include "layers_rnn.h"
#include "layers_dense.h"
#include "layers_sm.h"
#include "layers_ml_iforest.h"
#include "layers_ml_svmregressor.h"
#include "layers_ml_svc.h"
#include "layers_ml.h"

// #include "layers_template.h"

#ifdef USE_OPERATORS
  #include "layers_lambda.h"
#endif /* USE_OPERATORS */


AI_API_DECLARE_BEGIN

/*!
 * @struct ai_any_layer_ptr
 * @ingroup layers
 * @brief Generic union for typed layers pointers
 */
typedef struct {
  ai_layer_type type;              /*!< layer type id (see @ref ai_layer_type) */
  union {
#define LAYER_ENTRY(type_, id_, struct_, forward_func_, init_func_, destroy_func_) \
   AI_CONCAT(ai_layer_, struct_)* struct_;
#include "layers_list.h"
  };
} ai_any_layer_ptr;


AI_API_DECLARE_END

#endif /*LAYERS_H*/
