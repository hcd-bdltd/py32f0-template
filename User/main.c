/**
 ******************************************************************************
 * @file    main.c
 * @author  MCU Application Team
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
 * All rights reserved.</center></h2>
 *
 * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "main.h"

static void APP_TIM1Config(void);
static void APP_PWMChannelConfig(void);

int main(void)
{
    BSP_RCC_HSE_Config();
    BSP_LED_Init(LED_GREEN);

    APP_TIM1Config();
    APP_PWMChannelConfig();

    while (1)
    {
        BSP_LED_Toggle(LED_GREEN);
        LL_mDelay(1000);
    }
}

static void APP_PWMChannelConfig(void)
{
    LL_GPIO_InitTypeDef TIM1CH1MapInit = {0};
    LL_TIM_OC_InitTypeDef TIM_OC_Initstruct = {0};

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

    /* CH1: PA3 AF13 */
    /* CH2: PA13 AF13 */
    TIM1CH1MapInit.Pin = LL_GPIO_PIN_3 | LL_GPIO_PIN_13;
    TIM1CH1MapInit.Mode = LL_GPIO_MODE_ALTERNATE;
    TIM1CH1MapInit.Alternate = LL_GPIO_AF_13;
    LL_GPIO_Init(GPIOA, &TIM1CH1MapInit);

    /* CH1N: PA0 AF14 */
    /* CH2N: PA1 AF14 */
    TIM1CH1MapInit.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_1;
    TIM1CH1MapInit.Mode = LL_GPIO_MODE_ALTERNATE;
    TIM1CH1MapInit.Alternate = LL_GPIO_AF_14;
    LL_GPIO_Init(GPIOA, &TIM1CH1MapInit);

    TIM_OC_Initstruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_Initstruct.OCState = LL_TIM_OCSTATE_ENABLE;
    TIM_OC_Initstruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_Initstruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
    TIM_OC_Initstruct.OCNState = LL_TIM_OCSTATE_ENABLE;
    TIM_OC_Initstruct.OCNPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_Initstruct.OCNIdleState = LL_TIM_OCIDLESTATE_LOW;

    TIM_OC_Initstruct.CompareValue = 250;
    LL_TIM_OC_Init(TIM1, LL_TIM_CHANNEL_CH1, &TIM_OC_Initstruct);

    TIM_OC_Initstruct.CompareValue = 750;
    LL_TIM_OC_Init(TIM1, LL_TIM_CHANNEL_CH2, &TIM_OC_Initstruct);
}

static void APP_TIM1Config(void)
{
    LL_TIM_InitTypeDef TIM1CountInit = {0};

    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);

    TIM1CountInit.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    TIM1CountInit.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM1CountInit.Prescaler = 2400 - 1;
    TIM1CountInit.Autoreload = 1000 - 1;
    TIM1CountInit.RepetitionCounter = 0;
    LL_TIM_Init(TIM1, &TIM1CountInit);
    LL_TIM_EnableAllOutputs(TIM1);
    LL_TIM_EnableCounter(TIM1);
}

void APP_ErrorHandler(void)
{
    while (1)
        ;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    while (1)
        ;
}
#endif /* USE_FULL_ASSERT */
