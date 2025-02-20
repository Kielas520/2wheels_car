#include "stm32f10x.h"                  // 设备头文件

/**
  * 函    数：PWM初始化
  * 参    数：无
  * 返 回 值：无
  */
void PWM_Init(void)
{
	/* 开启时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);           // 开启TIM4的时钟
	
	/* GPIO初始化 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                 // 设置为复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;                       // 使用PB6引脚（TIM4_CH1）
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               // 设置GPIO速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);                           // 初始化PB6引脚
	
	/* 配置时钟源 */
	TIM_InternalClockConfig(TIM4);                                  // 选择TIM4为内部时钟
	
	/* 时基单元初始化 */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;              // 定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 时钟分频，选择不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;                 // 计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;               // 预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            // 重复计数器
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);             // 配置TIM4的时基单元
	
	/* 输出比较初始化 */ 
	TIM_OCInitTypeDef TIM_OCInitStructure;                           // 定义结构体变量
	TIM_OCStructInit(&TIM_OCInitStructure);                           // 结构体初始化
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               // 输出比较模式，选择PWM模式1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       // 输出极性，选择为高
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   // 输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;                               // 初始的CCR值
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);                         // 配置TIM4的输出比较通道1
	
	/* TIM使能 */
	TIM_Cmd(TIM4, ENABLE);                                           // 使能TIM4，定时器开始运行
}

/**
  * 函    数：PWM设置CCR
  * 参    数：Compare 要写入的CCR的值，范围：0~100
  * 返 回 值：无
  * 注意事项：CCR和ARR共同决定占空比，此函数仅设置CCR的值，并不直接是占空比
  *           占空比Duty = CCR / (ARR + 1)
  */
void PWM_SetCompare(uint16_t Compare)
{
	TIM_SetCompare1(TIM4, Compare);                                 // 设置CCR1的值
}
