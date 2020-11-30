/** -------------------------------------------------------------------------- 
 * File: OMSModuleController.h
 * Created Date: 11-29-2020
 * Author: Thomas Ose
 * ---------------------------------------------------------------------------
 * Last Modified: Sunday, 29th November 2020 7:47:19 pm
 * Modified By: Thomas Ose (tmo@osemicro.com>)
 * ---------------------------------------------------------------------------
 * Copyright (c) 2016 - 2020 OMS(re)Models
 * 
 *  This source file is subject of the GNU general public license 2,
 *  that is available at the world-wide-web at
 *  http://www.gnu.org/licenses/gpl.txt
 * 
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  copy of this software and associated documentation files.  The above
 *  copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 * ---------------------------------------------------------------------------
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	----------------------------------------------------------
 * 11-29-2020	tmo	Added LEDBank definition
 * 11-29-2020	tmo	Created inital code base
 * --------------------------------------------------------------------------- */
#ifndef _OMSMODULECONTROLLER_h
#define _OMSMODULECONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "TaskScheduler.h"

// Define variables

//#define DEBUG

#define LEDBANK_1 4
#define LEDBANK_2 5
#define LEDBANK_3 6
#define LEDBANK_4 7

#define MOD_1 8
#define MOD_2 9
#define MOD_3 10
#define MOD_4 11
#define MOD_5 12

#define LIGHT_SENSOR_THRESHHOLD 1015
#define LIGHT_SENSOR A0

#define HEART_BEAT 13
#define SECONDS 1000 // 1000 miliseconds
#ifdef DEBUG
#define MINUTES 1000 // 1 second test time
#else
#define MINUTES 60000 // 60 Seconds
#endif

#define ON LOW
#define OFF HIGH

int LastSensorRead = 0;
bool LightRequire = true;
bool LastLightRequire = true;
bool LastLightStatus = true;
unsigned long LightRequireStartTime = 0;

// task scheduler variables
Scheduler runner; // the main runner task

void CheckSensor_Callback();
void CheckModule_CallBack();
void CheckHeartBeat_CallBack();

Task CheckSensor(2500, TASK_FOREVER, &CheckSensor_Callback);
Task CheckModule(2000, TASK_FOREVER, &CheckModule_CallBack);
Task CheckHeartBeat(1000, TASK_FOREVER, &CheckHeartBeat_CallBack);

#endif