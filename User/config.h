#ifndef __CONFIG_H
#define __CONFIG_H

#pragma once

#include "MPU6050.h"
#include "Encoder.h"
#include "Motor.h"
#include <math.h>                       // 添加此行以包含数学函数的声明
#include "Serial.h"
#include "OLED.h"
#include "pid.h"
#include "format.h"



extern pid_t motorA;
extern pid_t motorB;
extern pid_t angle;

float SpeedA, SpeedB;                     // 当前速度


#endif
