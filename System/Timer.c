#include "stm32f10x.h"                  // Device header
void Timer1_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); // 使能TIM1时钟

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // 时钟分频
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseInitStruct.TIM_Period = 65-1; // ARR 设置为 64
    TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1; // PSC 设置为 7200 - 1
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0; // 重复计数

    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct); // 初始化 TIM1

    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); // 使能定时器更新中断

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置中断优先级分组
    NVIC_InitTypeDef NVIC_InitStruct;
    
    NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_IRQn; // 更改为 TIM1_UP_IRQn
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; // 使能中断
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2; // 抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1; // 子优先级

    NVIC_Init(&NVIC_InitStruct); // 初始化中断设置

    TIM_Cmd(TIM1, ENABLE); // 启动 TIM1
}