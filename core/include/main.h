#pragma once

#include "rcc.hpp"
#include "gpio.hpp"
#include "sys_tick.hpp"

#include "constants.hpp"
#include "pin_defs.hpp"

#include <cstdint>

using namespace Peripherals;
using namespace System;

#ifndef NVIC_PRIORITYGROUP_0
  #define NVIC_PRIORITYGROUP_0    ((uint32_t)0x00000007)     /*!< 0 bit  for pre-emption priority, 4 bits for subpriority */
  #define NVIC_PRIORITYGROUP_1    ((uint32_t)0x00000006)     /*!< 1 bit  for pre-emption priority, 3 bits for subpriority */
  #define NVIC_PRIORITYGROUP_2    ((uint32_t)0x00000005)     /*!< 2 bits for pre-emption priority, 2 bits for subpriority */
  #define NVIC_PRIORITYGROUP_3    ((uint32_t)0x00000004)     /*!< 3 bits for pre-emption priority, 1 bit  for subpriority */
  #define NVIC_PRIORITYGROUP_4    ((uint32_t)0x00000003)     /*!< 4 bits for pre-emption priority, 0 bit  for subpriority */
#endif
