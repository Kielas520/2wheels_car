#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
    // 启用 TIM4 和 GPIOB 的时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       // 设置为复用推挽输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // 使用 GPIOB 的引脚 6 和 7（PB6 和 PB7）
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // 设置 GPIO 输出速率为 50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                 // 初始化 GPIOB

    TIM_InternalClockConfig(TIM4); // 配置 TIM4 使用内部时钟

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 不分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数模式为向上计数
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1; // 设置自动重载值 ARR, 计数周期为 100
    TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1; // 预分频器设置，定时器计时频率为 2 MHz (72 MHz / 36)
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // 重复计数器设置
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure); // 初始化 TIM4 的基本参数

    // PWM模式初始化
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure); // 初始化结构体到默认值

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // 设置输出模式为 PWM1
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; // 输出极性配置
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 使能输出
    TIM_OCInitStructure.TIM_Pulse = 0; // 初始占空比，设置为 0

    TIM_OC1Init(TIM4, &TIM_OCInitStructure); // 初始化 TIM4 的通道 1
    TIM_OC2Init(TIM4, &TIM_OCInitStructure); // 初始化 TIM4 的通道 2

    TIM_Cmd(TIM4, ENABLE); // 启动 TIM4
}

void PWM_SetCompareA(uint16_t Compare) // 设置通道1的比较值
{
    TIM_SetCompare1(TIM4, Compare); // 更新 TIM4 通道1 的比较值
}

void PWM_SetCompareB(uint16_t Compare) // 设置通道2的比较值
{
    TIM_SetCompare2(TIM4, Compare); // 更新 TIM4 通道2 的比较值
}