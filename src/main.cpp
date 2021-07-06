/** -------------------------------------------------------------------------- 
 * File: main.cpp
 * Created Date: 11-29-2020
 * Author: Thomas Ose
 * ---------------------------------------------------------------------------
 * Last Modified: Monday, 5th July 2021 8:12:40 pm
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
 * 11-29-2020	tmo	Added LEDBank functionality
 * 11-29-2020	tmo	Created initial code base
 * --------------------------------------------------------------------------- */
#include "OMSModuleController.h"

/**
 * @brief  CallBack function for the sensor check
 * @note   Read the photo cell and sees if the light is required.  Sets NEED_LIGHT appropriately.
 *          If the value changes then also resets the relay counters.
 * @retval None
 */
void CheckSensor_Callback()
{
    int value = analogRead(LIGHT_SENSOR);
    delay(10);
    Serial.println(value);
    bool lightRequested = (value < 200) ? true: false;
    if (LastSensorRead != lightRequested)
    {
        LastSensorRead = lightRequested;
        LightRequire = lightRequested;
        Serial.println(LightRequire);
        Serial.println(LastLightStatus);
        if (LightRequire != LastLightStatus)
        {
            if (LightRequire && !LastLightRequire)
            {
                LastLightRequire = true;
                LightRequireStartTime = 0;
                Serial.println("Turn on lights");
            }
            if (!LightRequire && LastLightRequire)
            {
                LastLightRequire = false;
                Serial.println("Light Not Required");
            }
        }
        LastLightStatus = LightRequire;
    }
}

/**
 * @brief  Control all the relay outputs
 * @note   LightRequired controll the action of the Modules and LED Lights  
 * @retval None
 */
void CheckModule_CallBack()
{
    if (LightRequire && LightRequireStartTime == 0)
    {
        LightRequireStartTime = millis();
        digitalWrite(MOD_1, ON);
        digitalWrite(MOD_2, OFF);
        digitalWrite(MOD_3, ON);
        digitalWrite(MOD_4, ON);
        digitalWrite(MOD_5, ON);

        digitalWrite(LEDBANK_1, ON);
        digitalWrite(LEDBANK_2, ON);
        digitalWrite(LEDBANK_3, ON);
        digitalWrite(LEDBANK_4, ON);
    }
    if (!LightRequire && LightRequireStartTime != 0)
    {
        LightRequireStartTime = 0;
        digitalWrite(MOD_1, OFF);
        digitalWrite(MOD_2, ON);
        digitalWrite(MOD_3, OFF);
        digitalWrite(MOD_4, OFF);
        digitalWrite(MOD_5, OFF);

        digitalWrite(LEDBANK_1, OFF);
        digitalWrite(LEDBANK_2, OFF);
        digitalWrite(LEDBANK_3, OFF);
        digitalWrite(LEDBANK_4, OFF);
    }
}

/**
 * @brief  Heart beat routine
 * @note   Alternates the Arduino LED to indicate that the processor is working.
 * @retval None
 */
void CheckHeartBeat_CallBack()
{
    bool PinOn = digitalRead(HEART_BEAT);
    digitalWrite(HEART_BEAT, PinOn ? LOW : HIGH);
}

/**
 * @brief  Setup of default functions and values for the application
 * @note   
 * @retval None
 */
void setup()
{
#ifdef DEBUG // only write to the serial port if we are in debug mode
    Serial.begin(9600);
#endif

    LightRequireStartTime = 0;
    LastLightRequire = false;
    LightRequire = false;
    LastSensorRead = true;

    pinMode(MOD_1, OUTPUT);
    pinMode(MOD_2, OUTPUT);
    pinMode(MOD_3, OUTPUT);
    pinMode(MOD_4, OUTPUT);
    pinMode(MOD_5, OUTPUT);

    pinMode(LEDBANK_1, OUTPUT);
    pinMode(LEDBANK_2, OUTPUT);
    pinMode(LEDBANK_3, OUTPUT);
    pinMode(LEDBANK_4, OUTPUT);

    pinMode(LIGHT_SENSOR, INPUT);
    pinMode(HEART_BEAT, OUTPUT);

    runner.init();

    runner.addTask(CheckSensor);
    CheckSensor.enable();
    Serial.println("Photo Sensor task added");

    runner.addTask(CheckModule);
    CheckModule.enable();
    Serial.println("Module Control task added");

    runner.addTask(CheckHeartBeat);
    CheckHeartBeat.enable();
    Serial.println("Heartbeat task added");

    digitalWrite(MOD_1, OFF);
    digitalWrite(MOD_2, ON);
    digitalWrite(MOD_3, OFF);
    digitalWrite(MOD_4, OFF);
    digitalWrite(MOD_5, OFF);

    digitalWrite(LEDBANK_1, OFF);
    digitalWrite(LEDBANK_2, OFF);
    digitalWrite(LEDBANK_3, OFF);
    digitalWrite(LEDBANK_4, OFF);
}

/**
 * @brief  Main program loop
 * @note   
 * @retval None
 */
void loop()
{
    runner.execute();
}
