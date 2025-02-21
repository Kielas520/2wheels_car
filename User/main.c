#include "stm32f10x.h"                  // 设备头文件
#include "config.h"

float pitch = 0;
float current_pitch = 0;

int main(void)
{
    /* 模块初始化 */
    OLED_Init();                   // 初始化OLED显示
	Serial_Init();		//串口初始化
    MPU6050_Init();               // 初始化MPU6050传感器
    EncoderA_Init();               // 初始化编码器
	EncoderB_Init();               // 初始化编码器
    Motor_Init();                 // 初始化电机
	pid_Init(&motorA, DELTA_PID, 0.25, 0.2, 0.05); //kp, ki, kd
	pid_Init(&motorB, DELTA_PID, 0.27, 0.2, 0.05); //kp, ki, kd
	pid_Init(&angle, POSITION_PID, -2.8, 0, 0);  //kp, ki, kd
	angle.target = 0;  // 目标角度(直立时为0)
	
	/* 显示 */
	OLED_ShowString(1, 1, "Kielas"); // 显示静态字符串
	OLED_ShowString(1, 8, "pitch");     // 显示静态字符串	
	OLED_ShowString(3, 1, "A:");     // 显示静态字符串
	OLED_ShowString(3, 8, "B:");  // 显示静态字符串	

    while (1)
    {
        pitch = get_pitch(current_pitch);
		current_pitch = pitch;
		angle_pid_control(&angle, pitch);
		speed_pid_controlA();
		speed_pid_controlB();

        // 显示当前数据
        OLED_ShowSignedNum(2, 8, pitch, 5); // 显示当前角度
        OLED_ShowSignedNum(4, 1, motorA.target, 5);    // 显示当前速度
        OLED_ShowSignedNum(4, 8, motorB.target, 5); // 显示目标速度
		Serial_Printf("%f,%f,%f\n", motorB.target, motorB.out, motorB.now);
    }
}



