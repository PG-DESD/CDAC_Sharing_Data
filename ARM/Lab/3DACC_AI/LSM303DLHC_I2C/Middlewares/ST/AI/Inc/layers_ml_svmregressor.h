/**
  ******************************************************************************
  * @file    layers_svmregressor.h
  * @author  AIS
  * @date    11-Jan-2021
  * @brief   header file of AI platform SVM Regressor datatypes
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
#ifndef __LAYERS_SVMREGRESSOR_H_
#define __LAYERS_SVMREGRESSOR_H_
#pragma once

#include "layers_common.h"

/*!
 * @defgroup layers_svmreg Layers Definitions
 * @brief definition 
 *
 */

AI_API_DECLARE_BEGIN


/* SVM regressor kernel types */
typedef enum ai_svm_kernel_e_ {
  AI_SVMREG_KERNEL_LINEAR = 0,
  AI_SVMREG_KERNEL_POLYNOMIAL,
  AI_SVMREG_KERNEL_RBF,
  AI_SVMREG_KERNEL_SIGMOID,
  AI_SVMREG_KERNEL_UNSUPPORTED,
} ai_svm_kernel_e;


/*!
 * @struct ai_layer_svmreg
 * @ingroup layers_svmreg
 * @brief SVM Regressor layer
 *
 * The type of svmreg function is handled by the specific forward function
 * @ref forward_svm_regressor
 */
typedef AI_ALIGNED_TYPE(struct, 4) ai_layer_svmreg_ {
  AI_LAYER_COMMON_FIELDS_DECLARE
  ai_float intercept;       /*!< constant used in the decision function */
  ai_float gamma;           /*!< kernel coefficient for rbf, polynomial and sigmoid functions */
  ai_float coef0;           /*!< term in polynomial and sigmoid functions */
  ai_u32 degree;            /*!< polynomial function degree */
  ai_svm_kernel_e kernel_type;       /*!< kernel type : see ai_svm_kernel_e */
} ai_layer_svmreg;



/******************************************************************************/
/*  Forward Functions Section                                                 */
/******************************************************************************/

/*!
 * @brief Decodes the SVM Regressor ML operator.
 * @ingroup layers_svmreg
 * @param layer svm regressor layer
 */
AI_INTERNAL_API
void forward_svm_regressor(ai_layer *pLayer);



AI_API_DECLARE_END

#endif    /*__LAYERS_SVMREGRESSOR_H_*/
