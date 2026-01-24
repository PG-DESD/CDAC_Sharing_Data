/**
  ******************************************************************************
  * @file    network_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-01-24T14:03:49+0530
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

#include "network_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_network_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_network_weights_array_u64[59] = {
  0x3eaed74ebf2b2689U, 0xbf39c8e63f18696fU, 0x3edc074fbdbdd52dU, 0xbe519e603e5a4f25U,
  0x3ea8c2943e523d51U, 0xbd8bd529bd8d41bbU, 0x3f35a9f43e16877eU, 0xbf51ab2bbea21298U,
  0xbc50ac023d8329c1U, 0x3e9623f3bc302228U, 0xbdf3f05fbd8d2de7U, 0x3d45bfee3e637ee4U,
  0x3e6d3faf3f3a827fU, 0xbde212a13f11fe73U, 0xbe9a07d1bcee46c1U, 0x3f7607c33e06a109U,
  0x3eb840febed10681U, 0x3eb5bef6bee12bbbU, 0xbec51f543ed97dd8U, 0xbe3eda6bbf6cecd4U,
  0xbde2a2be3f391f83U, 0xbf262ccc3e635163U, 0xbedbe216bea574ffU, 0x3e2a11063f5fd620U,
  0x3ed185d6be8c7e3bU, 0x3f3c3692be3caa13U, 0xbdc5fa3a3ee4c92cU, 0xbdf9ee063f41820bU,
  0xbe37171e3e4ad2a9U, 0x3e6941f13de430f8U, 0xbf64bb7ebe2892dcU, 0x3f0d839f3f02a6baU,
  0x3e055f9abefc0adfU, 0xbe570284bd35e430U, 0x3dc956fa3dd31ac9U, 0x3f399e3bbe3ce6a6U,
  0xbdac6bf93d1cf075U, 0x3e80e3953f1afb97U, 0x3e46d534bf179eadU, 0xbe96b5abbf301fe7U,
  0xbeed69a23d9df91bU, 0xbf12b5e73d2f767bU, 0xbf249a833f1e7355U, 0xbec1827b3e253f3dU,
  0x3e40fde73ee8a3a0U, 0x3ee9224fbf0abfaaU, 0xbca4f4bc3e33888bU, 0xbcfb93483e1b98eaU,
  0xbe510766bca71d01U, 0x3de784863e8e6a18U, 0xbe1cb2283e1735d5U, 0x3cb1edce3f807626U,
  0x3e2a60463e0460fdU, 0x3da5e086bf89f8a2U, 0xbe54438e3f84e216U, 0x3f45b6edbeb91490U,
  0xbed204a63f07506dU, 0xbf63c361bf15b5dbU, 0x3cc3206bbe803727U,
};


ai_handle g_network_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_network_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

